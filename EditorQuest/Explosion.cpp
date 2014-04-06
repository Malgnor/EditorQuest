#include "Explosion.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Dummy.h"

Explosion::Explosion(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

void Explosion::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	switch (tile->id)
	{
	case 1:
		//vivo = false;
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void Explosion::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/explosion.png");	
	x = origem->PegaBoundingBox().x+16;
	y = origem->PegaBoundingBox().y+16;
	direcao = origem->PegaDirecao();
	tipo = DANO_MAGICO;
	tempodevida = 0;
	vivo = true;
}

void Explosion::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	x += cos(direcao)*400.0/SEG*deltaTime;
	y += sin(direcao)*400.0/SEG*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 1*SEG)
		vivo = false;
}

void Explosion::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void Explosion::Finalizar(){

}