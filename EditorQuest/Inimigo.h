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
	unsigned int indice;
	Atributos atributos;
	Uint32 time;

public:
	Inimigo(GerenteAtor& _gerente, Jogador* _jogador, Mapa* _mapa);

	SDL_Rect PegaBoundingBox();
	unsigned int PegaTipo();
	Atributos& PegaAtributos();
	double PegaDirecao();

	bool EstaNoJogo();

	void Colidiu(Ator* ator);
	void ColidiuMapa(cMap* tile, SDL_Rect* colisao);
	bool TemVisaoDoJogador();
	
	void Renderizar(SDL_Rect* camera);

	virtual void FoiAtingido(int dano, unsigned int tipo) = 0;
	virtual void Inicializar() = 0;
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera) = 0;
	virtual void Finalizar() = 0;

};

#endif