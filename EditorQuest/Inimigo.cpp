#include "Inimigo.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "Jogador.h"

Inimigo::Inimigo(GerenteAtor& _gerente, Jogador* _jogador, Mapa* _mapa) : Ator(_gerente)
{
	jogador = _jogador;
	mapa = _mapa;
}

Atributos& Inimigo::PegaAtributos(){
	return atributos;
}

SDL_Rect Inimigo::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}

unsigned int Inimigo::PegaTipo(){
	return ATOR_INIMIGO;
}

double Inimigo::PegaDirecao(){
	return direcao;
}

bool Inimigo::EstaNoJogo(){
	return atributos.hpatual > 0;
}

void Inimigo::Colidiu(Ator* ator, SDL_Rect* colisao){

}

void Inimigo::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	double dx, dy;
	switch (tile->id)
	{
	case 1:
		if (colisao->w > colisao->h)
		{
			dy = (double)(y - tile->rect.y);
			if (dy > 0)
			{
				y += colisao->h;
			}
			else
			{
				y -= colisao->h;
			}
			direcao += M_PI/10.0;
		}
		else
		{
			dx = (double)(x - tile->rect.x);
			if (dx > 0)
			{
				x += colisao->w;
			}
			else
			{
				x -= colisao->w;
			}
			direcao += M_PI/10.0;
		}
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

bool Inimigo::TemVisaoDoJogador(){
	double dx = jogador->PegaBoundingBox().x - x;
	double dy = jogador->PegaBoundingBox().y - y;
	double dd = sqrt(dx*dx+dy*dy);
	if (visao >= dd){
		cMap* tiles = mapa->PegaColisao();
		unsigned int qtd = mapa->PegaQtdColisao();
		for(unsigned int i = 0; i < qtd; i++){
			if(tiles[i].id == 1){
				int x1 = (int)x+16;
				int y1 = (int)y+16;
				int x2 = jogador->PegaBoundingBox().x+16;
				int y2 = jogador->PegaBoundingBox().y+16;
				if(SDL_IntersectRectAndLine(&tiles[i].rect, &x1, &y1, &x2, &y2) == SDL_TRUE){
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

void Inimigo::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x - (double)camera->x, y - (double)camera->y, 0, 0, direcao);
	SDL_Rect hpbar = { (int)x-camera->x+4, (int)y-8-camera->y, (int)((double)atributos.hpatual/(double)atributos.hp*24.0), 5};
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gerente.janela->renderer, &hpbar);
	hpbar.w = 26;
	hpbar.x = (int)x-1-camera->x+4;
	SDL_SetRenderDrawColor(gerente.janela->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(gerente.janela->renderer, &hpbar);
}