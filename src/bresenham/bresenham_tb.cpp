#include <iostream>
#include <fstream>

#include "bresenham.hpp"

#define OUTPUT_FILE "/tmp/output.raw"

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

void init_array(interface_t img[IMG_SIZE_H][IMG_SIZE_W]) {
	for (int y = 0; y < IMG_SIZE_H; y++) {
		for (int x = 0; x < IMG_SIZE_W; x++) {
			img[y][x] = 0x0;
		}
	}
}

int main(int argc, char ** argv)
{
	/* Image buffer */
	interface_t img[IMG_SIZE_H][IMG_SIZE_W];
	init_array(img);

	/* Known point */
	int x1 = 100, y1 = 2, x2 = 200, y2 = 250;

	bresenham(img, x1, y1, x2, y2);

	/* Output */
	img_writer(img);
	return 0;
}
