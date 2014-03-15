#ifndef _MENUINICIAL_H_
#define _MENUINICIAL_H_

#include "Tela.h"
#include "Sprite.h"

class MenuInicial : public Tela{
private:
	Sprite t, t_;
	double x1, x2, y1, y2;
	Uint8 ind1, ind2;
public:
	virtual void Inicializar(Janela* _janela);
	virtual void Atualizar();
	virtual void Renderizar();
	virtual void Finalizar();

	virtual Tela* ProximaTela();
	
	~MenuInicial();

};
#endif