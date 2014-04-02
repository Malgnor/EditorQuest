#include "EnergyBall.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Dummy.h"

EnergyBall::EnergyBall(GerenteAtor& _gerente, double _x, double _y, double _direcao) : Ator(_gerente)
{
	x = _x;
	y = _y;
	direcao = _direcao*M_PI/180.0;
}
	
SDL_Rect EnergyBall::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
unsigned int EnergyBall::PegaTipo(){
	return ATOR_HABILIDADE;
}
	
bool EnergyBall::EstaNoJogo(){
	return vivo;
}

void EnergyBall::Colidiu(Ator* ator){
	if(ator->PegaTipo() == ATOR_INIMIGO)
	{
		Dummy* atingido = (Dummy*)ator;
		atingido->FoiAtingido();
	}
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
	indice = tempodevida = 0;
	vivo = true;
}

void EnergyBall::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	x += cos(direcao)*500.0/SEG*deltaTime;
	y += sin(direcao)*500.0/SEG*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 10*SEG)
		vivo = false;
}

void EnergyBall::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void EnergyBall::Finalizar(){

}