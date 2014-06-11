#ifndef _CONSUMAVEL_H_
#define _CONSUMAVEL_H_

#include "Item.h"

enum { POCAO_HP, POCAO_MP, POCAO_HPMP, POCAO_RHP, POCAO_RMP, POCAO_RHPMP, POCAO_FRASCO};

class Consumavel : public Item
{
private:
	unsigned int tipopocao;

public:
	Consumavel(SDL_Renderer* renderer, std::string _nome, std::string _descricao, Atributos _atributos, unsigned int _tipo);
	virtual bool Usar(Jogador* jogador);
	unsigned int pegaTipoPocao();
};
#endif


