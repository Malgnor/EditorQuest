#include "Item.h"
#include <sstream>

using namespace std;

Item::Item()
	: nome(""), descricao(""), tipo(0)
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

Item::Item(SDL_Renderer* renderer, string _nome, string _descricao, Atributos _atributos, unsigned int _tipo, unsigned int x, unsigned int y)
	: nome(_nome), descricao(_descricao), atributos(_atributos), tipo(_tipo)
{
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	icone.CriaTexturaIcone(renderer, x, y);
	txtnome.CriaTexturaDoTexto(renderer, nome.c_str(), fonte, cor);
	TTF_CloseFont(fonte);
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	stringstream status;
	status.str("");
	status << descricao;
		if(atributos.hp)
	status << "\nHP += " << atributos.hp;
		if(atributos.mp)
	status << "\nMP += " << atributos.mp;
		if(atributos.hpregen || atributos.mpregen)
	status << "\nHPRegen/MPRegen += " << atributos.hpregen << "/" << atributos.mpregen;
		if(atributos.forca)
	status << "\nForca += " << atributos.forca;
		if(atributos.defesa)
	status << "\nDefesa += " << atributos.defesa;
		if(atributos.magia)
	status << "\nMagia += " << atributos.magia;
	txtdesc.CriaTexturaDoTextoC(renderer, status.str().c_str(), fonte, cor, 500);	
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

unsigned int Item::PegaTipo(){
	return tipo;
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