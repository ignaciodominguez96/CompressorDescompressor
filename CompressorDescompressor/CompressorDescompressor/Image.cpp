#include "Image.h"

struct cuadrant { //each cuadrant has it minimum and maximum for each color
	unsigned int minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0; //we initialize the maximums as 0 and the minimums as 255
	int puntaje;
};

enum types { RED = 1, GREEN, BLUE, ALPHA }; //simple enumeration

/*Compress image*/
bool image::compress(unsigned int puntajeDif) { 
	std::vector<unsigned char> pixels = decode(get_path()); //decoding image to pixel vector
	unsigned int w = get_width(); //getting size
	unsigned int h = get_heigth();
	cuadrant c1, c2, c3, c4; //creating cuadrants

	//analizing first cuadrant
	for (int j = 0; j < h / 2; j++) { //analizing each row (from row cero to the middle)
		if (get_max(pixels, RED, j * w + w / 2, j * w + w) > c1.maxR) // (j * w) we get the row, then we add half a row so we are in the middle
			c1.maxR = get_max(pixels, RED, j * w + w / 2, j * w + w); //analizing each pixel from the middle to the end
		if (get_min(pixels, RED, j * w + w / 2, j * w + w) < c1.minR)
		c1.minR = get_min(pixels, RED, j * w + w / 2, j * w + w);

		if (get_max(pixels, GREEN, j * w + w / 2, j * w + w) > c1.maxG)
			c1.maxG = get_max(pixels, GREEN, j * w + w / 2, j * w + w);
		if (get_min(pixels, GREEN, j * w + w / 2, j * w + w) < c1.minG)
			c1.minG = get_min(pixels, GREEN, j * w + w / 2, j * w + w);

		if (get_max(pixels, BLUE, j * w + w / 2, j * w + w) > c1.maxB)
			c1.maxB = get_max(pixels, BLUE, j * w + w / 2, j * w + w);
		if (get_min(pixels, BLUE, j * w + w / 2, j * w + w) < c1.minB)
			c1.minB = get_min(pixels, BLUE, j * w + w / 2, j * w + w);

	}
	c1.puntaje = c1.maxR - c1.minR + c1.maxG - c1.minG + c1.maxB - c1.minB;

	//analizing second cuadrant
	for (int j = 0; j < h / 2; j++) { //analizing each row (from row cero to the middle)
		if (get_max(pixels, RED, j * w, j * w + w / 2) > c2.maxR) // (j * w) we get the row, and its till the half
			c2.maxR = get_max(pixels, RED, j * w, j * w + w / 2); //analizing each pixel from the middle to the end
		if (get_min(pixels, RED, j * w, j * w + w / 2) < c2.minR)
			c2.minR = get_min(pixels, RED, j * w, j * w + w / 2);

		if (get_max(pixels, GREEN, j * w, j * w + w / 2) > c2.maxG)
			c2.maxG = get_max(pixels, GREEN, j * w, j * w + w / 2);
		if (get_min(pixels, GREEN, j * w, j * w + w / 2) < c2.minG)
			c2.minG = get_min(pixels, GREEN, j * w, j * w + w / 2);

		if (get_max(pixels, BLUE, j * w, j * w + w / 2) > c2.maxB)
			c2.maxB = get_max(pixels, BLUE, j * w, j * w + w / 2);
		if (get_min(pixels, BLUE, j * w, j * w + w / 2) < c2.minB)
			c2.minB = get_min(pixels, BLUE, j * w, j * w + w / 2);

	}
	c2.puntaje = c2.maxR - c2.minR + c2.maxG - c2.minG + c2.maxB - c2.minB;


	/*esto lo termino luego*/
	//analizing third cuadrant
	for (int j = 0; j < h / 2; j++) { //analizing each row (from row cero to the middle)
		if (get_max(pixels, RED, j * w + w / 2, j * w + w) > c3.maxR) // (j * w) we get the row, then we add half a row so we are in the middle
			c3.maxR = get_max(pixels, RED, j * w + w / 2, j * w + w); //analizing each pixel from the middle to the end
		if (get_min(pixels, RED, j * w + w / 2, j * w + w) < c3.minR)
			c3.minR = get_min(pixels, RED, j * w + w / 2, j * w + w);

		if (get_max(pixels, GREEN, j * w + w / 2, j * w + w) > c3.maxG)
			c3.maxG = get_max(pixels, GREEN, j * w + w / 2, j * w + w);
		if (get_min(pixels, GREEN, j * w + w / 2, j * w + w) < c3.minG)
			c3.minG = get_min(pixels, GREEN, j * w + w / 2, j * w + w);

		if (get_max(pixels, BLUE, j * w + w / 2, j * w + w) > c3.maxB)
			c3.maxB = get_max(pixels, BLUE, j * w + w / 2, j * w + w);
		if (get_min(pixels, BLUE, j * w + w / 2, j * w + w) < c3.minB)
			c3.minB = get_min(pixels, BLUE, j * w + w / 2, j * w + w);

	}
	c3.puntaje = c3.maxR - c3.minR + c3.maxG - c3.minG + c3.maxB - c3.minB;

	//analizing fourth cuadrant
	for (int j = 0; j < h / 2; j++) { //analizing each row (from row cero to the middle)
		if (get_max(pixels, RED, j * w + w / 2, j * w + w) > c4.maxR) // (j * w) we get the row, then we add half a row so we are in the middle
			c4.maxR = get_max(pixels, RED, j * w + w / 2, j * w + w); //analizing each pixel from the middle to the end
		if (get_min(pixels, RED, j * w + w / 2, j * w + w) < c4.minR)
			c4.minR = get_min(pixels, RED, j * w + w / 2, j * w + w);

		if (get_max(pixels, GREEN, j * w + w / 2, j * w + w) > c4.maxG)
			c4.maxG = get_max(pixels, GREEN, j * w + w / 2, j * w + w);
		if (get_min(pixels, GREEN, j * w + w / 2, j * w + w) < c4.minG)
			c4.minG = get_min(pixels, GREEN, j * w + w / 2, j * w + w);

		if (get_max(pixels, BLUE, j * w + w / 2, j * w + w) > c4.maxB)
			c4.maxB = get_max(pixels, BLUE, j * w + w / 2, j * w + w);
		if (get_min(pixels, BLUE, j * w + w / 2, j * w + w) < c4.minB)
			c4.minB = get_min(pixels, BLUE, j * w + w / 2, j * w + w);

	}
	c4.puntaje = c4.maxR - c4.minR + c4.maxG - c4.minG + c4.maxB - c4.minB;
	

}

