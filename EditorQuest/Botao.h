#ifndef _BOTAO_H_
#define _BOTAO_H_

#include "globaldef.h"
#include "Sprite.h"
#include <string>

class Botao
{
private:
	Sprite sprite[2];
	double x, y;
	std::string texto;
	bool pressionado;
	bool hover;
public:
	void Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte, SDL_Color cor);
	void Atualizar();
	void Renderizar(SDL_Renderer* renderer);
	bool Pressionado();
};

#endif
