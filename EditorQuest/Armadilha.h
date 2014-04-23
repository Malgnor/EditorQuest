#ifndef _ARMADILHA_H_
#define _ARMADILHA_H_

#include "Ator.h"

enum {ARMADILHA_FLECHA, ARMADILHA_ESPINHOS};

class Armadilha : public Ator
{
private:
	unsigned int tipo;
	Uint32 time;
	double x, y, direcao;

public:
	Armadilha(GerenteAtor& _gerente, double _x, double _y, double _direcao, unsigned int _tipo);

	unsigned int PegaTipoArmadilha();

	virtual SDL_Rect PegaBoundingBox();
	virtual unsigned int PegaTipo();
	virtual double PegaDirecao();
	
	virtual bool EstaNoJogo();

	virtual void Colidiu(Ator* ator, SDL_Rect* colisao);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};
#endif