/*Decompress image*/
bool image::decompress() {

}

//Decode from disk to raw pixels with a single function call
std::vector<unsigned char> decode(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	return image;
}

unsigned int get_max(std::vector<unsigned char> pixels, unsigned int type, unsigned int min, unsigned int max) {

	unsigned int maximum = 0;

	switch (type) {
	case RED:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i] > maximum) //if it is greater than the greatest, we found the new greatest
				maximum = pixels[ALPHA*i];
		}
		break;
	case GREEN:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i + 1] > maximum) //we add one because we want the second byte of the vector
				maximum = pixels[ALPHA*i + 1];
		}
		break;
	case BLUE:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i + 2] > maximum)
				maximum = pixels[ALPHA*i + 2];
		}
		break;
	default:
		break;
	}

	return maximum;

}

unsigned int get_min(std::vector<unsigned char> pixels, unsigned int type, unsigned int min, unsigned int max) {

	unsigned int minimum = 255;

	switch (type) {
	case RED:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i] < minimum) //if it is smaller than the smallest, we found the new smallest
				minimum = pixels[ALPHA*i];
		}
		break;
	case GREEN:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i + 1] < minimum) //we add one because we want the second byte of the vector
				minimum = pixels[ALPHA*i + 1];
		}
		break;
	case BLUE:
		for (int i = min; i < max; i++) {
			if (pixels[ALPHA*i + 2] < minimum)
				minimum = pixels[ALPHA*i + 2];
		}
		break;
	default:
		break;
	}

	return minimum;
}