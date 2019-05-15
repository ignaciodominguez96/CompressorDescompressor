#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include "ImageDescriptor.h"
#include "lodepng.h"
#include <iostream>

class image: public ImageDescriptor
{
public:
	image() {

	}

	~image()
	{

	}

	/*Compress image*/
	/*Returns 1 if failed*/
	bool compress(unsigned int puntajeDif);

	/*Decompress image*/
	/*Returns 1 if failed*/
	bool decompress(void);

private:
	
	std::vector<unsigned char> decode(const char* filename);
	unsigned int get_max(std::vector<unsigned char> pixels, unsigned int type, unsigned int max, unsigned int min);
	unsigned int get_min(std::vector<unsigned char> pixels, unsigned int type, unsigned int max, unsigned int min);

};





#endif // !IMAGE_H








