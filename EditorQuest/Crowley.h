#ifndef _RANGEDDUMMY_H_
#define _RANGEDDUMMY_H_

#include "Inimigo.h"

class Crowley : public Inimigo{
public:
	Crowley(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa);
	SDL_Rect PegaBoundingBox();
	void FoiAtingido(int dano, unsigned int tipo, SDL_Rect* colisao);
	
	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);
	void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif
