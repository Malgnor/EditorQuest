#include "DebugJanelas.h"
#ifdef DEBUG
#include "Janela.h"
#include "GerenteJanela.h"

using namespace std;

void DebugJanelas::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Debugger - Janelas");
	int w, h;
	janela->PegaTamanho(w, h);
	if( w != 640 && h != 480){
		janela->SetaTamanho(640, 480);
		janela->SetaPosicao(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	}
	janela->SetaCorFundo(255, 255, 255);
	janela->Mostrar();

	SDL_Color black = {0, 0, 0};
	txt.str("Texto");
	fonte[0] = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	fonte[1] = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	fonte[2] = TTF_OpenFont("resources/fonts/pix.ttf", 8);
	texto.CriaTexturaDoTextoC(janela->PegaRenderer(), txt.str().c_str(), fonte[0], black, 640);
	menu[0].CriaTexturaMenu(janela->PegaRenderer(), "resources/imgs/botaog.png", "Menu", fonte[0], black);
	menu[1].CriaTexturaMenu(janela->PegaRenderer(), "resources/imgs/botaog.png", "Menu Longo", fonte[1], black);
	menu[2].CriaTexturaMenu(janela->PegaRenderer(), "resources/imgs/botaog.png", "Menu muito longo", fonte[2], black);
	menu[3].CriaTexturaMenu(janela->PegaRenderer(), "resources/imgs/botaog.png", "Menu muito longo mesmo", fonte[1], black);
	menu[4].CriaTexturaMenu(janela->PegaRenderer(), "resources/imgs/botaog.png", "M", fonte[2], black);
	x = y = 10;
	r = 0.0;
}

void DebugJanelas::Atualizar(){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	y += 10*Mouse->wy;
	if(Teclas[FW_ESQUERDA].ativo)
		r--;
	if(Teclas[FW_DIREITA].ativo)
		r++;

	SDL_Color black = {0, 0, 0};
	int x, y;
	stringstream ntxt;
	ntxt.str("");
	ntxt << "Janelas ativas: " << GJanela.janelas.size() << endl;
	if(!GJanela.janelas.empty())
		for(Janela* j: GJanela.janelas){
			if(j->Existe()){
				j->PegaPosicao(x, y);
				ntxt << "ID: " << j->PegaID() << " Titulo: " << j->PegaTitulo() << " (" << x << ", " << y << ") (";
				j->PegaTamanho(x, y);
				ntxt << x << ", " << y << ") Foco: " << ((GJanela.PegaJanelaFocada() == j) ? "V" : "F") << endl;
			}
		}
	if(ntxt.str() != txt.str()){
		txt.str(ntxt.str());
		texto.CriaTexturaDoTextoC(janela->PegaRenderer(), txt.str().c_str(), fonte[0], black, 640);
	}
}

void DebugJanelas::Renderizar(){
	texto.Renderizar(janela->PegaRenderer(), (double)x, (double)y, 0, 0, r);
	menu[0].Renderizar(janela->PegaRenderer(), 320.0-menu[0].PegaDimensao().w/2, 200.0);
	menu[1].Renderizar(janela->PegaRenderer(), 320.0-menu[1].PegaDimensao().w/2, 240.0);
	menu[2].Renderizar(janela->PegaRenderer(), 320.0-menu[2].PegaDimensao().w/2, 280.0);
	menu[3].Renderizar(janela->PegaRenderer(), 320.0-menu[3].PegaDimensao().w/2, 320.0);
	menu[4].Renderizar(janela->PegaRenderer(), 320.0-menu[4].PegaDimensao().w/2, 160.0);
}

void DebugJanelas::Finalizar(){
	TTF_CloseFont(fonte[0]);
	TTF_CloseFont(fonte[1]);
	TTF_CloseFont(fonte[2]);
}

Tela* DebugJanelas::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado)
		return nullptr;
	if(PegaTecla()[FW_ESC].pressionado)
		return new DebugJanelas();
	return this;
}
	
DebugJanelas::~DebugJanelas(){
}

#endif