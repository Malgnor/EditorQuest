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