#ifndef _DROPITEM_H_
#define _DROPITEM_H_

#include "Ator.h"
#include "Sprite.h"
#include "Item.h"


class DropItem : public Ator
{
private:
	double x, y;
	Item* item;
	Uint32 time;
	bool vivo;

public:
	DropItem(GerenteAtor& _gerente, Item* _item, double _x, double _y);
	
	virtual SDL_Rect PegaBoundingBox();
	
	virtual double PegaDirecao();
	virtual bool EstaNoJogo();
	virtual unsigned int PegaTipo();

	virtual void Colidiu(Ator* ator, SDL_Rect* colisao);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};
#endif