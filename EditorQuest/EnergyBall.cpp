#include "EnergyBall.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Dummy.h"

EnergyBall::EnergyBall(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

void EnergyBall::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
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

void EnergyBall::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/energyball.png");
	x = origem->PegaBoundingBox().x;
	y = origem->PegaBoundingBox().y;
	direcao = origem->PegaDirecao();
	tipo = DANO_MAGICO;
	tempodevida = 0;
	vivo = true;
}

void EnergyBall::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	if(!origem->EstaNoJogo())
		vivo = false;
	tempodevida += deltaTime;
	x += cos(direcao)*0.5*deltaTime;
	y += sin(direcao)*0.5*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 1500)
		vivo = false;
}

void EnergyBall::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void EnergyBall::Finalizar(){

}