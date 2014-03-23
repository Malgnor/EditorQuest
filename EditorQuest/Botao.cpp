#include "Botao.h"

void Botao::Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte, SDL_Color cor){
	texto = _texto;
	x = _x;
	y = _y;
	pressionado = hover = false;
	sprite[0].CriaTexturaMenu(renderer, "resources/imgs/botao.png", texto.c_str(), fonte, cor);
	sprite[1].CriaTexturaMenu(renderer, "resources/imgs/botaop.png", texto.c_str(), fonte, cor);
}

void Botao::Atualizar(){
	int mx = 0;
	int my = 0;
	hover = pressionado = false;
	SDL_GetMouseState(&mx, &my);
	if(mx > x && mx < x+sprite[0].PegaDimensao().w && my > y && my < y+sprite[0].PegaDimensao().h)
	{
		hover = true;
		if(SDL_GetMouseState(0,0)&SDL_BUTTON(1))
		{
			pressionado = true;
		}
	}
}

void Botao::Renderizar(SDL_Renderer* renderer){
	sprite[hover ? 1 : 0].Renderizar(renderer, x, y);
}

bool Botao::Pressionado(){
	return pressionado;
}
