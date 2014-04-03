#ifndef _SLASH_H_
#define _SLASH_H_

#include "Ator.h"
#include "Sprite.h"
class Jogador;

class Slash : public Ator
{
private:
	Sprite sprite;
	double x, y, direcao, direcao2;
	unsigned int indice, tempodevida;
	bool vivo;
	Jogador* jogador;

public:
	Slash(GerenteAtor& _gerente, Jogador* _jogador);
	
	virtual SDL_Rect PegaBoundingBox();
	
	virtual bool EstaNoJogo();
	virtual unsigned int PegaTipo();

	virtual void Colidiu(Ator* ator);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};

#endif

