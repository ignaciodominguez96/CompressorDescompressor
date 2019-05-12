#pragma once

#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Button.h"
#include "Images.h"

#define MAX_IMAGES_IN_THE_BOARD 9

#define BOTON_LEFT 0  //indices correspondientes al vector de botones.
#define BOTON_RIGHT 1

#define FIRST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * button_actual)
#define LAST_IMAGE_BOARD(button_actual) (MAX_IMAGES_IN_THE_BOARD * (button_actual + 1))

class board
{
	public:
		board(int width, int height, vector<images> & images, vector<button> & buttons);
		~board();
		void refresh(void);
		void touch(int x, int y);
		void select_all_images(void);
		void unselect_all_images(void);
		bool is_some_image_select(void);
		void set_image_size(int sizeX_, int sizeY_);
		void set_boton_size(int botonSizeX, int botonSizeY);
		vector <ImageDescriptor> & get_images(void);
		vector <ImageDescriptor> & get_buttons(void);
		int get_size_x(void);
		int get_size_y(void);
		int get_margin_x(void);
		int get_margin_y(void);
		int get_actual(void);
		int get_cant(void);
		bool images_error(void);

	private:

		vector<images> & images;
		vector<button> & buttons;
		int image_size_x; //tamaño de cada image
		int image_size_y;
		int button_size_x; //tamaño de los botones
		int button_size_y;
		int margin_x; //margenes
		int margin_y;
		int width; //dimensiones del damero
		int height;
		int button_actual; // de cero a la cantidad de dameros -1
		int button_cant; // cantidad de dameros

		void change_board(int button_pressed);
};




#endif // !BOARD_H

