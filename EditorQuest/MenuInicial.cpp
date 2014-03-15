#include "MenuInicial.h"
#include "Janela.h"

void MenuInicial::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Editor's Quest - Menu Inicial");
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