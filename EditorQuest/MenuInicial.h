#ifndef _MENUINICIAL_H_
#define _MENUINICIAL_H_

#include "Tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"
#include <string>

class Editor;

class MenuInicial : public Tela{
private:
	BotaoPersonalizado jogar, sair;
	Botao altnome;
	Mapa mapa;
	Sprite titulo, portal, nomespr;
	std::string nome;
	unsigned int indice;
	Uint32 time;
	bool resolucao, editor, input;
	bool code[6];
	TTF_Font* fonte;
	SDL_Color cor;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~MenuInicial();

};
#endif