#include "Jogador.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "EnergyBall.h"
#include "Explosion.h"
#include "Slash.h"
#include "Equipamento.h"

Jogador::Jogador(GerenteAtor& _gerente, double posX, double posY) : Ator(_gerente), x(posX), y(posY)
{

}

void Jogador::AtualizarAtributos(){
	Atributos novos = {200, atributos.hpatual, 2, 200, atributos.mpatual, 4, 25, 50, 50};
	atributos = novos;
	for(int i = 0; i < EQUIP_QTD; i++){
		if(equipamentos[i]){
			Atributos a = equipamentos[i]->PegaAtributos();
			atributos.hp += a.hp;
			atributos.hpregen += a.hpregen;
			atributos.mp += a.mp;
			atributos.mpregen += a.mpregen;
			atributos.forca += a.forca;
			atributos.defesa += a.defesa;
			atributos.magia += a.magia;
		}
	}	
	if(atributos.hpatual > atributos.hp)
		atributos.hpatual = atributos.hp;
	if(atributos.mpatual > atributos.mp)
		atributos.mpatual = atributos.mp;
}

void Jogador::FoiAtingido(int dano, unsigned int tipo, SDL_Rect* colisao){
	if(!gm){
		double d = atan2(y-colisao->y, x-colisao->x);
		if(tipo == 0){
			atributos.hpatual -= (int)(floor((dano*atributos.hp)/(atributos.hp*(1.0+(atributos.defesa/100.0)))));
			x += cos(d)*16;
			y += sin(d)*16;
		}
		else if(tipo == 1){
			atributos.hpatual -= (int)(floor((dano*atributos.hp)/(atributos.hp*(1.0+(atributos.magia/100.0)))));
			x += cos(d)*8;
			y += sin(d)*8;
		}
	}
}

Item** Jogador::PegaInventario(){
	return inventario;
}

Equipamento** Jogador::PegaEquipamentos(){
	return equipamentos;
}

Atributos& Jogador::PegaAtributos(){
	return atributos;
}

unsigned int Jogador::PegaSkillSelecionada(){
	return skill;
}

double Jogador::PegaDirecao(){
	return direcao;
}

SDL_Rect Jogador::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	//SDL_Rect ret = {(int)x+1, (int)y+16, 32, 32};
	return ret;
}

unsigned int Jogador::PegaTipo(){
	return ATOR_JOGADOR;
}
	
bool Jogador::EstaNoJogo(){
	return atributos.hpatual > 0;
}

void Jogador::Colidiu(Ator* ator, SDL_Rect* colisao){

}

void Jogador::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	if(!ghost){
		double dx,dy;
		switch (tile->id)
		{
		case 1:
			if(colisao->w > colisao->h)
			{
				dy = (double)(y-tile->rect.y);
				if( dy > 0)
				{
					y += colisao->h;
				}
				else
				{
					y -= colisao->h;
				}
			}
			else
			{			
				dx = (double)(x-tile->rect.x);
				if( dx > 0)
				{
					x += colisao->w;
				}
				else
				{
					x -= colisao->w;
				}
			}
			break;
		}
	}
}

void Jogador::Inicializar(){
	sprite.CriaTexturaDaImagemC(gerente.janela->renderer, "resources/sprites/vlad.png", 33, 48);
	andando = false;
	direcao = 0.0;
	indicex = indicey = skill = 0;
	atributos.hpatual = atributos.hp = 200;
	atributos.hpregen = 2;
	atributos.mpatual = atributos.mp = 200;
	atributos.mpregen = 4;
	atributos.forca = 25;
	atributos.defesa = 50;
	atributos.magia = 50;
	time = animtime = 0;
	for(int i = 0; i < 10; i++)
		inventario[i] = 0;
	for(int i = 0; i < EQUIP_QTD; i++)
		equipamentos[i] = 0;
	gm = ghost = false;
}

void Jogador::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	KB_Botao* Teclas = PegaTecla();
	M_Mouse* Mouse = PegaMouse();
	time += deltaTime;
	if(time >= 1000){
		time -= 1000;
		atributos.hpatual += atributos.hpregen;
		atributos.mpatual += atributos.mpregen;
	}
	if(atributos.hpatual > atributos.hp)
		atributos.hpatual = atributos.hp;
	if(atributos.mpatual > atributos.mp)
		atributos.mpatual = atributos.mp;
	if(Teclas[KB_1].pressionado)
		skill = 0;
	if(Teclas[KB_2].pressionado)
		skill = 1;
	if(Teclas[KB_3].pressionado)
		skill = 2;
	if(Teclas[KB_W].ativo){
		y-=(0.3*deltaTime);
		indicey = 3;
		andando = true;
	}
	else if(Teclas[KB_S].ativo){
		y+=(0.3*deltaTime);
		indicey = 0;
		andando = true;
	}
	if(Teclas[KB_A].ativo){
		x-=(0.3*deltaTime);
		indicey = 1;
		andando = true;
	}
	else if(Teclas[KB_D].ativo){
		x+=(0.3*deltaTime);
		indicey = 2;
		andando = true;
	}	
	if(andando){
		animtime += deltaTime;
		if(animtime >= 200){
			animtime -= 200;
			indicex = (indicex+1)%4;
		}
	}
	andando = false;
	direcao = atan2(Mouse->y-(y-(double)camera->y)-16,Mouse->x-(x-(double)camera->x)-16);
	//printf("%f\t", direcao);
	if(indicey == 2){ //Direita
		if(direcao < -M_PI/4)
			direcao = -M_PI/4;
		else if (direcao > M_PI/4)
			direcao = M_PI/4;
	} else if (indicey == 0){ //Baixo
		if(direcao < M_PI/4)
			direcao = M_PI/4;
		else if (direcao > M_PI/4*3)
			direcao = M_PI/4*3;
	} else if (indicey == 1){ //Esquerda
		if(direcao < M_PI/4*3 && direcao >= 0)
			direcao = M_PI/4*3;
		else if (direcao > -M_PI/4*3 && direcao < 0)
			direcao = -M_PI/4*3;
	} else { //Cima
		if (direcao > -M_PI/4)
			direcao = -M_PI/4;
		else if (direcao < -M_PI/4*3)
			direcao = -M_PI/4*3;
	}
	//printf("%f\n", direcao);
	if(Mouse->wy){
		skill = (++skill)%3;
		printf("%d\n", skill);
	}
	if(Mouse->botoes[M_ESQUERDO].pressionado){
		switch (skill)
		{
		case 0:
			gerente.Adicionar(new Slash(gerente, this, atributos.forca));
			break;
		case 1:
			if(atributos.mpatual >= 5){
				gerente.Adicionar(new EnergyBall(gerente, this, atributos.magia));
				atributos.mpatual -= 5;
			}
			break;
		case 2:
			if(atributos.mpatual >= 20){
				gerente.Adicionar(new Explosion(gerente, this, atributos.magia*2));
				atributos.mpatual -= 20;
			}
			break;
		}
	}
}

void Jogador::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, indicex, indicey);
}

void Jogador::Finalizar(){	
	for(int i = 0; i < 10; i++){
		delete inventario[i];
		inventario[i] = 0;
	}
	for(int i = 0; i < EQUIP_QTD; i++){
		delete equipamentos[i];
		equipamentos[i] = 0;
	}
}

void Jogador::Godmode(){
	gm = !gm;
}

void Jogador::Ghost(){
	ghost = !ghost;
}