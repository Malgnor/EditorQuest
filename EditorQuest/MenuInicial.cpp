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
		//janela->ModoTelaCheia();
	}
	janela->PegaTamanho(w, h);
	janela->SetaCorFundo(255, 255, 255);
	janela->Mostrar();
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	jogar.Inicializar(janela->renderer, "Jogar", w/2.0, h/10.0*2.0, fonte, cor);
	sair.Inicializar(janela->renderer, "Sair", w/2.0, h/10.0*8.0, fonte, cor);
	TTF_CloseFont(fonte);
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
	jogar.Atualizar();
	sair.Atualizar();
}

void MenuInicial::Renderizar(){
	jogar.Renderizar(janela->renderer);
	sair.Renderizar(janela->renderer);
}

void MenuInicial::Finalizar(){
}

Tela* MenuInicial::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado || sair.Pressionado())
		return 0;
	if(jogar.Pressionado())
		return new Ingame();
	return this;
}
	
MenuInicial::~MenuInicial(){
}