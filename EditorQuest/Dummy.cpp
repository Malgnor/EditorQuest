#include "Dummy.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "Slash.h"
#include "DropItem.h"
#include "Item.h"
#include "Equipamento.h"
#include "Consumavel.h"

Dummy::Dummy(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa) :Inimigo(_gerente, _jogador, _mapa)
{
	x = _x;
	y = _y;
}

void Dummy::FoiAtingido(int dano, unsigned int tipo){
	atributos.hpatual -= dano;
}

void Dummy::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);	
	direcao = 0.0;
	visao = 200.0;
	time = 0;
	indice = 1;
	atributos.hpatual = atributos.hp = 100;
	atributos.hpregen = 1;
	atributos.mpatual = atributos.mp = 100;
	atributos.mpregen = 2;
	atributos.forca = 5;
	atributos.defesa = 5;
	atributos.magia = 5;
}		

void Dummy::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	time += deltaTime;
	if(TemVisaoDoJogador()){
		double x1 = jogador->PegaBoundingBox().x;
		double y1 = jogador->PegaBoundingBox().y;
		double dx = x1 - x;
		double dy = y1 - y;
		double dd = sqrt(dx*dx+dy*dy);
		direcao = atan2(y1-y, x1-x);
		if(dd > 40){			
			x += cos(direcao)*0.15*deltaTime;
			y += sin(direcao)*0.15*deltaTime;
		}
		if (dd < 55 && time >= 1000){
			time = 0;
			gerente.Adicionar(new Slash(gerente, this, 10));
		}
	} else {
		x += cos(direcao)*0.15*deltaTime;
		y += sin(direcao)*0.15*deltaTime;
	}
}	

void Dummy::Finalizar(){
	Item* item = 0;
	Atributos temp = atributos;
	switch (rand()%8)
	{
	case 0:
		item = new Equipamento(gerente.janela->renderer, "Arma", "Uma arma", "resources/imgs/A.png", temp, EQUIP_ARMA);
		break;
	case 1:
		item = new Equipamento(gerente.janela->renderer, "Capacete", "Um capacete", "resources/imgs/C.png", temp, EQUIP_CABECA);
		break;
	case 2:
		item = new Equipamento(gerente.janela->renderer, "Peitoral", "Um peitoral", "resources/imgs/T.png", temp, EQUIP_TRONCO);
		break;
	case 3:
		item = new Equipamento(gerente.janela->renderer, "Luvas", "Um par de luvas", "resources/imgs/M.png", temp, EQUIP_MAOS);
		break;
	case 4:
		item = new Equipamento(gerente.janela->renderer, "Sapatos", "Um Par de sapatos", "resources/imgs/P.png", temp, EQUIP_PES);
		break;
	case 5:
		temp.hp = 50;
		item = new Consumavel(gerente.janela->renderer, "Pocao de HP", "Uma pocao de vida", "resources/imgs/php.png", temp, POCAO_HP);
		break;
	case 6:
		temp.mp = 75;
		item = new Consumavel(gerente.janela->renderer, "Pocao de MP", "Uma pocao de mana", "resources/imgs/pmp.png", temp, POCAO_MP);
		break;
	case 7:
		temp.hp = 50;
		temp.mp = 50;
		item = new Consumavel(gerente.janela->renderer, "Pocao Hibrida", "Uma pocao de vida e mana", "resources/imgs/phpmp.png", temp, POCAO_HPMP);
		break;
	}
	gerente.Adicionar(new DropItem(gerente, item, x, y));
}
