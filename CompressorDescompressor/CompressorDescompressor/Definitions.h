#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

#define MAX_THRESHOLD	100
#define MIN_THRESHOLD	0

#define THRESHOLD_RATE 7.65

#define TYPE_OF_COMPRESS_FILE ".compr"

#define TYPE_OF_DESCOMPRESS_FILE ".png"

#define CHAR_INDICATE_DIVISION		'D'
#define CHAR_INDICATE_OK_AVERAGE	'A'

#define ID_CUADRANT1 1
#define ID_CUADRANT2 2
#define ID_CUADRANT3 3
#define ID_CUADRANT4 4

#define MODE_COMPRESSOR		0
#define MODE_DESCOMPRESSOR	1

#define MARGIN_RATE 0.1
#define UNIT 1

#define WIDTH_DEFAULT 1000
#define HEIGHT_DEFAULT 600
#define FONT_SIZE_DEFAULT 15

#define OK		0
#define ERROR  -1

#define POSITION_PARAMETER_MODE		 1
#define POSITION_PARAMETER_PATH		 2
#define POSITION_PARAMETER_THRESHOLD 3

#define FLAG_NO_IMAGE_DESCOMPR 0

#define CANT_ELEMENTS_INPUT		3 //path + mode + threshold (optional)
#define CANT_ELEMENTS_PER_CMD (CANT_ELEMENTS_INPUT + 1)


#define PATH_BUTTON_LEFT	"../EDA-TP8/botones/boton_left.png"
#define PATH_BUTTON_RIGHT	 "../EDA-TP8/botones/boton_right.png"

typedef struct
{
	std::string path;
	unsigned int mode;
	int threshold;

}userData_t;


#endif // !DEFINITIONS_H
