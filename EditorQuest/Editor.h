#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"
#include <string>

class Editor :
	public Tela
{
private:
	enum {BTN_MAPA, BTN_INIMIGOS, BTN_ARMADILHAS, BTN_ITENS, BTN_MENU,
		/*MAPA*/ BTN_PROX, BTN_ANT,
		/*INIMIGO*/
		/*ARMADILHA*/
		/*ITENS*/
		/*MENU*/ BTN_SAIR, BTN_SALVAR, BTN_MINUS, BTN_PLUS,
		BTN_MAX};
	enum {EDIT_MAPA, EDIT_INIMIGOS, EDIT_ARMADILHAS, EDIT_ITENS, EDIT_MENU, EDIT_NONE};
	Botao botoes[BTN_MAX];
	Mapa mapa;
	SDL_Rect camera;
	int bordaLateral, bordaHorizontal, estadoEditor, selecionado, scrollSpeed;
	Sprite tileset, input, scrollSpd, scrollTxt, nomeMapa;
	bool grid;
	std::string nome;

public:
	Editor(std::string _nome);
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~Editor();
};

#endif

