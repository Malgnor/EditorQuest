#ifndef _ATOR_H_
#define _ATOR_H_

class GerenteAtor;
struct SDL_Rect;

class Ator
{
protected:
	GerenteAtor& gerente;

public:		
	Ator(GerenteAtor& _gerente);
	
	virtual SDL_Rect PegaBoundingBox() = 0;
	
	virtual bool EstaNoJogo()	= 0;

	virtual void Colidiu(Ator* ator);

	virtual void Inicializar()	= 0;		
	virtual void Atualizar()	= 0;	
	virtual void Renderizar(SDL_Rect* camera)	= 0;
	virtual void Finalizar()	= 0;

	virtual ~Ator() {};
};

#endif
