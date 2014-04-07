#include "RangedDummy.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "EnergyBall.h"

RangedDummy::RangedDummy(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa) :Inimigo(_gerente, _jogador, _mapa)
{
	x = _x;
	y = _y;
}

void RangedDummy::FoiAtingido(int dano, unsigned int tipo){
	atributos.hpatual -= dano;
}

void RangedDummy::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);	
	direcao = 0.0;
	visao = 300.0;
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

void RangedDummy::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	time += deltaTime;
	if(TemVisaoDoJogador()){
		double x1 = jogador->PegaBoundingBox().x;
		double y1 = jogador->PegaBoundingBox().y;
		double dx = x1 - x;
		double dy = y1 - y;
		double dd = sqrt(dx*dx+dy*dy);
		if(dd > 100){
			x += cos(direcao)*0.15*deltaTime;
			y += sin(direcao)*0.15*deltaTime;
		}
		if (dd < 250 && time >= 1500){
			time = 0;
			gerente.Adicionar(new EnergyBall(gerente, this, 10));
		}
	} else {
		x += cos(direcao)*0.15*deltaTime;
		y += sin(direcao)*0.15*deltaTime;
	}
}	

void RangedDummy::Finalizar(){

}
