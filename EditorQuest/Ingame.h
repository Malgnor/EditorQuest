#ifndef _INGAME_H_
#define _INGAME_H_

#include "Tela.h"
#include "Sprite.h"
#include "GerenteAtor.h"
#include "Mapa.h"
#include "Botao.h"

class Ingame : public Tela
{
private:
	enum { ESTADO_INGAME, ESTADO_PAUSADO, ESTADO_STATUS, ESTADO_INVENTARIO };
	GerenteAtor gerenteAtor;
	SDL_Rect camera;
	Mapa mapa;
	Ator* jogador;
	Botao sair;
	Sprite filtro;
	unsigned int estado;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
};

#endif
