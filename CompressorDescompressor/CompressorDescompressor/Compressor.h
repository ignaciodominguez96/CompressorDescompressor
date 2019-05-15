#ifndef  COMPRESSOR_H
#define	 COMPRESSOR_H


#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"

#define TYPE_OF_COMPRESS_FILE ".compr"

#define CHAR_INDICATE_DIVISION		'D'
#define CHAR_INDICATE_OK_AVERAGE	'A'

namespace fsystem = boost::filesystem;


bool compress(unsigned int threshold_compression, const char * path_image, unsigned int image_width, unsigned int image_height);




#endif // ! COMPRESSOR_H

