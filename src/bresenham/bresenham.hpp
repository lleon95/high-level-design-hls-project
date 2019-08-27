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

#ifndef __BRESENHAM__
#define __BRESENHAM__

#include <ap_int.h>

#define IMG_SIZE_W 256
#define IMG_SIZE_H 256

#define CHANNEL_SIZE  1  /* Black and White image */
#define DIMENSION_WORD_WIDTH 16

typedef ap_uint<CHANNEL_SIZE> interface_t;

void bresenham(interface_t img[IMG_SIZE_H][IMG_SIZE_W],
		ap_int<DIMENSION_WORD_WIDTH> x1, ap_int<DIMENSION_WORD_WIDTH> y1,
		ap_int<DIMENSION_WORD_WIDTH> x2, ap_int<DIMENSION_WORD_WIDTH> y2);
#endif

