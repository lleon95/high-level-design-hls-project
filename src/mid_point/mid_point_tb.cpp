/*
 * High level design course
 * MSc in Electronics Engineering
 * II Quarter - 2019
 *
 * By:
 *    Luis Leon
 *    Emmanuel Madrigal
 *    Eliecer Mora
 */

#include <iostream>
#include <fstream>

#include "mid_point.hpp"

#define OUTPUT_FILE "/tmp/mid_point_circle_plot.raw"
#define X_CENTER 100
#define Y_CENTER 200
#define RADIUS 20

/*
 * This function writes the image in a file
 * Format: raw (GRAY8)
 * Receives: interface_t array
 */
int img_writer(interface_t img[IMG_SIZE_H][IMG_SIZE_W]) {
	std::ofstream img_out (OUTPUT_FILE);

	if (!img_out.is_open()) {
		return -1;
	}

	for (int y = 0; y < IMG_SIZE_H; y++) {
		for (int x = 0; x < IMG_SIZE_W; x++) {
			unsigned char value = 0;
			value = img[y][x] * 0xFF;
			img_out << value;
		}
	}

	return 0;
}

/*
 * This function initialises the "memory" array
 * Receives: interface_t array
 */
void init_array(interface_t img[IMG_SIZE_H][IMG_SIZE_W]) {
	for (int y = 0; y < IMG_SIZE_H; y++) {
		for (int x = 0; x < IMG_SIZE_W; x++) {
			img[y][x] = 0x0;
		}
	}
}

/*
 * This function compares the HW and SW results looking
 * for errors
 * Receives: interface_t array (img_hw)
 *           unsigned char array (img_sw)
 */
int compare_arrays(unsigned char img_sw[IMG_SIZE_H][IMG_SIZE_W],
		interface_t img_hw[IMG_SIZE_H][IMG_SIZE_W])
{
	int errors = 0;
	for(int y = 0; y < IMG_SIZE_H; y++) {
		for(int x = 0; x < IMG_SIZE_W; x++) {
			unsigned char hw_result = img_hw[y][x];
			errors += img_sw[y][x] != hw_result;
		}
	}
	return errors;
}

/*
 * This function performs exactly the same operations at
 * software level that the accelerator.
 *
 * The hardware version in RTL could perform operations
 * in another way that the described by C++, leading to
 * different results.
 */
void mid_point_sw(unsigned char img[IMG_SIZE_H][IMG_SIZE_W],
		  int x_center, int y_center, int radius)
{
  int x = radius, y = 0;
  int P = 1 - radius;
      
  /* Initial point on the axes after translation */
  img[x + x_center][y + y_center] = 1;
      
  /* When radius is zero only a single point will be printed */
  if (radius > 0) 
    {
      img[x + x_center][-y + y_center] = 1;
      img[y + x_center][x + y_center] = 1;
      img[-y + x_center][x + y_center] = 1;
    } 

  while (x > y) 
    {  
      y++; 
          
      /* Mid-point is inside or on the perimeter */
      if (P <= 0) 
	P = P + 2*y + 1; 
              
      /* Mid-point is outside the perimeter */
      else
	{ 
	  x--; 
	  P = P + 2*y - 2*x + 1; 
	} 
          
      /* All the perimeter points have already been printed */
      if (x < y) 
	break; 
          
      /*
       * Printing the generated point and its reflection in the other
       * octants after translation
       */
      img[x + x_center][y + y_center] = 1;
      img[-x + x_center][y + y_center] = 1;
      img[x + x_center][-y + y_center] = 1;
      img[-x + x_center][-y + y_center] = 1;
          
      /* 
       * If the generated point is on the line x = y then the
       * perimeter points have already been printed
       */
      if (x != y) 
	{ 
	  img[y + x_center][x + y_center] = 1;
	  img[-y + x_center][x + y_center] = 1;
	  img[y + x_center][-x + y_center] = 1;
	  img[-y + x_center][-x + y_center] = 1;
	} 
    }  
}

int main(int argc, char ** argv)
{
	/* Image buffer */
	interface_t img_hw[IMG_SIZE_H][IMG_SIZE_W];
	unsigned char img_sw[IMG_SIZE_H][IMG_SIZE_W] = {0};
	init_array(img_hw);

	/* Run on HW */
	mid_point(img_hw, X_CENTER, Y_CENTER, RADIUS);
	/* Run on SW */
	mid_point_sw(img_sw, X_CENTER, Y_CENTER, RADIUS);

	/* Verify */
	int errors = compare_arrays(img_sw, img_hw);

	if (errors == 0) {
		std::cout << "-- Simulation passed --" << std::endl;
	} else {
		std::cout << "-- Simulation failed --" << std::endl;
	}

	/* Output */
	img_writer(img_hw);
	return errors;
}

