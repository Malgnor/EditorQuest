#ifndef _GERENTEJANELA_H_
#define _GERENTEJANELA_H_

#include "globaldef.h"
#include <vector>
#define GJanela GerenteJanela::PegaGerenteJanela()

class Janela;

class GerenteJanela{
private:
	GerenteJanela();
	static GerenteJanela* self;
	std::vector<Janela*> janelas;
	Janela* janelafocada;
	friend class Debugger;

public:
	static GerenteJanela& PegaGerenteJanela();
	void Finalizar();

	void Adicionar(Janela* janela);
	void Remover(Janela* janela);
	void Remover(Uint32 id);
	void Remover(const char* titulo);

	void ProcessarEventosW(SDL_Event& evento);
	void Atualizar();
	void Renderizar();

	Janela* PegaJanelaPorID(Uint32 id);
	Janela* PegaJanelaPorTitulo(const char* titulo);
	Janela* PegaJanelaFocada();
	
	void SetaJanelaFocada(Janela* janela);
};
#endif