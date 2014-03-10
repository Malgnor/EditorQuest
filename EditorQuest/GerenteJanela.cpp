#include "GerenteJanela.h"
#include "Janela.h"

GerenteJanela* GerenteJanela::self = 0;

GerenteJanela::GerenteJanela(){
	janelafocada = 0;
}

GerenteJanela& GerenteJanela::PegaGerenteJanela(){
	if(!self) self = new GerenteJanela();
	return *self;
}

void GerenteJanela::Finalizar(){
	if(self){
		if(!janelas.empty()){
			for(Janela* j:janelas){
				delete j;
				j = 0;
			}
			janelas.clear();
			janelafocada = 0;
		}
		delete self;
		self = 0;
	}
}

void GerenteJanela::Adicionar(Janela* janela){
	janelas.push_back(janela);
	janelafocada = janela;
}

void GerenteJanela::Remover(Janela* janela){
	if(!janelas.empty())
		for(Janela* j: janelas)
			if(j == janela)
				j->Encerrar();
}

void GerenteJanela::Remover(Uint32 id){
	if(!janelas.empty())
		for(Janela* j: janelas)
			if(j->PegaID() == id)
				j->Encerrar();
}

void GerenteJanela::Remover(const char* titulo){
	if(!janelas.empty())
		for(Janela* j: janelas)
			if(j->PegaTitulo() == titulo)
				j->Encerrar();
}

void GerenteJanela::ProcessarEventos(SDL_Event& evento){
	if(!janelas.empty())
		for(Janela* j: janelas)
			j->ProcessarEventos(evento);		
}

void GerenteJanela::Atualizar(){
	std::vector<Janela*> removidos;
	std::vector<Janela*> ativos;
	if(!janelas.empty())
		for(Janela* j: janelas){
			if(j->Existe()){
				j->Atualizar();
				ativos.push_back(j);
			} else
				removidos.push_back(j);
		}
	swap(janelas, ativos);
	if(!removidos.empty())
		for(Janela* j: removidos)
			delete j;
}

void GerenteJanela::Renderizar(){
	if(!janelas.empty())
		for(Janela* j: janelas)
			j->Renderizar();
}

Janela* GerenteJanela::PegaJanelaPorID(Uint32 id){
	if(!janelas.empty())
		for(Janela* j: janelas)
			if(j->PegaID() == id)
				return j;
	return 0;
}

Janela* GerenteJanela::PegaJanelaPorTitulo(const char* titulo){
	if(!janelas.empty())
		for(Janela* j: janelas)
			if(j->PegaTitulo() == titulo)
				return j;
	return 0;
}

Janela* GerenteJanela::PegaJanelaFocada(){
	return janelafocada;
}

void GerenteJanela::SetaJanelaFocada(Janela* janela){
	janelafocada = janela;
}