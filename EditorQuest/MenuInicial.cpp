#include "MenuInicial.h"
#include "Janela.h"
#include "Ingame.h"

void MenuInicial::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Editor's Quest - Menu Inicial");
	int w, h;
	janela->PegaTamanho(w, h);
	if( w != 800 && h != 600){
		janela->SetaTamanho(800, 600);
		janela->SetaPosicao(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	}
	janela->SetaCorFundo(255, 255, 255);
	janela->Mostrar();
}

void MenuInicial::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	if(Teclas[FW_1].pressionado)
		janela->SetaCorFundo(255, 255, 255);
	if(Teclas[FW_2].pressionado)
		janela->SetaCorFundo(0, 255, 255);
	if(Teclas[FW_3].pressionado)
		janela->SetaCorFundo(255, 0, 255);
	if(Teclas[FW_4].pressionado)
		janela->SetaCorFundo(255, 255, 0);
}

void MenuInicial::Renderizar(){
}

void MenuInicial::Finalizar(){
}

Tela* MenuInicial::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado)
		return nullptr;
	if(PegaTecla()[FW_ESC].pressionado)
		return new Ingame();
	return this;
}
	
MenuInicial::~MenuInicial(){
}