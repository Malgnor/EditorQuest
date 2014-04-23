#include "Claw.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Lobisomem.h"
#include "Jogador.h"

Claw::Claw(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

SDL_Rect Claw::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)(origem->PegaBoundingBox().x+cos(direcao)*32.0);
	ret.y = (int)(origem->PegaBoundingBox().y+sin(direcao)*32.0);
	return ret;
}

void Claw::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
}

void Claw::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/clawslash.png", 32);
	tempodevida = 0;
	tipo = DANO_FISICO;
	vivo = true;
	direcao = origem->PegaDirecao();
	x = origem->PegaBoundingBox().x+16.0+cos(direcao)*16.0;
	y = origem->PegaBoundingBox().y+sin(direcao)*16.0;
	direcao2 = -M_PI/4.0;
}

void Claw::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	if(!origem->EstaNoJogo())
		vivo = false;
	tempodevida += deltaTime;
	direcao2 += deltaTime*((M_PI/2.0)/500.0);
	direcao = origem->PegaDirecao();
	x = origem->PegaBoundingBox().x+16.0+cos(direcao)*16.0;
	y = origem->PegaBoundingBox().y+sin(direcao)*16.0;
	if(tempodevida >= 500)
		vivo = false;
}

void Claw::Renderizar(SDL_Rect* camera){
	SDL_Point centro = {0, 16};
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, (unsigned int)((double)tempodevida/83.333333), 0, direcao, 1.0, 1.0, &centro);
}

void Claw::Finalizar(){

}