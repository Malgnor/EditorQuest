#ifndef _BOTAOPERSONALIZADO_H_
#define _BOTAOPERSONALIZADO_H_

#include "Botao.h"

class BotaoPersonalizado : public Botao
{
public:
	virtual void Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte = 0, SDL_Color cor = SDL_Color());
	virtual void Renderizar(SDL_Renderer* renderer);
};

#endif