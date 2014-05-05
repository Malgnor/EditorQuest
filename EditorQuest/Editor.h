#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "tela.h"
#include "BotaoPersonalizado.h"
#include "Mapa.h"

class Editor :
	public Tela
{
private:
	Sprite titulo;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~Editor();
};

#endif

