#ifndef _INGAME_H_
#define _INGAME_H_

#include "Tela.h"
#include "Sprite.h"
#include "GerenteAtor.h"
#include "Mapa.h"

class Ingame : public Tela
{
private:
	GerenteAtor gerenteAtor;
	SDL_Rect camera;
	Mapa mapa;

public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar(Uint32 deltaTime);
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
};

#endif
