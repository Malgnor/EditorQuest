#include "Lobisomem.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "Claw.h"
#include "DropItem.h"
#include "Item.h"
#include "Equipamento.h"
#include "Consumavel.h"

Lobisomem::Lobisomem(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa) :Inimigo(_gerente, _jogador, _mapa)
{
	x = _x;
	y = _y;
}

SDL_Rect Lobisomem::PegaBoundingBox(){
	SDL_Rect ret = {(int)x+14, (int)y+14, 32, 32};
	return ret;
}

void Lobisomem::FoiAtingido(int dano, unsigned int tipo, SDL_Rect* colisao){
	atributos.hpatual -= dano;
	double d = atan2(y-(double)colisao->y,x-(double)colisao->x);
	x += cos(d)*16;
	y += sin(d)*16;
}

void Lobisomem::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/sprites/lobisomem.png", 46, 46);	
	direcao = 0.0;
	visao = 200.0;
	time = animtime = 0;
	indicex = indicey = 0;
	atributos.hpatual = atributos.hp = 100;
	atributos.hpregen = 1;
	atributos.mpatual = atributos.mp = 100;
	atributos.mpregen = 2;
	atributos.forca = 5;
	atributos.defesa = 5;
	atributos.magia = 5;
}		

void Lobisomem::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	time += deltaTime;
	if(TemVisaoDoJogador()){
		double x1 = jogador->PegaBoundingBox().x;
		double y1 = jogador->PegaBoundingBox().y;
		double dx = x1 - x;
		double dy = y1 - y;
		double dd = sqrt(dx*dx+dy*dy);
		direcao = atan2(dy, dx);
		if(dd > 40){	
			animtime += deltaTime;
			if(animtime >= 300){
				animtime -= 300;
				indicex = (indicex+1)%3;
			}		
			x += cos(direcao)*0.15*deltaTime;
			y += sin(direcao)*0.15*deltaTime;
		}
		if (dd < 55 && time >= 1000){
			time = 0;
			gerente.Adicionar(new Claw(gerente, this, 10));
		}
	} else {
		animtime += deltaTime;
		if(animtime >= 300){
			animtime -= 300;
			indicex = (indicex+1)%3;
		}
		x += cos(direcao)*0.15*deltaTime;
		y += sin(direcao)*0.15*deltaTime;
	}
	if(direcao >= -M_PI/4 && direcao < M_PI/4)
		indicey = 2;
	else if(direcao >= M_PI/4 && direcao < M_PI/4*3)
		indicey = 0;
	else if(direcao >= M_PI/4*3 && direcao < M_PI/4*5)
		indicey = 1;
	else
		indicey = 3;
}	

void Lobisomem::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x - (double)camera->x, y - (double)camera->y, indicex, indicey);
	SDL_Rect hpbar = { (int)x-camera->x+4, (int)y-8-camera->y, (int)((double)atributos.hpatual/(double)atributos.hp*24.0), 5};
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gerente.janela->renderer, &hpbar);
	hpbar.w = 26;
	hpbar.x = (int)x-1-camera->x+4;
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(gerente.janela->renderer, &hpbar);
}

void Lobisomem::Finalizar(){
	Item* item = 0;
	Atributos temp = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
	switch (rand()%11)
	{
	case 0:
		temp.hpatual = temp.hp = 100;
		temp.hpregen = 1;
		temp.mpatual = temp.mp = 100;
		temp.mpregen = 2;
		temp.forca = 5;
		temp.defesa = 5;
		temp.magia = 5;
		item = new Equipamento(gerente.janela->renderer, "Arma", "Uma arma", "resources/espadas/EspadaBastarda.png", temp, EQUIP_ARMA);
		break;
	case 1:
		temp.hpatual = temp.hp = 100;
		temp.hpregen = 1;
		temp.mpatual = temp.mp = 100;
		temp.mpregen = 2;
		temp.forca = 5;
		temp.defesa = 5;
		temp.magia = 5;
		item = new Equipamento(gerente.janela->renderer, "Capacete", "Um capacete", "resources/equipamento/cabeca/ElmoDasCruzadas.png", temp, EQUIP_CABECA);
		break;
	case 2:
		temp.hpatual = temp.hp = 100;
		temp.hpregen = 1;
		temp.mpatual = temp.mp = 100;
		temp.mpregen = 2;
		temp.forca = 5;
		temp.defesa = 5;
		temp.magia = 5;
		item = new Equipamento(gerente.janela->renderer, "Peitoral", "Um peitoral", "resources/equipamento/Peito/ArmaduraDeAco.png", temp, EQUIP_TRONCO);
		break;
	case 3:
		temp.hpatual = temp.hp = 100;
		temp.hpregen = 1;
		temp.mpatual = temp.mp = 100;
		temp.mpregen = 2;
		temp.forca = 5;
		temp.defesa = 5;
		temp.magia = 5;
		item = new Equipamento(gerente.janela->renderer, "Calca", "Uma calca", "resources/equipamento/pernas/Calca de espinhos.png", temp, EQUIP_PERNAS);
		break;
	case 4:
		temp.hpatual = temp.hp = 100;
		temp.hpregen = 1;
		temp.mpatual = temp.mp = 100;
		temp.mpregen = 2;
		temp.forca = 5;
		temp.defesa = 5;
		temp.magia = 5;
		item = new Equipamento(gerente.janela->renderer, "Sapatos", "Um Par de sapatos", "resources/equipamento/pes/BotasDeCouro.png", temp, EQUIP_PES);
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
	case 8:
		temp.hp = 50;
		item = new Consumavel(gerente.janela->renderer, "Pocao de HP+", "Uma pocao % de vida", "resources/imgs/php.png", temp, POCAO_RHP);
		break;
	case 9:
		temp.mp = 75;
		item = new Consumavel(gerente.janela->renderer, "Pocao de MP+", "Uma pocao % de mana", "resources/imgs/pmp.png", temp, POCAO_RMP);
		break;
	case 10:
		temp.hp = 50;
		temp.mp = 50;
		item = new Consumavel(gerente.janela->renderer, "Pocao Hibrida+", "Uma pocao % de vida e mana", "resources/imgs/phpmp.png", temp, POCAO_RHPMP);
		break;
	}
	gerente.Adicionar(new DropItem(gerente, item, x, y));
}
