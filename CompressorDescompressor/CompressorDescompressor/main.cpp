#pragma once

#include <iostream>
#include <vector>
#include <allegro5\allegro.h>

#include "SearchFile.h"
#include "Supervisor.h"
#include "Board.h"
#include "lodepng.h"
#include "Viewer.h"
#include "Parser.h"
#include "Definitions.h"


#define TIME_TO_SEE_MSSG_ERROR 5.0

using namespace std;


int main(int argc, char* argv[])
{
	vector <string> files_path;
	userData_t userData;
	int all_ok = OK;

	if (parserCmd(argc, argv, userData) == true)
	{
		if (userData.mode == MODE_COMPRESSOR)
		{
			if (search_files_with_extension(files_path, userData.path.c_str(), TYPE_OF_DESCOMPRESS_FILE) == false)
			{
				cout << "El path que ha pasado por par�metro es invalido, intente nuevamente" << endl;
				cout << "Recuerde que primero debe pasar un path valido, donde haya imagenes" << TYPE_OF_DESCOMPRESS_FILE << endl;
				cout << "Luego, seguido de un espacio debe pasar el threshold, que es un numero entre" << MIN_THRESHOLD_PORC  << " y " << MAX_THRESHOLD_PORC << endl;

			}
			else if (((int)files_path.size()) == 0)
			{
				cout << "No existe ninguna imagen" << TYPE_OF_DESCOMPRESS_FILE << " en el directorio pasado por parametro" << endl;
				cout << "asegurese que la carpeta tenga imagenes, o de estar pasando bien el path" << endl;
				all_ok = ERROR;
			}
			
		}
		else if (userData.mode == MODE_DESCOMPRESSOR)
		{
			if (search_files_with_extension(files_path, userData.path.c_str(), TYPE_OF_COMPRESS_FILE) == false)
			{
				cout << "el path que ha pasado por par�metro es invalido, intente nuevamente" << endl;
				cout << "recuerde debe pasar un path valido, donde haya archivos " << TYPE_OF_COMPRESS_FILE << endl;
			}
			else if (((int)files_path.size()) == 0)
			{
				cout << "No existe ningun archivo " << TYPE_OF_COMPRESS_FILE << " en el directorio pasado por parametro" << endl;
				cout << "asegurese que la carpeta tenga archivos listos para descomprimir, o de estar pasando bien el path" << endl;
				all_ok = ERROR;
			}
		}

		
		if (!al_init())
		{
			cout << "Allegro Failed to initialize" << endl;
		}
		else
		{

			viewer view(userData.mode);

			vector<ImageDescriptor> images;
			vector<ImageDescriptor> buttons;

			for (int i = 0; i < ((int)files_path.size()); i++)
			{
				if (userData.mode == MODE_COMPRESSOR)
				{
					ImageDescriptor image(files_path[i].c_str()); //init de todas las imagenes
					images.push_back(image);
				}
				else if (userData.mode == MODE_DESCOMPRESSOR)
				{
					ImageDescriptor image(files_path[i].c_str(), FLAG_NO_IMAGE_DESCOMPR); //init de imagenes descompress
					images.push_back(image);
				}
								
			}

		

			ImageDescriptor button_left(PATH_BUTTON_LEFT); //init de los botones
			ImageDescriptor button_right(PATH_BUTTON_RIGHT);

			buttons.push_back(button_left);
			buttons.push_back(button_right);

			board boar(WIDTH_DEFAULT, HEIGHT_DEFAULT, images);

			if (boar.is_images_error())
			{
				cout << "Image initialization Failed" << endl;
				all_ok = ERROR;
			}

			boar.set_image_size(IMAGE_SIZE_X, IMAGE_SIZE_Y);

			boar.refresh();

			view.update_display(boar);

			al_set_target_backbuffer(view.get_display());

			al_flip_display();

			if (!(view.is_init()))
			{
				cout << "Viewer Failed to initialize" << endl;
				all_ok = ERROR;
			}

			supervisor superv(view, userData.threshold);

			while (!(superv.is_finish()))
			{
				superv.dispatcher(view, boar);
			}

			images.erase(images.begin());
			buttons.erase(buttons.begin());
		}

	}

	else
	{
		cout << "Error parseando";
		all_ok = ERROR;
		
	}

	if (all_ok == ERROR)
	{
		al_rest(TIME_TO_SEE_MSSG_ERROR);
	}


	return all_ok;
}


