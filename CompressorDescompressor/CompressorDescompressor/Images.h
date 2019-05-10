#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

ALLEGRO_BITMAP * load_image_at_size(const char* image_name, int size_x, int size_y);
//Devuelve el bitmap de la imagen cargada en el tamano deseado.
//En caso de error devuelve NULL.

void destroy_images(ALLEGRO_BITMAP  **imagen, unsigned int num_imagenes);
//Libera toda la memoria utilizada por las imagenes creadas