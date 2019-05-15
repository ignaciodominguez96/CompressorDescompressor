#pragma once

#ifndef DESCOMPRESSOR_H
#define DESCOMPRESSOR_H


#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"

#include "Definitions.h"


namespace fsystem = boost::filesystem;


bool descompress(const char * path_image);



#endif // !DESCOMPRESSOR_H
