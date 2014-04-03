#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Ator.h"
#include "Sprite.h"
#include "Item.h"

class Inimigo :
	public Ator
{
private:
	Sprite sprite;
	double x, y, direcao;
	unsigned int indice;
	Atributos atributos;
	Uint32 time;

public:
	Inimigo(GerenteAtor& _gerente);
	SDL_Rect PegaBoundingBox();
	unsigned int PegaTipo();
	Atributos& PegaAtributos();

	bool EstaNoJogo();

	void Colidiu(Ator* ator);
	void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar() = 0;
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera) = 0;
	void Renderizar(SDL_Rect* camera);
	void Finalizar();

};

#endif