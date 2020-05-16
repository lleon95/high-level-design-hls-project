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

#include "bresenham.hpp"

#define OUTPUT_FILE "/tmp/bresenham_line_plot.raw"
#define X1 100
#define X2 200
#define Y1 2
#define Y2 250

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
void bresenham_sw(unsigned char img[IMG_SIZE_H][IMG_SIZE_W],
		int x1, int y1, int x2, int y2)
{
   int m_new = 2 * (y2 - y1);
   int slope_error_new = m_new - (x2 - x1);
   for (int x = x1, y = y1; x <= x2; x++)
   {
	  img[y][x] = 1;

      /* Add slope to increment angle formed */
      slope_error_new += m_new;

      /* Slope error reached limit, time to
       * increment y and update slope error. */
      if (slope_error_new >= 0)
      {
         y++;
         slope_error_new  -= 2 * (x2 - x1);
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
	bresenham(img_hw, X1, Y1, X2, Y2);
	/* Run on SW */
	bresenham_sw(img_sw, X1, Y1, X2, Y2);

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

