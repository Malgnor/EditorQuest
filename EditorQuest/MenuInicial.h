#ifndef _MENUINICIAL_H_
#define _MENUINICIAL_H_

#include "Tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"

class MenuInicial : public Tela{
private:
	BotaoPersonalizado jogar, sair;
	Mapa mapa;
	Sprite titulo, portal;
	unsigned int indice;
	Uint32 time;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~MenuInicial();

};
#endif