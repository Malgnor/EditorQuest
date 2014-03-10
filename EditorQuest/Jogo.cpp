#include "Jogo.h"

Jogo::Jogo(){
	renderer = NULL;
	window = NULL;
	this->Inicializar();
}

void Jogo::Inicializar(){
	window = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
}

void Jogo::Renderizar(){
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Jogo::Encerrar(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
}

Jogo::~Jogo(){
	this->Encerrar();
}