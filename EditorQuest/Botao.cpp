#include "Botao.h"
#include "Entrada.h"

void Botao::Inicializar(SDL_Renderer* renderer, char* _texto, TTF_Font* fonte, SDL_Color cor){
	texto = _texto;
	pressionado = hover = solto = false;
	sprite[0].CriaTexturaMenu(renderer, "resources/imgs/botao.png", texto.c_str(), fonte, cor);
	sprite[1].CriaTexturaMenu(renderer, "resources/imgs/botaop.png", texto.c_str(), fonte, cor);
}

void Botao::Inicializar(SDL_Renderer* renderer, char* _texto, double _x, double _y, TTF_Font* fonte, SDL_Color cor){
	texto = _texto;
	x = _x;
	y = _y;
	pressionado = hover = solto = false;
	sprite[0].CriaTexturaMenu(renderer, "resources/imgs/botao.png", texto.c_str(), fonte, cor);
	sprite[1].CriaTexturaMenu(renderer, "resources/imgs/botaop.png", texto.c_str(), fonte, cor);
}

void Botao::Atualizar(M_Mouse* m){
	if(m->x > x && m->x < x+sprite[0].PegaDimensao().w && m->y > y && m->y < y+sprite[0].PegaDimensao().h)
	{
		hover = true;
		if(SDL_GetMouseState(0,0)&SDL_BUTTON(1))
		{
			pressionado = true;
		} else if(pressionado){
			pressionado = false;
			solto = true;
		}

	} else{
		hover = false;
		if(!(SDL_GetMouseState(0,0)&SDL_BUTTON(1)) && pressionado)
			pressionado = false;
	}
}

void Botao::Renderizar(SDL_Renderer* renderer){
	sprite[hover ? 1 : 0].Renderizar(renderer, x, y);
}

void Botao::SetaPosicao(double _x, double _y){
	x = _x;
	y = _y;
}

SDL_Rect Botao::PegaPosicao(){
	SDL_Rect ret = {(int)x, (int)y, 0, 0};
	return ret;
}

SDL_Rect Botao::PegaDimensao(){
	return sprite->PegaDimensao();
}

bool Botao::Pressionado(){
	if(solto){
		solto = false;
		return true;
	}
	return false;
}

bool Botao::Pressed(){
	return pressionado;
}

bool Botao::Hover(){
	return hover;
}