#ifndef _INGAME_H_
#define _INGAME_H_

#include "Tela.h"
#include "Sprite.h"
#include "GerenteAtor.h"
#include "Mapa.h"
#include "Jogador.h"
#include "Botao.h"
#include <sstream>

class Ingame : public Tela
{
private:
	enum { ESTADO_INGAME, ESTADO_PAUSADO, ESTADO_STATUS, ESTADO_INVENTARIO };
	enum { BOTAO_SAIR, BOTAO_VOLTAR, BOTAO_MENUINICIAL, BOTAO_STATUS, BOTAO_INVENTARIO};
	GerenteAtor gerenteAtor;
	SDL_Rect camera;
	Mapa mapa;
	Jogador* jogador;
	Botao botoes[5];
	TTF_Font* fonte;
	std::stringstream status;
	Sprite filtro, txtstatus, skills[3];
	unsigned int estado, invselecionado;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
};

#endif
