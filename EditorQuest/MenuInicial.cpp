#include "MenuInicial.h"
#include "Janela.h"
#include "Ingame.h"

void MenuInicial::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Walachia - Menu Inicial");
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
	jogar.Inicializar(janela->renderer, "resources/botoes/Jogar.png", 329.0, h/10.0*4.0);
	sair.Inicializar(janela->renderer, "resources/botoes/Sair do jogo.png", 269.0, h/10.0*8.0);
	titulo.CriaTexturaDaImagem(janela->renderer, "resources/imgs/Walachia.png");
	TTF_CloseFont(fonte);
}

void MenuInicial::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	jogar.Atualizar();
	sair.Atualizar();
}

void MenuInicial::Renderizar(){
	titulo.Renderizar(janela->renderer, ((800.0-(double)titulo.PegaDimensao().w)/2.0), 25);
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