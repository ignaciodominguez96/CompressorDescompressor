#include "Descompressor.h"

#define SIZE_STRING_DOT_COMPR 6

#define FLAG_INDICATE_DIVISION 0
#define CANT_CHILDRENS_PER_DIVISION 4

#define ELEMENTS_IN_RGBA 4



enum offset { RED_OFFSET = 0, GREEN_OFFSET, BLUE_OFFSET, ALPHA_OFFSET};




//auxiliar functions

void draw_png(unsigned int width_, fsystem::ifstream& readFile, std::vector<unsigned int>& nVector, std::vector<unsigned char>& pngImage);

void print_code_RGBA(std::vector<unsigned int>& vector, unsigned int size, std::vector<unsigned char>& image_png, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

void get_correlation(unsigned int& correlation_x, unsigned int& correlation_y, std::vector<unsigned int>& vector, unsigned int size);



//



bool descompress(const char * path_image)
{
	bool can_descompress = false;

	std::vector<unsigned int> vect;
	std::vector<unsigned char> image_bmp;

	std::string image_filename(path_image);
	image_filename.resize(image_filename.size() - SIZE_STRING_DOT_COMPR);
	std::string extension = TYPE_OF_DESCOMPRESS_FILE;

	std::string image_new_filename(image_filename + extension); //creo el archivo

	fsystem::ifstream file_bmp(path_image, std::ios_base::in | std::ios_base::binary);

	//extraigo los primeros 4 bytes de la imagen
	unsigned int size;
	unsigned char length[4];

	for (int j = 0; j < 4; j++)			
	{									
		length[j] = file_bmp.get();
	}
	unsigned int * ptr = (unsigned int *)length;

	size = *ptr;

	image_bmp.resize((size_t)((size*size) * 4));

	draw_png(size, file_bmp, vect, image_bmp);

	unsigned error = lodepng::encode(image_new_filename, image_bmp, size, size);

	if (error == true)
	{
		std::cout << "DECODER LODE error " << error << ": " << lodepng_error_text(error) << std::endl;
		can_descompress = false;
	}

	return can_descompress;
}



void draw_png(unsigned int size, fsystem::ifstream& file_bmp, std::vector<unsigned int>& vector, std::vector<unsigned char>& image_png)
{
	char actual_char = 0;

	char red;
	char green;
	char blue;

	char alpha = 255;

	actual_char = file_bmp.get();


	while (!file_bmp.eof()) // se dibuja hasta llegar al eof
	{
		if ( (actual_char) == CHAR_INDICATE_DIVISION )
		{
			vector.push_back(FLAG_INDICATE_DIVISION); // image divide in  4 childrens
		}



		else if ( (actual_char) == CHAR_INDICATE_OK_AVERAGE) // image average
		{
			red		=	file_bmp.get();
			green	=	file_bmp.get();
			blue	=	file_bmp.get();


			bool is_one_cuadrant = vector.size() != 0; //mientras no este en el cuadrante original(size = 0) caso especial donde solo hay un cuadrante,

			if (is_one_cuadrant)
			{
				vector[ vector.size() - 1]++;	//incremento el contador de cuadrantes de el nivel donde que me encuentro
											
			}

			print_code_RGBA(vector, size, image_png, red, green, blue, alpha); // dibujo
			
			
			while ((is_one_cuadrant) && ((vector[ vector.size() - 1]  == CANT_CHILDRENS_PER_DIVISION)))	// si se dibujo los cuatro cuadrantes correspondientes a el cuadrado del nivel superior, borro la n
			{																							// correspondiente a ese cuadrado y paso al siguiente cuadrante, haci hasta que no sea cuatro el nivel actual
																					
																					
				vector.pop_back();	
				
				if (vector.size() != 0)
				{
					vector[vector.size() - 1 ]++;
				}
			}
		}

		actual_char = file_bmp.get();
	}
}

void print_code_RGBA(std::vector<unsigned int>& vector, unsigned int size, std::vector<unsigned char>& image_png, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	unsigned int correlation_x;
	unsigned int correlation_y;

	unsigned int actual_size = size / pow(2, vector.size());	// largo del cuadrado que voy a dibjar, calculado en base a el nivel en el que me encuentro
																
	get_correlation(correlation_x, correlation_y, vector, size); //busco el (0,0) relativo para ese cuadrante 

	unsigned int  max_index_i;
	unsigned int  max_index_j;


	max_index_i = correlation_x + (actual_size) * ELEMENTS_IN_RGBA; // limites en x e y para dibujar el cuadrado
	max_index_j = correlation_y + (actual_size);

	for (unsigned int i = correlation_x; i < max_index_i; i += ELEMENTS_IN_RGBA) //for que me dibuja el cuadrado correspondiente y agrega el alpha arbitrario
	{
		for (unsigned int j = correlation_y; j < max_index_j; j++)
		{
			image_png[i + j * (size * ELEMENTS_IN_RGBA) + RED_OFFSET   ] = red;
			image_png[i + j * (size * ELEMENTS_IN_RGBA) + GREEN_OFFSET ] = green;
			image_png[i + j * (size * ELEMENTS_IN_RGBA) + BLUE_OFFSET  ] = blue;
			image_png[i + j * (size * ELEMENTS_IN_RGBA) + ALPHA_OFFSET ] = alpha;
		}
	}
}

void get_correlation(unsigned int& correlation_x, unsigned int& correlation_y, std::vector<unsigned int>& vector, unsigned int size)
{
	correlation_x = 0;
	correlation_y = 0;

	for (int actual_level = 1; actual_level <= vector.size(); actual_level++) // va sumando los corrimientos para cad anivel hasta llegar al actual
	{
		unsigned int cuadrant_id;

		if (vector.size() == actual_level)
		{
			cuadrant_id = vector[actual_level - 1]; // para el cuadrante actual, el valor en n sera igual al cuadrante que debo dibujar
		}
		else
		{
			cuadrant_id = vector[actual_level - 1] + 1;	// para los niveles mas altos, por la estructura del programa, el valor n  sera igual al cuadrante que debo dibujar menos uno
		}	
			


				
		switch (cuadrant_id) // corriminetos correspondientes a cada cuadrante
		{
			case ID_CUADRANT1:
				break;
			case ID_CUADRANT2:
				correlation_x += (size / pow(2, actual_level)) * ELEMENTS_IN_RGBA;
				break;
			case ID_CUADRANT3:
				correlation_y += size / pow(2, actual_level);
				break;
			case ID_CUADRANT4:
				correlation_x += (size / pow(2, actual_level)) * ELEMENTS_IN_RGBA;
				correlation_y += size / pow(2, actual_level);
				break;
			}
	}
}
