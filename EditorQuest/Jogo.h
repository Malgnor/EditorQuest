#ifndef _JOGO_H_
#define _JOGO_H_

#include "Janela.h"

class Jogo : public Janela
{
public:
	Jogo();
	virtual void Inicializar();
	virtual void Renderizar();
	virtual void Encerrar();
	~Jogo();
};
#endif