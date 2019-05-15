#ifndef DEFINITIONS_H
#define DEFINITIONS_H


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


#define UNIT 1

#define WIDTH_DEFAULT 1000
#define HEIGHT_DEFAULT 600
#define FONT_SIZE_DEFAULT 15

#define ERROR -1


typedef struct
{
	string path;
	int threshold;

}userData_t;


#endif // !DEFINITIONS_H
