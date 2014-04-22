#ifndef _BOTAO_H_
#define _BOTAO_H_

#include "globaldef.h"
#include "Sprite.h"
#include <string>

class Botao
{
protected:
	Sprite sprite[2];
	double x, y;
	std::string texto;
	bool pressionado;
	bool hover;
public:
	virtual void Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte, SDL_Color cor);
	virtual void Atualizar();
	virtual void Renderizar(SDL_Renderer* renderer);
	bool Pressionado();
};

#endif
