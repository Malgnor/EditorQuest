#ifndef _SDLAPP_H_
#define _SDLAPP_H_

#include "globaldef.h"
#include "Janela.h"

class SDLApp{
private:
	void Inicializar();
	void Encerrar();

public:
	SDLApp();
	~SDLApp();
	int Executar();
};

#endif