#include "Parser.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

bool parserCmd(int argc, char ** argv, userData_t & userData)
{
	bool can_parse = true;
	
	if (argc > 2)
	{
		userData.path = get_path_from_cmd(argc - 1, argv);		 //arg - 1 porque el último elemento del argv no pertenece al path (el último es el treshold)
		
		
		double threshold_cmd = string_to_double(argv[argc - 1]); //ultimo parametro es el threshold
		
		
		if ((threshold_cmd >= MIN_THRESHOLD) && (threshold_cmd <= MAX_THRESHOLD))
		{
			userData.threshold = interpret_threshold(threshold_cmd);
		}
		else
		{
			cout << "Threshold (2do parametro) debe ser un numero entre " << MIN_THRESHOLD << " y " << MAX_THRESHOLD << endl;
			can_parse = false;
		}


	}
	else
	{
		cout << "ERROR:  ingresar por linea de comando primero el path al directorio de imagenes a comprimir y luego un threshold entre 0 y 100" << endl;
		can_parse = false;
	}

	return can_parse;
}


double string_to_double(const char * num_string)
{
	double num_dec = 0.0;
	string num_string_aux = num_string;
	num_dec = (double) stof(num_string_aux, nullptr);

	return num_dec;
}


string get_path_from_cmd(int argc, char ** argv)
{
	string completePath;
	if (argc > 0)
	{
		completePath = argv[1];
	}
	for (int i = 2; i < argc; i++)
	{
		completePath += ' ';
		completePath += argv[i];
	}

	return completePath;
}


int interpret_threshold(double threshold_cmd)
{
	int threshold = (int)ceil(threshold_cmd * THRESHOLD_RATE);
	return threshold;
}