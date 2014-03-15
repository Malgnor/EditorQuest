#include "Jogo.h"
#include "GerenciadorTelas.h"
#include "GerenteJanela.h"
#include "MenuInicial.h"
#include <stdlib.h>

Jogo::Jogo(){	
	renderer = NULL;
	window = NULL;
	gerente = NULL;
	this->Inicializar();
	GJanela.Adicionar(this);
}

Jogo::~Jogo(){
	if(this->Existe())
		GJanela.Remover(this);
}

void Jogo::Inicializar(){
	window = SDL_CreateWindow("Editor's Quest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	gerente = new GerenciadorTelas(new MenuInicial(), this);
}

void Jogo::ProcessarEventos(SDL_Event& evento){	
	if(evento.key.keysym.sym == SDLK_KP_0 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_1 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_2 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_3 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
}

void Jogo::Atualizar(){
	if(this->Existe())
		if(!gerente->Acabou())
			gerente->Atualizar();
		else
			GJanela.Remover(this);
}

void Jogo::Renderizar(){
	if(this->Existe())
		if(!gerente->Acabou()){
			SDL_RenderClear(renderer);
			gerente->Renderizar();
			SDL_RenderPresent(renderer);
		}
}

void Jogo::Encerrar(){	
	if(this->Existe()){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		delete gerente;
		renderer = NULL;
		window = NULL;
		gerente = NULL;
	}
}
