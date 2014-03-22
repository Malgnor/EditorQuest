#ifndef _ATOR_H_
#define _ATOR_H_

#ifndef _INPUT_
#define _INPUT_
#define PegaTecla gerente.janela->entrada.pegaTecla
#define PegaMouse gerente.janela->entrada.pegaMouse
#endif

class GerenteAtor;
struct SDL_Rect;

class Ator
{
protected:
	GerenteAtor& gerente;

public:		
	Ator(GerenteAtor& _gerente);
	
	virtual SDL_Rect PegaBoundingBox() = 0;
	
	virtual bool EstaNoJogo() = 0;

	virtual void Colidiu(Ator* ator) = 0;

	virtual void Inicializar() = 0;		
	virtual void Atualizar() = 0;	
	virtual void Renderizar(SDL_Rect* camera) = 0;
	virtual void Finalizar() = 0;

	virtual ~Ator() {};
};

#endif
