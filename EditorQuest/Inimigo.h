#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Ator.h"
#include "Sprite.h"
#include "Item.h"

class Jogador;
class Mapa;

class Inimigo :
	public Ator
{
protected:
	Jogador* jogador;
	Mapa* mapa;
	Sprite sprite;
	double x, y, direcao, visao;
	unsigned int indicex, indicey, id;
	Atributos atributos;
	Uint32 time, animtime;

public:
	Inimigo(GerenteAtor& _gerente, Jogador* _jogador, Mapa* _mapa);

	virtual SDL_Rect PegaBoundingBox();
	unsigned int PegaTipo();
	Atributos& PegaAtributos();
	double PegaDirecao();
	unsigned int PegaId();

	bool EstaNoJogo();

	void Colidiu(Ator* ator, SDL_Rect* colisao);
	void ColidiuMapa(cMap* tile, SDL_Rect* colisao);
	bool TemVisaoDoJogador();
	
	virtual void Renderizar(SDL_Rect* camera);

	virtual void FoiAtingido(int dano, unsigned int tipo, SDL_Rect* colisao);
	virtual void Inicializar() = 0;
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera) = 0;
	virtual void Finalizar();

};

#endif