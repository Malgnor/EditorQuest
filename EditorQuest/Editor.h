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
		/*MAPA*/ BTN_PROX, BTN_ANT, BTN_LARGURA, BTN_ALTURA, BTN_MODIFICAR, 
		/*INIMIGO*/
		/*ARMADILHA*/
		/*ITENS*/
		/*MENU*/ BTN_SAIR, BTN_SALVAR, BTN_CARREGAR, BTN_MINUS, BTN_PLUS, BTN_ALTNOME, BTN_GRID, 
		BTN_MAX};
	enum {EDIT_MAPA, EDIT_INIMIGOS, EDIT_ARMADILHAS, EDIT_ITENS, EDIT_MENU, EDIT_NONE};
	enum {INPUT_NOME, INPUT_ALTURA, INPUT_LARGURA};
	Botao botoes[BTN_MAX];
	Mapa mapa;
	SDL_Rect camera;
	int bordaLateral, bordaHorizontal, estadoEditor, selecionado, scrollSpeed, mLargura, mAltura, eInput;
	Sprite tileset, scrollSpd, scrollTxt, nomeMapa, larguraTxt, alturaTxt;
	bool grid, input;
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

