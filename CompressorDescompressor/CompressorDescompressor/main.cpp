#pragma once

#include <iostream>
#include <vector>
#include <allegro5\allegro.h>

#include "SearchFile.h"
#include "Supervisor.h"
#include "Board.h"
#include "Image.h"
#include "Button.h"
#include "lodepng.h"
#include "Viewer.h"
#include "Parser.h"
#include "Definitions.h"


using namespace std;


int main(int argc, char* argv[])
{
	vector <string> images_path;
	userData_t userData;

	if (!parserCmd(argc, argv, userData))
	{
	}

	else if (!search_files_with_extension(images_path, userData.path.c_str(), TYPE_OF_DESCOMPRESS_FILE))
	{
		cout << "El path que ha pasado por parámetro es invalido, intente nuevamente" << endl;
		cout << "Recuerde que primero debe pasar un path valido, donde haya imagenes" << TYPE_OF_DESCOMPRESS_FILE << endl;
		cout << "Luego, seguido de un espacio debe pasar el threshold, que es un numero entre" << MIN_THRESHOLD << " y " << MAX_THRESHOLD << endl;
		
		cout << userData.path.c_str() << endl;
		
		al_rest(5.0);
	}
	else if (((int)images_path.size()) == 0)
	{
		cout << "No existe ninguna imagen" << TYPE_OF_DESCOMPRESS_FILE << " en el directorio pasado por parametro" << endl;
		cout << "asegurese que la carpeta tenga imagenes, o de estar pasando bien el path" << endl;
		return ERROR;
	}
	else
	{
		if (!al_init())
		{
			cout << "Allegro Failed to initialize" << endl;
		}
		else
		{
			viewer * view = &viewer(MODE_COMPRESSOR);

			vector<ImageDescriptor> images;
			vector<ImageDescriptor> buttons;

			for (int i = 0; i < ((int)images_path.size()); i++)
			{
				ImageDescriptor image(images_path[i].c_str()); //init de todas las imagenes
				images.push_back(image);
			}

			
			ImageDescriptor button_left("../EDA-TP8/botones/boton_left.png"); //init de los botones
			ImageDescriptor button_right("../EDA-TP8/botones/boton_right.png");
			
			buttons.push_back(button_left); 
			buttons.push_back(button_right);

			board * boar = &board(WIDTH_DEFAULT, HEIGHT_DEFAULT, images, buttons);
			
			if (boar->is_images_error())
			{
				cout << "Image initialization Failed" << endl;
				al_rest(1.0);
				return ERROR;
			}

			boar->set_image_size(IMAGE_SIZE_X, IMAGE_SIZE_Y); 
														   
			boar->refresh();

			view->update_display(*boar);

			al_set_target_backbuffer(view->get_display());

			al_flip_display();

			if (!(view->is_init))
			{
				cout << "Viewer Failed to initialize." << endl;
				return -1;
			}
			
			supervisor * superv = &supervisor(*view, userData.threshold);
			
			while (!(superv->is_finish))
			{
				superv->dispatcher(*view, *boar);
			}

			images.erase(images.begin());
			buttons.erase(buttons.begin());
		}
	}

	return 0;
}


