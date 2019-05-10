#pragma once
#include <vector>
#include<iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

using namespace std;
using namespace boost::filesystem;


bool SearchFile(vector<string>& paths_vector, const char* path, const char* extension);
//Funcion que busca en un directorio todos los archivos que terminan con una extension dada.
//La extension debe tener el . que la precede. Por ejemplo, como tercer parametro ".txt"

