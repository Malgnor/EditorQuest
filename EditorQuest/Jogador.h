#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include "Ator.h"
#include "Sprite.h"

class Jogador : public Ator
{
private:
	Sprite sprite;
	double x, y;
	unsigned int indice;

public:
	Jogador(GerenteAtor& _gerente);
	
	virtual SDL_Rect PegaBoundingBox();
	
	virtual bool EstaNoJogo();

	virtual void Colidiu(Ator* ator);

	virtual void Inicializar();		
	virtual void Atualizar();	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};
#endif