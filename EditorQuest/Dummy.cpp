#include "Dummy.h"
#include "GerenteAtor.h"
#include "Jogador.h"

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
		direcao = atan2(y1-y, x1-x);
	}
	x += cos(direcao)*0.15*deltaTime;
	y += sin(direcao)*0.15*deltaTime;
}	

void Dummy::Finalizar(){

}
