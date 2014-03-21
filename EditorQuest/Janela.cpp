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
	this->Finalizar();
}

void Janela::Inicializar(Tela* telainicial){
	window = SDL_CreateWindow("Undefined", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256, 256, SDL_WINDOW_HIDDEN);
	if(window == 0){
		printf( "Falha ao criar Window! SDL Error: %s\n",  SDL_GetError() );
		this->Finalizar();
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == 0){
		printf( "Falha ao criar Renderer! SDL Error: %s\n",  SDL_GetError() );
		this->Finalizar();
		return;
	}
	corfundo.r = corfundo.g = corfundo.b = corfundo.a = 0;
	SDL_SetRenderDrawColor(renderer, corfundo.r, corfundo.g, corfundo.b, corfundo.a);
	entrada = FW_Entrada();
	gerente = new GerenciadorTelas(telainicial, this);
}

void Janela::ProcessarEventos(SDL_Event& evento){
	entrada.atualiza(evento);
}

void Janela::ProcessarEventosW(SDL_Event& evento){
	if(evento.window.windowID == this->PegaID()){
		switch (evento.window.event)
		{
		/*
		case SDL_WINDOWEVENT_SHOWN:
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_EXPOSED:
		case SDL_WINDOWEVENT_CLOSE:
		case SDL_WINDOWEVENT_LEAVE:
		case SDL_WINDOWEVENT_MOVED:
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_MAXIMIZED:
		case SDL_WINDOWEVENT_RESTORED:
		case SDL_WINDOWEVENT_ENTER:
		case SDL_WINDOWEVENT_FOCUS_LOST:
		*/
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_LEAVE:
		case SDL_WINDOWEVENT_FOCUS_LOST:
		case SDL_WINDOWEVENT_MINIMIZED:
			entrada.reseta();
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			GJanela.SetaJanelaFocada(this);
			break;
		}
	}
}

void Janela::Atualizar(){
	if(this->Existe())
		if(!gerente->Acabou())
			gerente->Atualizar();
		else
			this->Finalizar();
}

void Janela::Renderizar(){
	if(this->Existe())
		if(!gerente->Acabou()){
			SDL_SetRenderDrawColor(renderer, corfundo.r, corfundo.g, corfundo.b, corfundo.a);
			SDL_RenderClear(renderer);
			gerente->Renderizar();
			SDL_RenderPresent(renderer);
		}
}

void Janela::Finalizar(){	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete gerente;
	renderer = NULL;
	window = NULL;
	gerente = NULL;
}

void Janela::Mostrar(){
	SDL_ShowWindow(window);
}

void Janela::Esconder(){
	SDL_HideWindow(window);
}

void Janela::Remover(){
	SDL_HideWindow(window);
	this->Finalizar();
}

bool Janela::Existe(){
	return (window != 0);
}

SDL_Color Janela::PegaCorFundo(){
	return corfundo;
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

SDL_Rect Janela::PegaPosicaoeTamanho(){
	SDL_Rect rect;
	SDL_GetWindowPosition(window, &rect.x, &rect.y);
	SDL_GetWindowSize(window, &rect.w, &rect.h);
	return rect;
}

void Janela::SetaCorFundo(SDL_Color cor){
	corfundo = cor;
}

void Janela::SetaCorFundo(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	corfundo.r = r;
	corfundo.g = g;
	corfundo.b = b;
	corfundo.a = a;
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
