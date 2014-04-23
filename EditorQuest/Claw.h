#ifndef _CLAW_H_
#define _CLAW_H_

#include "Habilidades.h"

class Claw : public Habilidades
{
private:
	double direcao2;

public:
	Claw(GerenteAtor& _gerente, Ator* _origem, int dano);

	SDL_Rect PegaBoundingBox();
	
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif

