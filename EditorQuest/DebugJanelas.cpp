#include "DebugJanelas.h"
#include "Janela.h"
#include "GerenteJanela.h"

using namespace std;

void DebugJanelas::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Debugger - Janelas");
	janela->SetaTamanho(640, 480);
	janela->SetaPosicao(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	janela->Mostrar();

	SDL_Color black = {0, 0, 0};
	txt.str("Texto");
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	texto.CarregaTexturaDoTextoC(janela->PegaRenderder(), txt.str().c_str(), fonte, black);
	x = y = 100;
	r = 0.0;
}

void DebugJanelas::Atualizar(){
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
		texto.CarregaTexturaDoTextoC(janela->PegaRenderder(), txt.str().c_str(), fonte, black);
	}
}

void DebugJanelas::Renderizar(){
	texto.Renderizar(janela->PegaRenderder(), x, y, 0, 0, r);
}

void DebugJanelas::Finalizar(){
	TTF_CloseFont(fonte);
}

Tela* DebugJanelas::ProximaTela(){
	return this;
}
	
DebugJanelas::~DebugJanelas(){
}