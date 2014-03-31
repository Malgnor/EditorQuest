#include "Jogador.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Habilidade.h"

Jogador::Jogador(GerenteAtor& _gerente) : Ator(_gerente)
{

}
	
SDL_Rect Jogador::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
unsigned int Jogador::PegaTipo(){
	return ATOR_JOGADOR;
}
	
bool Jogador::EstaNoJogo(){
	return true;
}

void Jogador::Colidiu(Ator* ator){

}

void Jogador::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
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
		indice = 1;
		break;
	case 3:
		indice = 2;
		break;
	case 4:
		indice = 3;
		break;
	default:
		break;
	}
}

void Jogador::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);
	x = 400.0;
	y = 300.0;
	direcao = 0.0;
	indice = 0;
	hpatual = atributos.hp = 100;
	atributos.hpregen = 1;
	mpatual = atributos.mp = 100;
	atributos.mpregen = 2;
	atributos.forca = 5;
	atributos.defesa = 5;
	atributos.magia = 5;
	time = 0;
}

void Jogador::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	time += deltaTime;
	if(time >= 1000){
		time -= 1000;
		hpatual += atributos.hpregen;
		mpatual += atributos.mpregen;
		if(hpatual > atributos.hp)
			hpatual = atributos.hp;
		if(mpatual > atributos.mp)
			mpatual = atributos.mp;
	}
	// SEG = 1000.0
	if(Teclas[FW_W].ativo)
		y-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_S].ativo)
		y+=(300.0/SEG*deltaTime);
	if(Teclas[FW_A].ativo)
		x-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_D].ativo)
		x+=(300.0/SEG*deltaTime);
	direcao = atan2(Mouse->y-(y-(double)camera->y)-16,Mouse->x-(x-(double)camera->x)-16)*180.0/M_PI;
	if(Mouse->botoes[FW_MESQUERDO].pressionado)
		gerente.Adicionar(new Habilidade(gerente, x, y, direcao));
	//printf("%f %d %d\n", direcao, Mouse->x, Mouse->y);
	indice = 0;
}

void Jogador::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, indice, 0, direcao);
}

void Jogador::Finalizar(){

}