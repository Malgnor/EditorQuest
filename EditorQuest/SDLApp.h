#ifndef _SDLAPP_H_
#define _SDLAPP_H_

#include "globaldef.h"

class SDLApp{

public:
	SDLApp();
	~SDLApp();
	void Inicializar();
	int Executar();
	void Finalizar();
};

#endif