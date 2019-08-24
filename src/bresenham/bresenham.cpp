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
 * C++ program for Bresenham's Line Generation
 * Assumptions :
 * 1) Line is drawn from left to right.
 * 2) x1 < x2 and y1 < y2
 * 3) Slope of the line is between 0 and 1.
 *
 * Inspired by:
 * https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/
 */

#include "bresenham.hpp"

/*
 * Accelerator
 *
 * Params:
 * Image array: img
 * Start point: x1, y1
 * End point: x2, y2
 */
void bresenham(interface_t img[IMG_SIZE_H][IMG_SIZE_W],
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
