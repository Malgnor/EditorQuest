#ifndef _EQUIPAMENTO_H_
#define _EQUIPAMENTO_H_

#include "Item.h"

class Equipamento : public Item
{
private:
	bool equipado;
	unsigned int slot;

public:
	Equipamento(SDL_Renderer* renderer, std::string _nome, std::string _descricao, Atributos _atributos, unsigned int slot, unsigned int x);
	virtual bool Usar(Jogador* jogador);
	unsigned int PegaSlot();
	bool EstaEquipado();
};
#endif
