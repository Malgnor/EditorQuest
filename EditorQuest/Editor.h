#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"
#include "Inimigo.h"
#include "Armadilha.h"
#include "GerenteAtor.h"
#include <vector>
#include <string>

struct StatBtn{
	Botao botao;
	int data, min, estado;
	Sprite sprite;
};

class Editor :
	public Tela
{
private:
	enum {BTN_MAPA, BTN_INIMIGOS, BTN_ARMADILHAS, BTN_ITENS, BTN_MENU,
		/*MAPA*/ BTN_PROX, BTN_ANT, BTN_MODIFICAR, 
		/*INIMIGO*/ BTN_BOSS, BTN_REMOVER, 
		/*ARMADILHA*/
		/*ITENS*/
		/*MENU*/ BTN_SAIR, BTN_SALVAR, BTN_CARREGAR, BTN_MINUS, BTN_PLUS, BTN_ALTNOME, BTN_GRID, 
		BTN_MAX};
	enum {EDIT_MAPA, EDIT_INIMIGOS, EDIT_ARMADILHAS, EDIT_ITENS, EDIT_MENU, EDIT_NONE};
	enum {/*MAPA*/ STAT_ALTURA, STAT_LARGURA,
		  /*INIMIGO*/ STAT_HP, STAT_HPR, STAT_FORCA, STAT_DEFESA, STAT_MAGIA,
		  /*ARMADILHA*/ STAT_DIR, STAT_DANO, 
		  STAT_MAX};
	Botao botoes[BTN_MAX];
	StatBtn stats[STAT_MAX];
	Mapa mapa;
	SDL_Rect camera;
	int bordaLateral, bordaHorizontal, estadoEditor, selecionado, scrollSpeed;
	Sprite tileset, scrollSpd, scrollTxt, nomeMapa, mobset, armset;
	bool grid, input, edit;
	GerenteAtor gerenteAtores;
	std::string nome;
	std::vector<Inimigo*> inimigos;
	Inimigo* inisel;
	std::vector<Armadilha*> armadilhas;
	Armadilha* armsel;

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

