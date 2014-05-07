#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"

class Editor :
	public Tela
{
private:
	enum {BTN_MAPA, BTN_INIMIGOS, BTN_ARMADILHAS, BTN_ITENS, BTN_CIMA, BTN_BAIXO, BTN_ESQUERDA, BTN_DIREITA, BTN_MAX};
	enum {EDIT_MAPA, EDIT_INIMIGOS, EDIT_ARMADILHAS, EDIT_ITENS, EDIT_NONE};
	Botao botoes[BTN_MAX];
	Mapa mapa;
	SDL_Rect camera;
	int bordaLateral, bordaHorizontal, estadoEditor, selecionado;
	bool grid;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~Editor();
};

#endif

