#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include "Janela.h"
#include "Sprite.h"
#include <sstream>

class Debugger : public Janela
{
private:
	TTF_Font *fonte;
	int x, y;
	double r;
	Sprite texto;
	std::stringstream txt;

public:
	Debugger();
	~Debugger();

	virtual void Inicializar();
	virtual void ProcessarEventos(SDL_Event& evento);
	virtual void Atualizar();
	virtual void Renderizar();
	virtual void Encerrar();
};
#endif