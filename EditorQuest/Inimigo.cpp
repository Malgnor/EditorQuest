#include "Inimigo.h"
#include "Mapa.h"
#include "GerenteAtor.h"

Inimigo::Inimigo(GerenteAtor& _gerente) : Ator(_gerente)
{
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

bool Inimigo::EstaNoJogo(){
	return atributos.hpatual > 0;
}

void Inimigo::Colidiu(Ator* ator){

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

void Inimigo::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x - (double)camera->x, y - (double)camera->y, indice, 0, direcao);
}