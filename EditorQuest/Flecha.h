#ifndef _FLECHA_H_
#define _FLECHA_H_

#include "Habilidades.h"

class Flecha : public Habilidades
{

public:
	Flecha(GerenteAtor& _gerente, Ator* _origem, int _dano);
	
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif

