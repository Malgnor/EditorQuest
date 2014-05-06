#ifndef _LOBISOMEM_H_
#define _LOBISOMEM_H_

#include "Inimigo.h"

class Lobisomem : public Inimigo{
public:
	Lobisomem(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa);
	
	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);
	void Renderizar(SDL_Rect* camera);
};

#endif
