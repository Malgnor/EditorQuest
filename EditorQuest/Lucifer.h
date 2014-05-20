#ifndef _LUCIFER_H_
#define _LUCIFER_H_

#include "Inimigo.h"

class Lucifer : public Inimigo{
public:
	Lucifer(GerenteAtor& _gerente, double _x, double _y, Atributos _atributos, Jogador* _jogador, Mapa* _mapa);
		
	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	void Renderizar(SDL_Rect* camera);
};

#endif
