#include "Descompressor.h"

#define SIZE_STRING_DOT_COMPR 6

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "lodepng.h"

#define ERROR -1
#define MIDDLE_X(x1,x2) (((x1)+(x2))/2)
#define MIDDLE_Y(y1,y2) (((y1)+(y2))/2)

#define LEFT_X(x1,x2)	((x1))
#define RIGHT_X(x1,x2)	((x2))

#define TOP_Y(y1,y2)	((y1))
#define BOTTOM_Y(y1,y2)	((y2))

bool decompress_recursion(unsigned char * image_arrey, unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, FILE *image_file, uint32_t image_width, uint32_t image_height);
void draw_pixels(unsigned char * image_arrey, unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, uint32_t w_size, unsigned char red, unsigned char green, unsigned char blue);
int f_size(FILE *source_file, void *dest, size_t num_bytes);


bool descompress(const char *path_image)
{
	
	std::string image_filename(path_image);
	image_filename.resize(image_filename.size() - SIZE_STRING_DOT_COMPR);
	std::string extension = TYPE_OF_DESCOMPRESS_FILE;

	std::string image_new_filename(image_filename + extension); //creo el archivo

	fsystem::ifstream file_bmp(path_image, std::ios_base::in | std::ios_base::binary);


	unsigned char * image_array = NULL; //definimos el arreglo imagen en NULL
	uint32_t width, height;
	FILE *image_file;

	image_file = fopen(path_image, "rb+");
	if (image_file == NULL)
	{
		perror("ERROR");
		return false; 
	}
	
	if (f_size(image_file, &width, sizeof(uint32_t)) < sizeof(uint32_t))
		return false; 

	if (f_size(image_file, &height, sizeof(uint32_t)) < sizeof(uint32_t))
		return false; 

	
	image_array = (unsigned char *) malloc(width*height * 4 * sizeof(unsigned char));

	if (decompress_recursion(image_array, 0, 0, width, height, image_file, width, height))
	{
		
		lodepng_encode32_file(image_new_filename.c_str(), image_array, width, height);
		free(image_array); 
		return true;
	}
	else
		return false;
}


bool decompress_recursion(unsigned char * image_arrey, unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, FILE *image_file, uint32_t image_width, uint32_t image_height)
{
	unsigned char character, red, green, blue;
	bool ret = false;

	
	character = fgetc(image_file);
	if (character == CHAR_INDICATE_OK_AVERAGE)
	{
		red = fgetc(image_file); 
		green = fgetc(image_file); 
		blue = fgetc(image_file); 
		draw_pixels(image_arrey, X1, Y1, X2, Y2, image_width, red, green, blue); 
		
	}
	else if (character == CHAR_INDICATE_DIVISION)
	{
		if (decompress_recursion(image_arrey, LEFT_X(X1, X2), TOP_Y(Y1, Y2), MIDDLE_X(X1, X2), MIDDLE_Y(Y1, Y2), image_file, image_width, image_height) == false);
		else if (decompress_recursion(image_arrey, MIDDLE_X(X1, X2), TOP_Y(Y1, Y2), RIGHT_X(X1, X2), MIDDLE_Y(Y1, Y2), image_file, image_width, image_height) == false);
		else if (decompress_recursion(image_arrey, LEFT_X(X1, X2), MIDDLE_Y(Y1, Y2), MIDDLE_X(X1, X2), BOTTOM_Y(Y1, Y2), image_file, image_width, image_height) == false);
		else if (decompress_recursion(image_arrey, MIDDLE_X(X1, X2), MIDDLE_Y(Y1, Y2), RIGHT_X(X1, X2), BOTTOM_Y(Y1, Y2), image_file, image_width, image_height) == false);
		else ret = true;
	}
	ret = true;
	return ret;
}

void draw_pixels(unsigned char * image_arrey, unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, uint32_t w_size, unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int  counter_row, counter_column;
	for (counter_row = Y1; counter_row < Y2; counter_row++)
		for (counter_column = X1; counter_column < X2; counter_column++)
		{
			image_arrey[((counter_column * 4) + (4 * w_size*counter_row)) + 0] = red; 
			image_arrey[((counter_column * 4) + (4 * w_size*counter_row)) + 1] = green; 
			image_arrey[((counter_column * 4) + (4 * w_size*counter_row)) + 2] = blue; 
			image_arrey[((counter_column * 4) + (4 * w_size*counter_row)) + 3] = 0xff; 
		}
}

int f_size(FILE *source_file, void *dest, size_t num_bytes)
{
	int bytes_leidos;
	unsigned int char_leido;

	if (source_file == NULL || dest == NULL)
		bytes_leidos = ERROR;
	else
		for (bytes_leidos = 0; bytes_leidos < num_bytes; bytes_leidos++)
			if ((char_leido = fgetc(source_file)) == EOF)
				break;
			else
				((char*)dest)[bytes_leidos] = char_leido;

	return bytes_leidos;
}
