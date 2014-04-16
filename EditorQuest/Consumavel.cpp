#include "Consumavel.h"
#include "Jogador.h"
#include "GerenteAtor.h"


Consumavel::Consumavel(SDL_Renderer* renderer, std::string _nome, std::string _descricao, const char* _icone, Atributos _atributos, unsigned int _tipo)
	: Item(renderer, _nome, _descricao, _icone, _atributos, ITEM_CONSUMIVEL), tipopocao(_tipo)
{

}

bool Consumavel::Usar(Jogador* jogador)
{
	Atributos& pa = jogador->PegaAtributos();
	switch (tipopocao)
	{
	case POCAO_FRASCO:
		return false;
		break;
	case POCAO_HP:
		pa.hpatual += atributos.hp;
		break;
	case POCAO_MP:
		pa.mpatual += atributos.mp;
		break;
	case POCAO_HPMP:
		pa.hpatual += atributos.hp;
		pa.mpatual += atributos.mp;
		break;
	case POCAO_RHP:
		pa.hpatual += int((double)atributos.hp/100.0*(double)pa.hp);
		break;
	case POCAO_RMP:
		pa.mpatual += int((double)atributos.mp/100.0*(double)pa.mp);
		break;
	case POCAO_RHPMP:
		pa.hpatual += int((double)atributos.hp/100.0*(double)pa.hp);
		pa.mpatual += int((double)atributos.mp/100.0*(double)pa.mp);
		break;
	}
	jogador->AtualizarAtributos();
	atributos.hp = atributos.mp = 0;
	tipopocao = POCAO_FRASCO;
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	SDL_Color cor = {0, 0, 0};
	SDL_Renderer* renderer = jogador->gerente.janela->renderer;
	nome = "Frasco";
	descricao = "Um frasco vazio";
	icone.CriaTexturaDaImagem(renderer, "resources/imgs/frasco.png");
	txtdesc.CriaTexturaDoTexto(renderer, descricao.c_str(), fonte, cor);
	TTF_CloseFont(fonte);
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	txtnome.CriaTexturaDoTexto(renderer, nome.c_str(), fonte, cor);
	TTF_CloseFont(fonte);
	return true;
}

unsigned int Consumavel::pegaTipoPocao()
{
	return tipopocao;
}
