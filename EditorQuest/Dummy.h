#ifndef _DUMMY_H_
#define _DUMMY_H_

#include "Ator.h"
#include "Sprite.h"

class Dummy : public Ator
{
private:
	double x, y;
	bool vivo;
	Sprite sprite;
public:
	Dummy(GerenteAtor& _gerente, double _x, double _y);

	void FoiAtingido();
	
	virtual SDL_Rect PegaBoundingBox();
	virtual unsigned int PegaTipo();
	
	virtual bool EstaNoJogo();

	virtual void Colidiu(Ator* ator);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif
