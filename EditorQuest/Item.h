#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "Sprite.h"

struct Atributos{
	int hp;
	int hpregen;
	int mp;
	int mpregen;
	int forca;
	int defesa;
	int magia;
};

class Item{
private:
	std::string nome;
	std::string descricao;
	Sprite icone, txtnome, txtdesc;
	Atributos atributos;

public:
	Item();
	Item(SDL_Renderer* renderer, std::string _nome, std::string _descricao, const char* _icone, Atributos _atributos);
	std::string PegaNome();
	std::string PegaDescricao();
	Atributos PegaAtributos();
	Sprite& PegaIcone();
	Sprite& PegaTxtNome();
	Sprite& PegaTxtDesc();
};

#endif
