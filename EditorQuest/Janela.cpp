#include "Janela.h"
#include "GerenteJanela.h"
#include "GerenciadorTelas.h"
#include "Tela.h"

Janela::Janela(Tela* telainicial){	
	renderer = NULL;
	window = NULL;
	gerente = NULL;
	this->Inicializar(telainicial);
	GJanela.Adicionar(this);
}

Janela::~Janela(){
	if(this->Existe())
		GJanela.Remover(this);
}

void Janela::Inicializar(Tela* telainicial){
	window = SDL_CreateWindow("Undefined", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256, 256, SDL_WINDOW_HIDDEN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	gerente = new GerenciadorTelas(telainicial, this);
}

void Janela::ProcessarEventos(SDL_Event& evento){	
	if(evento.key.keysym.sym == SDLK_KP_0 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_1 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_2 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	else if(evento.key.keysym.sym == SDLK_KP_3 && evento.key.state == SDL_RELEASED)		
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
}

void Janela::Atualizar(){
	if(this->Existe())
		if(!gerente->Acabou())
			gerente->Atualizar();
		else
			GJanela.Remover(this);
}

void Janela::Renderizar(){
	if(this->Existe())
		if(!gerente->Acabou()){
			SDL_RenderClear(renderer);
			gerente->Renderizar();
			SDL_RenderPresent(renderer);
		}
}

void Janela::Encerrar(){	
	if(this->Existe()){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		delete gerente;
		renderer = NULL;
		window = NULL;
		gerente = NULL;
	}
}

void Janela::ProcessarEventosW(SDL_Event& evento){
	if(evento.window.windowID == this->PegaID()){
		switch (evento.window.event)
		{
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			GJanela.SetaJanelaFocada(this);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(window);
			GJanela.Remover(this);
			return;
		}
	}
}

void Janela::Mostrar(){
	SDL_ShowWindow(window);
}

void Janela::Esconder(){
	SDL_HideWindow(window);
}

void Janela::Remover(){
	SDL_HideWindow(window);
	GJanela.Remover(this);
}

bool Janela::Existe(){
	return (window != 0);
}

SDL_Renderer* Janela::PegaRenderder(){
	return renderer;
}

Uint32 Janela::PegaID(){
	return SDL_GetWindowID(window);
}

const char* Janela::PegaTitulo(){
	return SDL_GetWindowTitle(window);
}

void Janela::PegaPosicao(int &x, int &y){
	SDL_GetWindowPosition(window, &x, &y);
}

void Janela::PegaTamanho(int &w, int &h){
	SDL_GetWindowSize(window, &w, &h);
}

void Janela::SetaTitulo(const char* titulo){
	SDL_SetWindowTitle(window, titulo);
}

void Janela::SetaIcone(SDL_Surface* icone){
	SDL_SetWindowIcon(window, icone);
}

void Janela::SetaPosicao(int x, int y){
	SDL_SetWindowPosition(window, x, y);
}

void Janela::SetaTamanho(int w, int h){
	SDL_SetWindowSize(window, w, h);
}
