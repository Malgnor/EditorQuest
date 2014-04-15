#include "Flecha.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

Flecha::Flecha(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

void Flecha::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	switch (tile->id)
	{
	case 1:
		vivo = false;
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void Flecha::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/flecha.png");
	x = origem->PegaBoundingBox().x;
	y = origem->PegaBoundingBox().y;
	direcao = origem->PegaDirecao();
	tipo = DANO_FISICO;
	tempodevida = 0;
	vivo = true;
}

void Flecha::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	if(!origem->EstaNoJogo())
		vivo = false;
	tempodevida += deltaTime;
	x += cos(direcao)*0.5*deltaTime;
	y += sin(direcao)*0.5*deltaTime;
	if(tempodevida >= 1500)
		vivo = false;
}

void Flecha::Renderizar(SDL_Rect* camera){
	//SDL_Point centro = {0, 5};
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, 0, 0, direcao);
}

void Flecha::Finalizar(){

}