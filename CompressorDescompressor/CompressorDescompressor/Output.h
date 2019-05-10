#pragma once



#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_primitives.h>

#include "Images.h"
#include "Board.h"

#define UNIT 1

class viewer //Se ocupa de todo lo relacionado con el output de la simulacion
{
public:
	viewer(unsigned int width_ = 1000, unsigned int height_ = 600);
	~viewer();
	void UpdateDisplay(damero & damero_);
	bool IsInitOK(void);
	ALLEGRO_DISPLAY* GetDisplay(void);
	void printMesagge(char * mesagge);

private:

	unsigned int height;
	unsigned int width;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	double font_size;
	bool init;
	bool InitializeResources(char* image, char* font_path, unsigned int font_size);
	void PrintDamero(damero& damero_); //falta definir
	void DrawHalo(double x, double y, double sizeX, double sizeY); //dibuja el marco alrededor de una imagen seleccionada
													//recibe la esquina superior izquierda de la imagen y el tamano de la misma

};