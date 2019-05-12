#pragma once
#include <vector>
#include "ImageDescriptor.h"

#define IMAGES_PER_BOARD 9
#define BOTON_LEFT 0  //indices correspondientes al vector de botones.
#define BOTON_RIGHT 1
#define FIRST_IMG_OF_THIS_BOARD(boardActual) (IMAGES_PER_BOARD * boardActual)
#define LAST_IMG_OF_THIS_BOARD(boardActual) (IMAGES_PER_BOARD * (boardActual + 1))

class board
{
public:
	board(int width_, int height_, vector<ImageDescriptor> & images_, vector<ImageDescriptor> & botons_);// : images(images_), botons(botons_) {} //HAY QUE ARREGLARLO!
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
	int get_sizeX(void);
	int get_sizeY(void);
	int get_marginX(void);
	int get_marginY(void);
	int get_actual(void);
	int get_cant(void);
	bool images_error(void);
	
private:

	vector<ImageDescriptor> & images;
	vector<ImageDescriptor> & buttons;
	int image_sizeX; //tamaño de cada image
	int image_sizeY;
	int button_sizeX; //tamaño de los botones
	int button_sizeY;
	int marginX; //margenes
	int marginY;
	int width; //dimensiones del Board
	int height;
	int button_actual; // de cero a la cantidad de Boards -1
	int button_cant; // cantidad de Boards

	void change_board(int botonPressed_);
};

