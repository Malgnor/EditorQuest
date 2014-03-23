#include "Jogador.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

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
	indice = 0;
}

void Jogador::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();	
	if(Teclas[FW_W].ativo)
		y-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_S].ativo)
		y+=(300.0/SEG*deltaTime);
	if(Teclas[FW_A].ativo)
		x-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_D].ativo)
		x+=(300.0/SEG*deltaTime);
	indice = 0;
}

void Jogador::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, indice);
}

void Jogador::Finalizar(){

}