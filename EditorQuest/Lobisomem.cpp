#include "Lobisomem.h"
#include "GerenteAtor.h"
#include "Jogador.h"
#include "Claw.h"

Lobisomem::Lobisomem(GerenteAtor& _gerente, double _x, double _y, Atributos _atributos, Jogador* _jogador, Mapa* _mapa) :Inimigo(_gerente, _jogador, _mapa)
{
	x = _x;
	y = _y;
	atributos = _atributos;
	id = 0;
}

void Lobisomem::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/sprites/lobisomem.png", 46, 46);	
	direcao = 0.0;
	visao = 200.0;
	time = animtime = 0;
	indicex = indicey = 0;
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
	SDL_SetRenderDrawColor(gerente.janela->renderer, 255, 0, 0, 255);
}