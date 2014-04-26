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
	}
	janela->PegaTamanho(w, h);
	janela->SetaCorFundo(255, 255, 255);
	janela->Mostrar();
	unsigned int altura, largura;
	altura = (unsigned int)ceil((double)h/32.0);
	largura = (unsigned int)ceil((double)w/32.0);
	unsigned int** map = new unsigned int*[altura];
	for(unsigned int i = 0; i < altura; i++){
		map[i] = new unsigned int[largura];
	}
	for(unsigned int i = 0; i < altura; i++){
		for(unsigned int j = 0; j < largura; j++){
			if( i == 0 || j == 0 || j == largura-1 || i == altura-1 /*|| (0 == j%16 && i > 4) || (0 == j%8 && i < altura-4 && 0 != j%16)*/)
				map[i][j] = 1;
			else
				map[i][j] = 2;
		}
	}
	mapa.Inicializar(janela->renderer, map, altura, largura);
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	jogar.Inicializar(janela->renderer, "resources/botoes/Jogar.png", 329.0, h/10.0*4.0);
	sair.Inicializar(janela->renderer, "resources/botoes/Sair do jogo.png", 269.0, h/10.0*8.0);
	titulo.CriaTexturaDaImagem(janela->renderer, "resources/imgs/Walachia.png");
	portal.CriaTexturaDaImagemC(janela->renderer, "resources/imgs/portal.png", 180, 0, 0, 128, 0);
	TTF_CloseFont(fonte);
	indice = 0;
	time = 0;
}

void MenuInicial::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	time += deltaTime;
	if(time >= 333){
		time -= 333;
		indice = (indice+1)%4;
	}
	jogar.Atualizar();
	sair.Atualizar();
}

void MenuInicial::Renderizar(){
	mapa.Renderizar(janela->renderer, 0);
	titulo.Renderizar(janela->renderer, ((800.0-(double)titulo.PegaDimensao().w)/2.0), 25.0);
	portal.Renderizar(janela->renderer, ((800.0-(double)portal.PegaDimensao().w)/2.0), 310.0, indice);
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