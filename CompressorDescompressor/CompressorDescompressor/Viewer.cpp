#include "Viewer.h"



#define BACKGROUND_PATH "background.png" //Imagen de fondo

#define FONT_PATH "Font.ttf"
#define FONT_COLOR "white"

#define IMAGE_DESCOMPRESSOR_PATH "iconMet.png"

#define MARKER_WIDTH 10

bool init_allegro(void);			//inicializa allegro --- listo
		



//listo
viewer::viewer(unsigned int width, unsigned int height, double font_size, unsigned int mode)
{
	

	this->is_init_bool = init_allegro();
	
	if (this->is_init_bool)
	{
		if ((mode == MODE_COMPRESSOR) || (mode == MODE_DESCOMPRESSOR))
		{
			this->mode = mode;
			this->width = width;
			this->height = height;
			this->font_size = font_size;
			this->is_init_bool = init_allegro_elements(BACKGROUND_PATH, FONT_PATH);
		}
		else
		{
			this->is_init_bool = false;
		}

		
	}


	if (mode == MODE_DESCOMPRESSOR)
	{
		this->error_descompressor_image = false;
		this->image_descompressor = load_image_at_size(IMAGE_DESCOMPRESSOR_PATH, IMAGE_SIZE_X, IMAGE_SIZE_Y);


		if (this->image_descompressor == nullptr)
		{
			this->error_descompressor_image = true;
			this->is_init_bool = false;
		}
			   
	}
	
	
}

//listo
viewer:: ~viewer()
{

	if (this->is_init_bool)
	{
		al_destroy_bitmap(this->background);
		al_destroy_font(this->font);
		al_destroy_display(this->display);

		this->is_init_bool = false;
	}
}


//listo
bool viewer::is_init(void)
{
	return this->is_init_bool;
}  


//listo
void viewer::update_display(board & board)
{

	ALLEGRO_BITMAP* aux_target = al_get_target_bitmap(); 

	al_set_target_backbuffer(this->display);
	
	al_draw_bitmap(this->background, 0.0, 0.0, 0.0);

	print_board(board);

	al_set_target_bitmap(aux_target);


}


//listo
ALLEGRO_DISPLAY* viewer::get_display(void)
{
	return this->display;
}

//listo
void viewer::print_message(char * mesagge)
{
	al_draw_text(this->font, al_color_name(FONT_COLOR), this->width / 2.0, this->height - (IMAGE_SIZE_Y / 4.0), ALLEGRO_ALIGN_CENTER, mesagge);
}


//listo
bool viewer::init_allegro_elements(const char* path_background, const char* font_path)
{

	bool init_allegro_el = true;

	this->display = al_create_display( (this->width)*(UNIT), (this->height)*(UNIT) );
	
	if (this->display == nullptr)
	{
		init_allegro_el = false;

	}

	if (init_allegro_el)
	{
		this->background = load_image_at_size(path_background, (this->width)*(UNIT), (this->height)*(UNIT));

		if (background == nullptr)
		{
			al_draw_bitmap(this->background, 0, 0, 0);
			al_destroy_display(this->display);
			init_allegro_el = false;
		}
	}

	
	if (init_allegro_el)
	{
		this->font = al_load_ttf_font(font_path, this->font_size, 0);
		
		if (this->font == nullptr)
		{
			al_destroy_display(this->display);
			al_destroy_bitmap(this->background);
			init_allegro_el = false;
		}
	}


	return init_allegro_el;

}

//listo
void viewer::print_board(board& board)
{

	int pos_x = 0;
	int pos_y = 0;

	int size_x = board.get_size_x();
	int size_y = board.get_size_y();
	int actual_board = board.get_actual();

	ALLEGRO_COLOR color = al_color_name(FONT_COLOR);

	ALLEGRO_BITMAP * aux_bitmap = NULL;



	for (int i = FIRST_IMAGE_BOARD(actual_board); (i < LAST_IMAGE_BOARD(actual_board)) && (i < (board).get_images().size()); i++)
	{
		pos_x = ((board).get_images())[i].get_pos_x();
		pos_y = ((board).get_images())[i].get_pos_y();


		

		if (this->mode == MODE_COMPRESSOR)
		{
			 aux_bitmap = ((board).get_images())[i].get_bitmap();
		}
		else if (this->mode == MODE_DESCOMPRESSOR)
		{
			aux_bitmap = this->image_descompressor;
		}

		al_draw_bitmap(aux_bitmap , pos_x, pos_y, 0); 
	

		const char * text = (board.get_images())[i].get_name_file();

		al_draw_text(this->font, color, pos_x + (IMAGE_SIZE_X / 2.0), pos_y + IMAGE_SIZE_Y + 10, ALLEGRO_ALIGN_CENTRE, );
		
		
		bool image_selected = ((board).get_images())[i].was_selected();

		if (image_selected)
		{
			draw_marker(pos_x, pos_y, size_x, size_y);
		}

	}



	
	if (board.get_cant() != 0) //si tengo por lo menos una imagen en el tablero
	{
		bool button_touched = false;
		int first_button = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
		int last_button = (int)   (board).get_buttons().size();

		if ((board).get_actual() == 0) //primer damero
		{
			first_button = 1; //salteo el primer boton.
		}
		else if ((board).get_actual() == (board).get_cant()) //ultimo damero
		{
			last_button--; //descarto el �ltimo boton.
		}



		for (int i = first_button; (i < last_button) && (!button_touched); i++)
		{
			ImageDescriptor button = (board.get_buttons()[i]);
			
			ALLEGRO_BITMAP * image_button = button.get_bitmap();
			int button_pos_x = button.get_pos_x();
			int button_pos_y = button.get_pos_y();

			al_draw_bitmap(image_button, button_pos_x, button_pos_y, 0);
		}
	}

}


//listo
void viewer::draw_marker(double x, double y, double sizeX, double sizeY)
{
	ALLEGRO_BITMAP* actual_bitmap = al_get_target_bitmap();
	al_set_target_backbuffer(this->display);

	for (int i = 1; i <= MARKER_WIDTH; i++)
	{
		al_draw_rectangle(x - i, y - i, x + sizeX + i, y + sizeY + i, al_map_rgb(0, 255 - i * 20, 0), 1.0);
	}

	al_set_target_bitmap(actual_bitmap);
}

//listo
bool init_allegro(void)
{
	bool is_init = true;

	if (!al_init_image_addon() && is_init)
	{
		is_init = false;
	}

	if (!al_init_font_addon() && is_init)
	{
		is_init = false;
	}

	if (!al_init_ttf_addon() && is_init)
	{
		is_init = false;
	}

	if (!al_init_primitives_addon() && is_init)
	{
		is_init = false;
	}


	return is_init;

}