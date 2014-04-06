#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "Habilidades.h"

class Explosion : public Habilidades
{
public:
	Explosion(GerenteAtor& _gerente, Ator* _origem, int _dano);
	
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif

