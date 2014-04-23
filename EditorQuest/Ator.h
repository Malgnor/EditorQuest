#ifndef _ATOR_H_
#define _ATOR_H_

#ifndef _INPUT_
#define _INPUT_
#define PegaTecla gerente.janela->entrada.pegaTecla
#define PegaMouse gerente.janela->entrada.pegaMouse
#endif

#include "globaldef.h"
class GerenteAtor;
struct cMap;

enum {ATOR_SEMCOLISAO, ATOR_JOGADOR, ATOR_HABILIDADE, ATOR_INIMIGO, ATOR_ARMADILHA, ATOR_ITEM};

class Ator
{
public:		
	GerenteAtor& gerente;

	Ator(GerenteAtor& _gerente);
	
	virtual SDL_Rect PegaBoundingBox() = 0;
	virtual unsigned int PegaTipo() = 0;
	virtual double PegaDirecao() = 0;
	
	virtual bool EstaNoJogo() = 0;

	virtual void Colidiu(Ator* ator, SDL_Rect* colisao) = 0;
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao) = 0;

	virtual void Inicializar() = 0;		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera) = 0;	
	virtual void Renderizar(SDL_Rect* camera) = 0;
	virtual void Finalizar() = 0;

	virtual ~Ator() {};
};

#endif
