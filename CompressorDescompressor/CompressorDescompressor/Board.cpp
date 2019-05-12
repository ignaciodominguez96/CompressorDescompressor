
#include "Board.h"
#define MARGEN_RATE 0.1

board::board(int width_, int height_, vector<ImageDescriptor> & images_, vector<ImageDescriptor> & botons_) : images(images_), buttons(botons_)
{
	width = width_;
	height = height_;
	marginX = width * MARGEN_RATE;
	marginY = height * MARGEN_RATE;
	buttons[BOTON_LEFT].setPos(BOTON_SIZE_X * MARGEN_RATE, height - BOTON_SIZE_Y);
	buttons[BOTON_RIGHT].setPos(width - (BOTON_SIZE_X * 2) - ((BOTON_SIZE_X * MARGEN_RATE) * 3), height - BOTON_SIZE_Y - (BOTON_SIZE_Y * MARGEN_RATE));

	button_cant = (int)(images.size() / IMAGES_PER_BOARD);
	if (!(images.size() % IMAGES_PER_BOARD)) //si la division es exacta
	{
		button_cant--; //resto, porque los dameros arrancan desde 0.
	}					//ejemplo: si tengo 9 imagenes y mi damero acepta 9 imagenes como maximo, quiero que mi dameroMaximo sea '0' en lugar de '1'

	button_actual = 0;
}
board::~board()
{

}
void 
board::refresh(void)
{
	int pos_X = marginX; //posicion de la imagen inicial
	int pos_Y = marginY;
	for (int i = FIRST_IMG_OF_THIS_BOARD(button_actual); (i < LAST_IMG_OF_THIS_BOARD(button_actual)) && (i < images.size()); i++)
	{
		images[i].setPos(pos_X, pos_Y); //seteo posicion
		pos_X += (image_sizeX + marginX);  //calculo posición de la proxima imagen
		if (pos_X > (width - marginX - image_sizeX)) //reseteo posX cuando llega al tope de anchura del board. tope de anchura: (width - marginX - image_sizeX)
		{
			pos_X = marginX;
			pos_Y += (image_sizeY + marginY); //avanzo en 'y'
		}

	}
}


void 
board::touch(int x, int y)
{
	bool imageTouched = false;
	int pos_X = 0;
	int pos_Y = 0;

	for (int i = FIRST_IMG_OF_THIS_BOARD(button_actual); (i < LAST_IMG_OF_THIS_BOARD(button_actual)) && (!imageTouched) && (i < images.size()); i++)
	{
		pos_X = images[i].getPosX();
		pos_Y = images[i].getPosY();
		if (((x >= pos_X) && (x <= (pos_X + image_sizeX))) && ((y >= pos_Y) && (y <= (pos_Y + image_sizeY)))) //si se toco una imagen
		{
			imageTouched = true;
			images[i].toggleSelected();
		}
	}

	if (!imageTouched)
	{
		bool botonTouched = false;
		int inicio = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
		int finish = (int)buttons.size();
		if (button_actual == 0) //primer damero
		{
			inicio = 1; //salteo el primer boton.
		}
		else if (button_actual == button_cant) //ultimo damero
		{
			finish--; //descarto el último boton.
		}
		for (int i = inicio; (i < finish) && (!botonTouched); i++)
		{
			pos_X = buttons[i].getPosX();
			pos_Y = buttons[i].getPosY();
			if (((x >= pos_X) && (x <= (pos_X + image_sizeX))) && ((y >= pos_Y) && (y <= (pos_Y + image_sizeY)))) //si se toco una imagen
			{
				botonTouched = true;
				change_board(i);
				refresh();
			}
		}
	}
}
void 
board::select_all_images(void)
{
	for (int i = FIRST_IMG_OF_THIS_BOARD(button_actual); (i < LAST_IMG_OF_THIS_BOARD(button_actual)) && (i < images.size()); i++)
	{
		if (!(images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}
void 
board::unselect_all_images(void)
{
	for (int i = FIRST_IMG_OF_THIS_BOARD(button_actual); (i < LAST_IMG_OF_THIS_BOARD(button_actual)) && (i < images.size()); i++)
	{
		if ((images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}
bool 
board::is_some_image_select(void)
{
	bool Selected = false;
	for (int i = 0; (i < images.size()) && !Selected; i++)
	{
		if (images[i].wasSelected())
		{
			Selected = true;
		}
	}
	return Selected;
}



void 
board::set_image_size(int sizeX_, int sizeY_)
{
	image_sizeX = sizeX_;
	image_sizeY = sizeY_;

}
void 
board::set_boton_size(int SizeX, int SizeY)
{
	button_sizeX = SizeX;
	button_sizeY = SizeY;
}
vector <ImageDescriptor> &
board::get_images(void)
{
	return images;
}
vector <ImageDescriptor> &
board::get_buttons(void)
{
	return buttons;
}
int 
board::get_sizeX(void)
{
	return image_sizeX;
}
int 
board::get_sizeY(void)
{
	return image_sizeY;
}
int 
board::get_marginX(void)
{
	return marginX;
}
int 
board::get_marginY(void)
{
	return marginY;
}
int 
board::get_actual(void)
{
	return button_actual;
}
int 
board::get_cant(void)
{
	return button_cant;
}



bool 
board::images_error(void)
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

void 
board::change_board(int botonPressed_)
{
	switch (botonPressed_)
	{
	case BOTON_LEFT:
		button_actual--;
		break;
	case BOTON_RIGHT:
		button_actual++;
		break;
	}
}