#include "Item.h"

using namespace std;

Item::Item()
	: nome(""), descricao("")
{
	atributos.hp = 0;
	atributos.hpatual = 0;
	atributos.hpregen = 0;
	atributos.mp = 0;
	atributos.mpatual = 0;
	atributos.mpregen = 0;
	atributos.forca = 0;
	atributos.defesa = 0;
	atributos.magia = 0;
}

Item::Item(SDL_Renderer* renderer, string _nome, string _descricao, const char* _icone, Atributos _atributos)
	: nome(_nome), descricao(_descricao), atributos(_atributos)
{
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	icone.CriaTexturaDaImagem(renderer, _icone);
	txtdesc.CriaTexturaDoTexto(renderer, descricao.c_str(), fonte, cor);
	txtnome.CriaTexturaDoTexto(renderer, nome.c_str(), fonte, cor);
	TTF_CloseFont(fonte);
}

string Item::PegaNome(){
	return nome;
}

string Item::PegaDescricao(){
	return descricao;
}

Atributos Item::PegaAtributos(){
	return atributos;
}

Sprite& Item::PegaIcone(){
	return icone;
}

Sprite& Item::PegaTxtNome(){
	return txtnome;
}

Sprite& Item::PegaTxtDesc(){
	return txtdesc;
}