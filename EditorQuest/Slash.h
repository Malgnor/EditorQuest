#ifndef _SLASH_H_
#define _SLASH_H_

#include "Habilidades.h"

class Slash : public Habilidades
{
private:
	double direcao2;

public:
	Slash(GerenteAtor& _gerente, Ator* _origem, int dano);
	
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif

