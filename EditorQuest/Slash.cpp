#include "Slash.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Dummy.h"
#include "Jogador.h"

Slash::Slash(GerenteAtor& _gerente, Jogador* _jogador) : Ator(_gerente)
{
	jogador = _jogador;
}
	
SDL_Rect Slash::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
unsigned int Slash::PegaTipo(){
	return ATOR_HABILIDADE;
}
	
bool Slash::EstaNoJogo(){
	return vivo;
}

void Slash::Colidiu(Ator* ator){
	if(ator->PegaTipo() == ATOR_INIMIGO)
	{
		Dummy* atingido = (Dummy*)ator;
		atingido->FoiAtingido(10, 0);
	}

}

void Slash::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	/*
	switch (tile->id)
	{
	case 1:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
	*/
}

void Slash::Inicializar(){
	sprite.CriaTexturaDaImagemC(gerente.janela->renderer, "resources/imgs/slashh.png", 0, 0, 255, 255, 255);
	indice = tempodevida = 0;
	vivo = true;
	direcao = jogador->PegaDirecao();
	x = jogador->PegaBoundingBox().x+16.0+cos(direcao)*16.0;
	y = jogador->PegaBoundingBox().y+sin(direcao)*16.0;
	direcao2 = -M_PI/4.0;
}

void Slash::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	direcao2 += deltaTime*((M_PI/2.0)/500.0);
	direcao = jogador->PegaDirecao();
	x = jogador->PegaBoundingBox().x+16.0+cos(direcao)*16.0;
	y = jogador->PegaBoundingBox().y+sin(direcao)*16.0;
	//printf("%f %f %f %f %f %f\n", direcao, x, y, cos(direcao*M_PI/180.0), sin(direcao*M_PI/180.0));
	if(tempodevida >= 0.5*SEG)
		vivo = false;
}

void Slash::Renderizar(SDL_Rect* camera){
	SDL_Point centro = {0, 16};
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, 0, 0, direcao+direcao2, 1.0, 1.0, &centro);
}

void Slash::Finalizar(){

}