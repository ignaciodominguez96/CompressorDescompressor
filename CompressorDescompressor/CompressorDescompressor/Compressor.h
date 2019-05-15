#ifndef  COMPRESSOR_H
#define	 COMPRESSOR_H


#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"

#include "Definitions.h"

namespace fsystem = boost::filesystem;


bool compress(unsigned int threshold_compression, const char * path_image, unsigned int image_width, unsigned int image_height);




#endif // ! COMPRESSOR_H

