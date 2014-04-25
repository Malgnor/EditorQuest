#include "Lucifer.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "EnergyBall.h"
#include "Slash.h"

Lucifer::Lucifer(GerenteAtor& _gerente, double _x, double _y, Jogador* _jogador, Mapa* _mapa) :Inimigo(_gerente, _jogador, _mapa)
{
	x = _x;
	y = _y;
}

void Lucifer::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/sprites/lucifer.png", 32, 32);	
	direcao = 0.0;
	visao = 250.0;
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

void Lucifer::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
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
		if(time >= 1500){
			if (dd < 250 && dd > 55){
				time = 0;
				gerente.Adicionar(new EnergyBall(gerente, this, 10));
			} else if( dd < 55){
				time = 0;
				gerente.Adicionar(new Slash(gerente, this, 10));
			}
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

void Lucifer::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x - (double)camera->x, y - (double)camera->y, indicex, indicey);
	SDL_Rect hpbar = { (int)x-camera->x+4, (int)y-8-camera->y, (int)((double)atributos.hpatual/(double)atributos.hp*24.0), 5};
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gerente.janela->renderer, &hpbar);
	hpbar.w = 26;
	hpbar.x = (int)x-1-camera->x+4;
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(gerente.janela->renderer, &hpbar);
}