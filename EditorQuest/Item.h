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
	unsigned int tipo, x, y;

public:
	Item();
	Item(SDL_Renderer* renderer, std::string _nome, std::string _descricao, Atributos _atributos, unsigned int _tipo, unsigned int x, unsigned int y);

	virtual bool Usar(Jogador* jogador) = 0;

	std::string PegaNome();
	std::string PegaDescricao();
	Atributos& PegaAtributos();
	unsigned int PegaTipo();
	Sprite& PegaIcone();
	Sprite& PegaTxtNome();
	Sprite& PegaTxtDesc();
	void PegaXY(unsigned int &_x, unsigned int &_y);
};

#endif
