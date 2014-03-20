#pragma once

class GerenteAtor;

class Ator
{
protected:
	GerenteAtor& gerente;

public:		
	Ator(GerenteAtor& _gerente);

	virtual float PegaX()		= 0;
	virtual float PegaY()		= 0;
	
	virtual bool EstaNoJogo()	= 0;
	virtual void Inicializar()	= 0;		
	virtual void Atualizar()	= 0;	
	virtual void Renderizar()	= 0;
	virtual void Finalizar()	= 0;
	virtual ~Ator() {};
};

