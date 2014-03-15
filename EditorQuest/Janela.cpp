#include "Janela.h"
#include "GerenteJanela.h"

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
