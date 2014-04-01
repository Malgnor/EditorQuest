#include "Explosion.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

Explosion::Explosion(GerenteAtor& _gerente, double _x, double _y, double _direcao) : Ator(_gerente)
{
	x = _x-32.0;
	y = _y-32.0;
	direcao = _direcao*M_PI/180.0;
}
	
SDL_Rect Explosion::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
unsigned int Explosion::PegaTipo(){
	return ATOR_HABILIDADE;
}
	
bool Explosion::EstaNoJogo(){
	return vivo;
}

void Explosion::Colidiu(Ator* ator){

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
	indice = tempodevida = 0;
	vivo = true;
}

void Explosion::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	//x += cos(direcao)*500.0/SEG*deltaTime;
	//y += sin(direcao)*500.0/SEG*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 1*SEG)
		vivo = false;
}

void Explosion::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void Explosion::Finalizar(){

}