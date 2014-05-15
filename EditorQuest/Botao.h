#ifndef _BOTAO_H_
#define _BOTAO_H_

#include "globaldef.h"
#include "Sprite.h"
#include <string>

struct M_Mouse;

class Botao
{
protected:
	Sprite sprite[2];
	double x, y;
	std::string texto;
	bool pressionado, hover, solto;

public:
	virtual void Inicializar(SDL_Renderer* renderer, char* _texto, TTF_Font* fonte, SDL_Color cor);
	virtual void Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte, SDL_Color cor);
	virtual void Atualizar(M_Mouse* m);
	virtual void Renderizar(SDL_Renderer* renderer);
	void SetaPosicao(double _x, double _y);
	SDL_Rect PegaPosicao();
	SDL_Rect PegaDimensao();
	bool Pressionado();
	bool Pressed();
	bool Hover();
};

#endif
