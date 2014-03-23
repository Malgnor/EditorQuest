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
	std::vector<Janela*> removidos;
	Janela* janelafocada;

#ifdef DEBUG
	friend class DebugJanelas;
#endif

public:
	static GerenteJanela& PegaGerenteJanela();
	void Finalizar();

	void Adicionar(Janela* janela);
	void Remover(Janela* janela);
	void Remover(Uint32 id);
	void Remover(const char* titulo);

	void ProcessarEventosW(SDL_Event& evento);
	void Atualizar(Uint32 deltaTime);
	void Renderizar();

	Janela* PegaJanelaPorID(Uint32 id);
	Janela* PegaJanelaPorTitulo(const char* titulo);
	Janela* PegaJanelaFocada();

	unsigned int PegaQtdJanelas();
	
	void SetaJanelaFocada(Janela* janela);
};
#endif