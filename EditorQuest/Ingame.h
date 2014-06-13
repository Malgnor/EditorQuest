#ifndef _INGAME_H_
#define _INGAME_H_

#include "Tela.h"
#include "Sprite.h"
#include "GerenteAtor.h"
#include "Mapa.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "BotaoPersonalizado.h"
#include <sstream>

class Ingame : public Tela
{
private:
	enum { ESTADO_INGAME, ESTADO_WIN, ESTADO_LOSE, ESTADO_PAUSADO, ESTADO_STATUS, ESTADO_INVENTARIO };
	enum { BOTAO_SAIR, BOTAO_VOLTAR, BOTAO_MENUINICIAL, BOTAO_STATUS, BOTAO_INVENTARIO, BOTAO_USAR, BOTAO_USAR2, BOTAO_DESTRUIR, BOTAO_RETRY, BOTAO_PROX, BOTAO_QTD};
	GerenteAtor gerenteAtor;
	SDL_Rect camera;
	Mapa mapa;
	Jogador* jogador;
	Inimigo* boss;
	BotaoPersonalizado botoes[BOTAO_QTD];
	TTF_Font* fonte;
	std::stringstream status;
	std::string perfil, proxMapa, mapatual;
	Sprite filtro, txtstatus, skills[3], gameover, victory;
	unsigned int estado, invselecionado;
	bool extra;

public:
	Ingame(std::string nome);
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
};

#endif
