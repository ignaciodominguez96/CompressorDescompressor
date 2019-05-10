#pragma once
#include <string>

#include"Images.h"

#define IMAGE_SIZE_X 180 //256 
#define IMAGE_SIZE_Y 100 //130
#define BOTON_SIZE_X 80
#define BOTON_SIZE_Y 80
#define SPACE 10

using namespace std;

class ImageDescriptor
{
public:
	ImageDescriptor();
	ImageDescriptor(const char * path_); //falta completar.
	bool wasSelected(void);
	void toggleSelected(void);
	void setPos(int posX_, int posY_);
	int getPosX(void);
	int getPosY(void);
	unsigned int getWidth();
	unsigned int getHeight();
	const char * getPath(void);
	const char * getNameFile(void);
	bool GetError()const;
	ALLEGRO_BITMAP* GetBitmap()const;
	~ImageDescriptor();
private:
	bool selected;
	const char * path;
	string fileName;
	string extractNamefile(const char * path_);
	ALLEGRO_BITMAP* Image;
	int posX;
	int posY;
	bool error;
	unsigned int  width;
	unsigned int height;
};

