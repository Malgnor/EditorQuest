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
	enum { BOTAO_SAIR, BOTAO_VOLTAR, BOTAO_MENUINICIAL, BOTAO_STATUS, BOTAO_INVENTARIO};
	GerenteAtor gerenteAtor;
	SDL_Rect camera;
	Mapa mapa;
	Ator* jogador;
	Botao botoes[5];
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
