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

/*
 * C++ program for Mid_Point's Circle Generation
 *
 * Inspired by:
 * https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
 */

#include "mid_point.hpp"

/*
 * Accelerator
 *
 * Params:
 * Image array: img
 * Start point: x1, y1
 * End point: x2, y2
 */
void mid_point(interface_t img[IMG_SIZE_H][IMG_SIZE_W],
	       ap_int<DIMENSION_WORD_WIDTH> x_center, ap_int<DIMENSION_WORD_WIDTH> y_center,
	       ap_int<DIMENSION_WORD_WIDTH> radius)
{
  ap_int<DIMENSION_WORD_WIDTH> x = radius;
  ap_int<DIMENSION_WORD_WIDTH> y = 0;
  ap_int<DIMENSION_WORD_WIDTH> P = 1 - radius;

      
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

