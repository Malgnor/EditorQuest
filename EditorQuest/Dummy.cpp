#include "Dummy.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "Slash.h"

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
		if(dd > 16)
			direcao = atan2(y1-y, x1-x);
		if (dd < 46 && time >= 1000){
			time = 0;
			gerente.Adicionar(new Slash(gerente, this, 10));
		}
	}
	x += cos(direcao)*0.15*deltaTime;
	y += sin(direcao)*0.15*deltaTime;
}	

void Dummy::Finalizar(){

}
