#ifndef _HABILIDADES_H_
#define _HABILIDADES_H_

#include "Ator.h"
#include "Sprite.h"
#include <vector>

enum {DANO_FISICO, DANO_MAGICO};

class Habilidades : public Ator
{
protected:
	Sprite sprite;
	double x, y, direcao;
	unsigned int tempodevida, tipo;
	int dano;
	bool vivo;
	Ator* origem;
	std::vector<Ator*> atingidos;

public:
	Habilidades(GerenteAtor& _gerente, Ator* _origem, int _dano);
	
	SDL_Rect PegaBoundingBox();
	
	bool EstaNoJogo();
	unsigned int PegaTipo();
	double PegaDirecao();

	void Colidiu(Ator* ator);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao) = 0;

	virtual void Inicializar() = 0;		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera) = 0;	
	virtual void Renderizar(SDL_Rect* camera) = 0;
	virtual void Finalizar() = 0;
};
#endif
