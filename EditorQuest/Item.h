#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "Sprite.h"

struct Atributos{
	int hp;
	int hpatual;
	int hpregen;
	int mp;
	int mpatual;
	int mpregen;
	int forca;
	int defesa;
	int magia;
};

class Jogador;

enum {ITEM_EQUIPAMENTO, ITEM_CONSUMIVEL};

class Item{
protected:
	std::string nome;
	std::string descricao;
	Sprite icone, txtnome, txtdesc;
	Atributos atributos;
	unsigned int tipo;

public:
	Item();
	Item(SDL_Renderer* renderer, std::string _nome, std::string _descricao, const char* _icone, Atributos , unsigned int _tipo);

	virtual bool Usar(Jogador* jogador) = 0;

	std::string PegaNome();
	std::string PegaDescricao();
	Atributos PegaAtributos();
	unsigned int PegaTipo();
	Sprite& PegaIcone();
	Sprite& PegaTxtNome();
	Sprite& PegaTxtDesc();
};

#endif
