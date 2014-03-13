#include "Debugger.h"
#include "Jogo.h"
#include "GerenteJanela.h"

using namespace std;

Debugger::Debugger(){	
	renderer = NULL;
	window = NULL;
	this->Inicializar();
	GJanela.Adicionar(this);
}

Debugger::~Debugger(){
	GJanela.Remover(this);
}

void Debugger::Inicializar(){
	window = SDL_CreateWindow("Debugger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Color black = {0, 0, 0};
	txt.str("Texto");
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	texto.CarregaTexturaDoTextoC(renderer, txt.str().c_str(), fonte, black);
	x = y = 6;
}

void Debugger::ProcessarEventos(SDL_Event& evento){
	if(evento.key.keysym.sym == SDLK_KP_PLUS && evento.key.state == SDL_RELEASED)
		new Jogo;
	if(evento.type == SDL_MOUSEWHEEL)
		y += evento.wheel.y*10;
}

void Debugger::Atualizar(){
	SDL_Color black = {0, 0, 0};
	int x, y;
	stringstream ntxt;
	ntxt.str("");
	ntxt << "Janelas ativas: " << GJanela.janelas.size() << endl;
	if(!GJanela.janelas.empty())
		for(Janela* j: GJanela.janelas){
			j->PegaPosicao(x, y);
			ntxt << "Janela ID: " << j->PegaID() << " Titulo: " << j->PegaTitulo() << " (" << x << ", " << y << ") (";
			j->PegaTamanho(x, y);
			ntxt << x << ", " << y << ") Foco: " << ((GJanela.PegaJanelaFocada() == j) ? "V" : "F") << endl;
		}
	if(ntxt.str() != txt.str()){
		txt.str(ntxt.str());
		texto.CarregaTexturaDoTextoC(renderer, txt.str().c_str(), fonte, black);
	}
}

void Debugger::Renderizar(){
	SDL_RenderClear(renderer);
	texto.Renderizar(renderer, x, y);
	SDL_RenderPresent(renderer);
}

void Debugger::Encerrar(){
	TTF_CloseFont(fonte);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
}
