#ifndef _JANELA_H_
#define _JANELA_H_

#include "globaldef.h"

class Janela{
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;

public:
	virtual void Inicializar() = 0;
	virtual void Renderizar() = 0;
	virtual void Encerrar() = 0;
};

#endif