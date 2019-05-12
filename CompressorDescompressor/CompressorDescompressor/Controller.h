#pragma once
//Asume que se inicializo Allegro
//Modulo que se ocupa de manejar los eventos y llamar
//A las funcione necesarias.
#include<allegro5\allegro.h>
#include"Output.h"
#include"board.h"


class controller {
public:
	controller(viewer&, unsigned int threshold_);
	~controller();
	void dispatch(viewer& v, board& d);
	bool IsInitOK()const;
	bool GetExit()const;

private:
	ALLEGRO_EVENT_QUEUE* ev_queue;
	bool init;
	bool exit;
	unsigned int threshold;
};