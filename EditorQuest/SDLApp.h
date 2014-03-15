#ifndef _SDLAPP_H_
#define _SDLAPP_H_

#include "globaldef.h"

class SDLApp{
private:
	Uint32 ticks;

public:
	SDLApp();
	~SDLApp();
	void Inicializar();
	int Executar();
	void Encerrar();
};

#endif