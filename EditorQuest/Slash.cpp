#include "Slash.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

Slash::Slash(GerenteAtor& _gerente, double _x, double _y, double _direcao) : Ator(_gerente)
{
	x = _x+cos(_direcao*M_PI/180.0)*24.0;
	y = _y+sin(_direcao*M_PI/180.0)*24.0;
	direcao = _direcao;
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

}

void Slash::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
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

void Slash::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/slash.png");
	indice = tempodevida = 0;
	vivo = true;
}

void Slash::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	tempodevida += deltaTime;
	//x += cos(direcao)*500.0/SEG*deltaTime;
	//y += sin(direcao)*500.0/SEG*deltaTime;
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(tempodevida >= 0.5*SEG)
		vivo = false;
}

void Slash::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, 0, 0, direcao);
}

void Slash::Finalizar(){

}