#pragma once

#ifndef VIEWER_H
#define VIEWER_H

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_primitives.h>

#include "Images.h"
#include "Board.h"


#define UNIT 1

#define WIDTH_DEFAULT 1000
#define HEIGHT_DEFAULT 600
#define FONT_SIZE_DEFAULT 15


#define MODE_COMPRESSOR		0
#define MODE_DESCOMPRESSOR	1


class viewer //Se ocupa de todo lo relacionado con el output de la simulacion
{
public:
	viewer(unsigned int width = WIDTH_DEFAULT, unsigned int height = HEIGHT_DEFAULT, double font_size = FONT_SIZE_DEFAULT, unsigned int mode);
	~viewer();
	bool is_init(void);					 //listo
	void update_display(board & board); //listo
	ALLEGRO_DISPLAY* get_display(void);
	void print_message(char * mesagge);

private:

	unsigned int mode;
	unsigned int height;
	unsigned int width;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	double font_size;
	bool is_init_bool;

	//datos miembros para descompressor
	ALLEGRO_BITMAP * image_descompressor;
	bool error_descompressor_image; 


	//private methods
	bool init_allegro_elements(const char* path_background, const char* font_path);
	void print_board(board& board); //falta definir
	void draw_marker(double x, double y, double sizeX, double sizeY); //dibuja el marco alrededor de una imagen seleccionada
																	//recibe la esquina superior izquierda de la imagen y el tamano de la misma




};


#endif // !VIEWER_H



