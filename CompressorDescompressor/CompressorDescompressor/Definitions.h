#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

#define THRESHOLD_RATE 7.65


#define TYPE_OF_COMPRESS_FILE ".compr"

#define TYPE_OF_DESCOMPRESS_FILE ".png"

#define CHAR_INDICATE_DIVISION		'D'
#define CHAR_INDICATE_OK_AVERAGE	'A'

#define ID_CUADRANT1 1
#define ID_CUADRANT2 2
#define ID_CUADRANT3 3
#define ID_CUADRANT4 4

#define MODE_COMPRESSOR		1
#define MODE_DESCOMPRESSOR	2



#define WIDTH_DEFAULT 1000
#define HEIGHT_DEFAULT 600
#define FONT_SIZE_DEFAULT 30



#define BACKGROUND_PATH "background2.png" //Imagen de fondo

#define FONT_PATH "Font.ttf"
#define FONT_COLOR "red"

#define IMAGE_DESCOMPRESSOR_PATH "icon_compress.png"

#define MARKER_WIDTH 10


#define PATH_BUTTON_LEFT	"button_left2.png"
#define PATH_BUTTON_RIGHT	"button_right2.png"

typedef struct
{
	std::string path;
	unsigned int mode;
	int threshold;

}userData_t;


#endif // !DEFINITIONS_H
