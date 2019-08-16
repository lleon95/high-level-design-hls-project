#ifndef __BRESENHAM__
#define __BRESENHAM__

#include <ap_int.h>

#define IMG_SIZE_W 256
#define IMG_SIZE_H 256

#define CHANNEL_SIZE  1  /* Black and White image */

typedef ap_uint<CHANNEL_SIZE> interface_t;

void bresenham(interface_t img[IMG_SIZE_H][IMG_SIZE_W],
		int x1, int y1, int x2, int y2);
#endif
