#include "Equipamento.h"
#include "Jogador.h"

Equipamento::Equipamento(SDL_Renderer* renderer, std::string _nome, std::string _descricao, const char* _icone, Atributos _atributos, unsigned int _slot)
	: Item(renderer, _nome, _descricao, _icone, _atributos, ITEM_EQUIPAMENTO), equipado(false), slot(_slot){}

bool Equipamento::Usar(Jogador* jogador){
	Item** inventario = jogador->PegaInventario();
	Equipamento** equipamentos = jogador->PegaEquipamentos();
	if(equipado){
		for(int i = 0; i < 10; i++){
			if(inventario[i] != 0)
				continue;
			inventario[i] = this;
			equipamentos[slot] = 0;
			equipado = false;				
			jogador->AtualizarAtributos();
			return true;
		}
	} else {
		if(equipamentos[slot] != 0){
			for(int i = 0; i < 10; i++){
				if(inventario[i] != (Item*)this)
					continue;
				inventario[i] = (Item*)equipamentos[slot];
				equipamentos[slot] = this;
				equipado = true;				
				jogador->AtualizarAtributos();
				return true;
			}
		} else {
			for(int i = 0; i < 10; i++){
				if(inventario[i] != (Item*)this)
					continue;
				inventario[i] = 0;
				equipamentos[slot] = this;
				equipado = true;				
				jogador->AtualizarAtributos();
				return true;
			}
		}
	}
	return false;
}

unsigned int Equipamento::PegaSlot(){
	return slot;
}

bool Equipamento::EstaEquipado(){
	return equipado;
}