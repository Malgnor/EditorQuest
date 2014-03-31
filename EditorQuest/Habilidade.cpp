#include "Habilidade.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

Habilidade::Habilidade(GerenteAtor& _gerente, double _x, double _y, double _direcao) : Ator(_gerente)
{
	x = _x;
	y = _y;
	direcao = _direcao*M_PI/180.0;
}
	
SDL_Rect Habilidade::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
unsigned int Habilidade::PegaTipo(){
	return ATOR_HABILIDADE;
}
	
bool Habilidade::EstaNoJogo(){
	return vivo;
}

void Habilidade::Colidiu(Ator* ator){

}

void Habilidade::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
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

void Habilidade::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/energyball.png");
	indice = tempodevida = 0;
	vivo = true;
}

void Habilidade::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	x += cos(direcao)*500.0/SEG*deltaTime;
	y += sin(direcao)*500.0/SEG*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 10*SEG)
		vivo = false;
}

void Habilidade::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void Habilidade::Finalizar(){

}