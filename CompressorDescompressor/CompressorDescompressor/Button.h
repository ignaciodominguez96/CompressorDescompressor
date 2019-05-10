#pragma once
#include <vector>
#include "ImageDescriptor.h"

#define IMAGES_PER_DAMERO 9
#define BOTON_LEFT 0  //indices correspondientes al vector de botones.
#define BOTON_RIGHT 1
#define FIRST_IMG_OF_THIS_DAMERO(dameroActual) (IMAGES_PER_DAMERO * dameroActual)
#define LAST_IMG_OF_THIS_DAMERO(dameroActual) (IMAGES_PER_DAMERO * (dameroActual + 1))

class damero
{
public:
	damero(int width_, int height_, vector<ImageDescriptor> & images_, vector<ImageDescriptor> & botons_);// : images(images_), botons(botons_) {} //HAY QUE ARREGLARLO!
	void refresh(void);
	void touchDamero(int x, int y);
	void selectAllImages(void);
	void unSelectAllImages(void);
	bool wasSomethingSelected(void);
	void setImagesSize(int sizeX_, int sizeY_);
	void setBotonsSize(int botonSizeX, int botonSizeY);
	vector <ImageDescriptor> & getImages(void);
	vector <ImageDescriptor> & getBotons(void);
	int getSizeX(void);
	int getSizeY(void);
	int getMargenX(void);
	int getMargenY(void);
	int getDameroActual(void);
	int getDameroMaximo(void);
	bool imagesError(void);
	~damero();
private:

	vector<ImageDescriptor> & images;
	vector<ImageDescriptor> & botons;
	int sizeX; //tamaño de cada image
	int sizeY;
	int botonSizeX; //tamaño de los botones
	int botonSizeY;
	int margenX; //margenes
	int margenY;
	int width; //dimensiones del damero
	int height;
	int dameroActual; // de cero a la cantidad de dameros -1
	int dameroMaximo; // cantidad de dameros

	void changeDamero(int botonPressed_);
};

