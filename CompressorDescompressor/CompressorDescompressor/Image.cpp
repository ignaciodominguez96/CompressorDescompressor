#include "Image.h"

struct cuadrant { //each cuadrant has it minimum and maximum for each color
	unsigned int minR = 255, maxR = 0, minG = 255, maxG = 0, minB = 255, maxB = 0; //we initialize the maximums as 0 and the minimums as 255
	int puntaje;
};

enum types { RED = 1, GREEN, BLUE, ALPHA }; //simple enumeration

/*Compress image*/
bool image::compress(unsigned int puntajeDif) {
	std::vector<unsigned char> pixels = decode(get_path()); //decoding image to pixel vector
	std::vector<unsigned char> subpixels = pixels; //vector with cuadrants
	unsigned int w = get_width(); //getting size
	unsigned int h = get_heigth();
	unsigned int times = 0;
	
	analize_cuad(w, h, pixels, puntajeDif, times); //always start times in 0

}

void analize_cuad(unsigned int w, unsigned int h, std::vector<unsigned char> pixels,unsigned int puntajeDif, unsigned int times) {
	cuadrant c1, c2, c3, c4;
	std::vector<unsigned char> subpixels;
	c1.puntaje = copy_q1(c1, w, h, pixels, subpixels); //copying first cuadrant from pixels to subpixels
	if (c1.puntaje > puntajeDif) { //we have to analize again
		analize_cuad(w / 2, h / 2, subpixels, puntajeDif, times + 1); //calling this function with half the hight and width and incrementing times
	}
	c2.puntaje = copy_q2(c2, w, h, pixels, subpixels); //copying second cuadrant from pixels to subpixels
	if (c2.puntaje > puntajeDif) { //we have to analize again
		analize_cuad(w / 2, h / 2, subpixels, puntajeDif, times + 1); //calling this function with half the hight and width and incrementing times
	}
	c3.puntaje = copy_q3(c3, w, h, pixels, subpixels); //copying third cuadrant from pixels to subpixels
	if (c3.puntaje > puntajeDif) { //we have to analize again
		analize_cuad(w / 2, h / 2, subpixels, puntajeDif, times + 1); //calling this function with half the hight and width and incrementing times
	}
	c4.puntaje = copy_q4(c1, w, h, pixels, subpixels); //copying fourth cuadrant from pixels to subpixels
	if (c1.puntaje > puntajeDif) { //we have to analize again
		analize_cuad(w / 2, h / 2, subpixels, puntajeDif, times + 1); //calling this function with half the hight and width and incrementing times
	}

	/*Create node*/
	//aca hay que crear el nodo
}


unsigned int copy_q1(cuadrant c1, unsigned int w, unsigned int h, std::vector<unsigned char> pixels, std::vector<unsigned char> subpixels) {
	int k = 0;

	for (int j = 0; j < h / 2; j++) { //we copy from the start to the half (vertically)
		for (int i = w / 2; i < w; i++) { //we copy from the half to the end (horizontally)
			for (int l = RED; l <= ALPHA; l++) {
				subpixels[k] = pixels[j*h*ALPHA + i * ALPHA + l]; //we move in rows (j*h) and then in items in that row (+i) and then in bytes in that item
				k++;
			}
		}
	}

	/*Now we evaluate the score*/
	c1.minR = get_min(subpixels, RED, 0, w*h);
	c1.maxR = get_max(subpixels, RED, 0, w*h);
	c1.minG = get_min(subpixels, GREEN, 0, w*h);
	c1.maxG = get_max(subpixels, GREEN, 0, w*h);
	c1.minB = get_min(subpixels, BLUE, 0, w*h);
	c1.maxB = get_max(subpixels, BLUE, 0, w*h);

	c1.puntaje = c1.maxR - c1.minR + c1.maxG - c1.minG + c1.maxB - c1.minB;
	return c1.puntaje;
}

unsigned int copy_q2(cuadrant c2, unsigned int w, unsigned int h, std::vector<unsigned char> pixels, std::vector<unsigned char> subpixels) {
	int k = 0;

	for (int j = 0; j < h / 2; j++) { //we copy from the start to the half (vertically)
		for (int i = 0; i < w / 2; i++) { //we copy from the start to the half (horizontally)
			for (int l = RED; l <= ALPHA; l++) {
				subpixels[k] = pixels[j*h*ALPHA + i * ALPHA + l]; //we move in rows (j*h) and then in items in that row (+i) and then in bytes in that item
				k++;
			}
		}
	}

	/*Now we evaluate the score*/
	c2.minR = get_min(subpixels, RED, 0, w*h);
	c2.maxR = get_max(subpixels, RED, 0, w*h);
	c2.minG = get_min(subpixels, GREEN, 0, w*h);
	c2.maxG = get_max(subpixels, GREEN, 0, w*h);
	c2.minB = get_min(subpixels, BLUE, 0, w*h);
	c2.maxB = get_max(subpixels, BLUE, 0, w*h);

	c2.puntaje = c2.maxR - c2.minR + c2.maxG - c2.minG + c2.maxB - c2.minB;
	return c2.puntaje;
}

unsigned int copy_q3(cuadrant c3, unsigned int w, unsigned int h, std::vector<unsigned char> pixels, std::vector<unsigned char> subpixels) {
	int k = 0;

	for (int j = h / 2; j < h; j++) { //we copy from the half to the end (vertically)
		for (int i = 0; i < w / 2; i++) { //we copy from the start to the half (horizontally)
			for (int l = RED; l <= ALPHA; l++) {
				subpixels[k] = pixels[j*h*ALPHA + i * ALPHA + l]; //we move in rows (j*h) and then in items in that row (+i) and then in bytes in that item
				k++;
			}
		}
	}

	/*Now we evaluate the score*/
	c3.minR = get_min(subpixels, RED, 0, w*h);
	c3.maxR = get_max(subpixels, RED, 0, w*h);
	c3.minG = get_min(subpixels, GREEN, 0, w*h);
	c3.maxG = get_max(subpixels, GREEN, 0, w*h);
	c3.minB = get_min(subpixels, BLUE, 0, w*h);
	c3.maxB = get_max(subpixels, BLUE, 0, w*h);

	c3.puntaje = c3.maxR - c3.minR + c3.maxG - c3.minG + c3.maxB - c3.minB;
	return c3.puntaje;
}

unsigned int copy_q4(cuadrant c4, unsigned int w, unsigned int h, std::vector<unsigned char> pixels, std::vector<unsigned char> subpixels) {
	int k = 0;

	for (int j = h / 2; j < h ; j++) { //we copy from the half to the end (vertically)
		for (int i = w / 2; i < w; i++) { //we copy from the half to the end (horizontally)
			for (int l = RED; l <= ALPHA; l++) {
				subpixels[k] = pixels[j*h*ALPHA + i * ALPHA + l]; //we move in rows (j*h) and then in items in that row (+i) and then in bytes in that item
				k++;
			}
		}
	}

	/*Now we evaluate the score*/
	c4.minR = get_min(subpixels, RED, 0, w*h);
	c4.maxR = get_max(subpixels, RED, 0, w*h);
	c4.minG = get_min(subpixels, GREEN, 0, w*h);
	c4.maxG = get_max(subpixels, GREEN, 0, w*h);
	c4.minB = get_min(subpixels, BLUE, 0, w*h);
	c4.maxB = get_max(subpixels, BLUE, 0, w*h);

	c4.puntaje = c4.maxR - c4.minR + c4.maxG - c4.minG + c4.maxB - c4.minB;
	return c4.puntaje;
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