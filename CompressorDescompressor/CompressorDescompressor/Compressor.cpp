#include "Compressor.h"
#include "Cuadrant.h"

#define MAX_THRESHOLD (255*3)
#define SIZE_STRING_DOT_PNG 4
#define NEW_SIZE_IN_BYTES	4


#define SKIP_BITS 3






//auxiliar functions

void algorithm_compression_quad_tree(unsigned int threshold_compression, fsystem::ofstream & text, std::vector<unsigned char>& image_to_compress, unsigned int size_image);

bool fill_cuadrant(std::vector<unsigned char>& original_image, unsigned int original_size, std::vector<unsigned char>& cuadrant, unsigned int id_cuadrant);

//


bool compress(unsigned int threshold_compression, const char * path_image, unsigned int image_width, unsigned int image_height) 
{

	bool can_compress = false;

	std::vector<unsigned char> image_aux; 

	//como vamos a usar el algoritmo de compresion quad tree, se tiene que verificar las condiciones para usarlo (imagen cuadrada) y de tamaño 2^n
	//ademas, aceptamos un threshold maximo de 3*255

	if ((image_width == image_height) && (threshold_compression <= MAX_THRESHOLD) )
	{

		char size_image_char = (char) image_width; // = image_height
		unsigned int size_image_uint = image_width; // = image_height

		unsigned error_decode = lodepng::decode(image_aux, image_width, image_height, path_image);
		
		if (error_decode == false)
		{

			std::string image_filename(path_image);

			image_filename.resize(image_filename.size() - SIZE_STRING_DOT_PNG); //remuevo el ".png" del nombre

			std::string extension_compress_file = TYPE_OF_COMPRESS_FILE;



			std::string name_of_new_file_compress = image_filename + extension_compress_file;

			fsystem::ifstream new_file_r(name_of_new_file_compress); //creo el archivo

			new_file_r.close();



			fsystem::ofstream new_file_w(name_of_new_file_compress); 

			char * ptr_size_file =  &size_image_char;

			for (int i = 0; i < NEW_SIZE_IN_BYTES; i++) //escribo el largo de la imagenen  NEW_SIZE_IN_BYTES bytes
			{
				new_file_w.put(*(ptr_size_file + i));
			}


			algorithm_compression_quad_tree(threshold_compression, new_file_w, image_aux, size_image_uint);

			can_compress = true;
		} 


		
	}

	return can_compress;

}

void algorithm_compression_quad_tree(unsigned int threshold_compression, fsystem::ofstream & text, std::vector<unsigned char>& image_to_compress, unsigned int size_image)
{
	
	cuadrant * cuadrant_aux = &cuadrant();
	
	cuadrant_aux->set_min_max_image_RGB_skip(image_to_compress, SKIP_BITS);

	cuadrant_aux->uptdate_score();

	unsigned int score = cuadrant_aux->get_score();

	if (score > threshold_compression) 
	{
		std::vector<unsigned char> cuadrant1 (size_image * size_image, 0); // el size del nuevo cuadrante es los lados al cuadrado por 4 bytes cada pixel dividido 4
		std::vector<unsigned char> cuadrant2 (size_image * size_image, 0);
		std::vector<unsigned char> cuadrant3 (size_image * size_image, 0);
		std::vector<unsigned char> cuadrant4 (size_image * size_image, 0);
		
		fill_cuadrant(image_to_compress, size_image, cuadrant1, ID_CUADRANT1);
		fill_cuadrant(image_to_compress, size_image, cuadrant3, ID_CUADRANT2);
		fill_cuadrant(image_to_compress, size_image, cuadrant3, ID_CUADRANT3);
		fill_cuadrant(image_to_compress, size_image, cuadrant4, ID_CUADRANT4);

		text.put(CHAR_INDICATE_DIVISION);
		
		//division en 4 hijos

		unsigned int new_size_childrens = (size_image / 2);
		

		algorithm_compression_quad_tree(threshold_compression, text, cuadrant1, new_size_childrens);
		algorithm_compression_quad_tree(threshold_compression, text, cuadrant2, new_size_childrens);
		algorithm_compression_quad_tree(threshold_compression, text, cuadrant3, new_size_childrens);
		algorithm_compression_quad_tree(threshold_compression, text, cuadrant4, new_size_childrens);


	}
	else 
	{
		text.put(CHAR_INDICATE_OK_AVERAGE);

		char red_average = (char)(cuadrant_aux->get_red_avg());
		char green_average = (char)(cuadrant_aux->get_green_avg());
		char blue_average = (char)(cuadrant_aux->get_blue_avg());

		text.put(red_average); 
		text.put(green_average);
		text.put(blue_average);


	}
}

bool fill_cuadrant(std::vector<unsigned char>& original_image, unsigned int original_size, std::vector<unsigned char>& cuadrant, unsigned int id_cuadrant)
{
	bool all_ok = true;

	unsigned int index_i_init;
	unsigned int index_i_finish;
	
	unsigned int index_j_init;
	unsigned int index_j_finish;
	
	switch (id_cuadrant)
	{
		case ID_CUADRANT1:

			index_i_init = 0;
			index_i_finish = (original_size * 2);


			index_j_init = 0;
			index_j_finish = (original_size / 2);

			break;



		case ID_CUADRANT2:

			index_i_init = (original_size * 2);
			index_i_finish = (original_size * 4);


			index_j_init = 0;
			index_j_finish = (original_size / 2);


			break;



		case ID_CUADRANT3:

			index_i_init = 0;
			index_i_finish = (original_size * 2);


			index_j_init = (original_size / 2);;
			index_j_finish = (original_size);

			break;



		case ID_CUADRANT4:


			index_i_init = (original_size * 2);
			index_i_finish = (original_size * 4);


			index_j_init = (original_size / 2);
			index_j_finish = (original_size);



			break;


		default: //introdujeron un cuadrante inexistente
			all_ok = false;
			break;
		}


	for (unsigned int i = index_i_init, k = 0; i < index_i_finish; i++, k++)
	{
		for (unsigned int j = index_j_init, l = 0; j < index_j_finish; j++, l++)
		{
			cuadrant[k + l * (original_size * 2)] = original_image[i + j * (original_size * 4)];
		}
	}


	return all_ok;
}