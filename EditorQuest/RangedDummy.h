#ifndef _RANGEDDUMMY_H_
#define _RANGEDDUMMY_H_

#include "Inimigo.h"

class RangedDummy : public Inimigo{
public:
	RangedDummy(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa);

	void FoiAtingido(int dano, unsigned int tipo);
	
	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Finalizar();
};

#endif
