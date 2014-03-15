#include "MenuInicial.h"
#include "Janela.h"

void MenuInicial::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Editor's Quest - Menu Inicial");
	janela->SetaTamanho(800, 600);
	janela->SetaPosicao(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	janela->Mostrar();
}

void MenuInicial::Atualizar(){
	if(Teclas[FW_1].pressionado)
		SDL_SetRenderDrawColor(janela->PegaRenderder(), 255, 255, 255, 255);
	if(Teclas[FW_2].pressionado)
		SDL_SetRenderDrawColor(janela->PegaRenderder(), 0, 255, 255, 255);
	if(Teclas[FW_3].pressionado)
		SDL_SetRenderDrawColor(janela->PegaRenderder(), 255, 0, 255, 255);
	if(Teclas[FW_4].pressionado)
		SDL_SetRenderDrawColor(janela->PegaRenderder(), 255, 255, 0, 255);
}

void MenuInicial::Renderizar(){
}

void MenuInicial::Finalizar(){
}

Tela* MenuInicial::ProximaTela(){
	return this;
}
	
MenuInicial::~MenuInicial(){
}