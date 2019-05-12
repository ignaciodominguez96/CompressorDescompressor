#include "Board.h"
#define MARGEN_RATE 0.1



board::board(int width, int height, vector<images> & images, vector<button> & buttons) : images(images_), botons(botons_)
{
	width = width_;
	height = height_;
	margenX = width * MARGEN_RATE;
	margenY = height * MARGEN_RATE;
	botons[BOTON_LEFT].setPos(BOTON_SIZE_X * MARGEN_RATE, height - BOTON_SIZE_Y);
	botons[BOTON_RIGHT].setPos(width - (BOTON_SIZE_X * 2) - ((BOTON_SIZE_X * MARGEN_RATE) * 3), height - BOTON_SIZE_Y - (BOTON_SIZE_Y * MARGEN_RATE));

	dameroMaximo = (int)(images.size() / IMAGES_PER_DAMERO);
	if (!(images.size() % IMAGES_PER_DAMERO)) //si la division es exacta
	{
		dameroMaximo--; //resto, porque los dameros arrancan desde 0.
	}					//ejemplo: si tengo 9 imagenes y mi damero acepta 9 imagenes como maximo, quiero que mi dameroMaximo sea '0' en lugar de '1'

	dameroActual = 0;
}

void board::setImagesSize(int sizeX_, int sizeY_)
{
	sizeX = sizeX_;
	sizeY = sizeY_;
}
void board::setBotonsSize(int sizeX_, int sizeY_)
{
	botonSizeX = sizeX_;
	botonSizeY = sizeY_;
}
void board::touchDamero(int x, int y)
{
	bool imageTouched = false;
	int posX = 0;
	int posY = 0;

	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (!imageTouched) && (i < images.size()); i++)
	{
		posX = images[i].getPosX();
		posY = images[i].getPosY();
		if (((x >= posX) && (x <= (posX + sizeX))) && ((y >= posY) && (y <= (posY + sizeY)))) //si se toco una imagen
		{
			imageTouched = true;
			images[i].toggleSelected();
		}
	}

	if (!imageTouched)
	{
		if (dameroMaximo != 0)  //habilito botones si tengo mas de un damero 
		{
			bool botonTouched = false;
			int inicio = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
			int finish = (int)botons.size();
			if (dameroActual == 0) //primer damero
			{
				inicio = 1; //deshabilito el primet boton
			}
			else if (dameroActual == dameroMaximo) //ultimo damero
			{
				finish--; //deshabilito el último boton
			}
			for (int i = inicio; (i < finish) && (!botonTouched); i++)
			{
				posX = botons[i].getPosX();
				posY = botons[i].getPosY();
				if (((x >= posX) && (x <= (posX + sizeX))) && ((y >= posY) && (y <= (posY + sizeY)))) //si se toco una imagen
				{
					botonTouched = true;
					changeDamero(i);
					refresh();
				}
			}
		}

	}
}

void board::refresh(void)
{
	int posX = margenX; //posicion de la imagen inicial
	int posY = margenY;
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
	{
		images[i].setPos(posX, posY); //seteo posicion
		posX += (sizeX + margenX);  //calculo posición de la proxima imagen
		if (posX > (width - margenX - sizeX)) //reseteo posX cuando llega al tope de anchura del damero. tope de anchura: (width - margenX - sizeX)
		{
			posX = margenX;
			posY += (sizeY + margenY); //avanzo en 'y'
		}
	}
}

void board::selectAllImages(void)
{
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
	{
		if (!(images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}

void board::unSelectAllImages(void)
{
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
	{
		if ((images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}

vector <ImageDescriptor> & board::getImages(void)
{
	return images;
}

vector <ImageDescriptor> & board::getBotons(void)
{
	return botons;
}

bool board::wasSomethingSelected(void)
{
	bool wasSomethingSelected = false;
	for (int i = 0; (i < images.size()) && !wasSomethingSelected; i++)
	{
		if (images[i].wasSelected())
		{
			wasSomethingSelected = true;
		}
	}
	return wasSomethingSelected;
}

int board::getSizeX(void)
{
	return sizeX;
}

int board::getSizeY(void)
{
	return sizeY;
}

int board::getMargenX(void)
{
	return margenX;
}

int board::getMargenY(void)
{
	return margenY;
}

int board::getDameroActual(void)
{
	return dameroActual;
}

int board::getDameroMaximo(void)
{
	return dameroMaximo;
}

bool board::imagesError(void)
{
	bool errorFounded = false;
	for (int i = 0; (i < images.size()) && (!errorFounded); i++)
	{
		if (images[i].GetError())
		{
			errorFounded = true;
		}
	}

	return errorFounded; //true si hubo error en alguna imagen.- false si esta todo bien.
}

void board::changeDamero(int botonPressed_)
{
	switch (botonPressed_)
	{
	case BOTON_LEFT:
		dameroActual--;
		break;
	case BOTON_RIGHT:
		dameroActual++;
		break;
	}
}

board::~board()
{
}
