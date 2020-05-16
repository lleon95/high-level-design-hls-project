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

#ifndef __MID_POINT__
#define __MID_POINT__

#include <ap_int.h>

#define IMG_SIZE_W 256
#define IMG_SIZE_H 256

#define CHANNEL_SIZE  1  /* Black and White image */
#define DIMENSION_WORD_WIDTH 16

typedef ap_uint<CHANNEL_SIZE> interface_t;

void mid_point(interface_t img[IMG_SIZE_H][IMG_SIZE_W],
	       ap_int<DIMENSION_WORD_WIDTH> x_center, ap_int<DIMENSION_WORD_WIDTH> y_center,
	       ap_int<DIMENSION_WORD_WIDTH> radius);
#endif

