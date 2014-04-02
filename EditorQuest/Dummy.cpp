#include "Dummy.h"
#include "GerenteAtor.h"

Dummy::Dummy(GerenteAtor& _gerente, double _x, double _y) :Ator(_gerente){
	x = _x;
	y = _y;
}

void Dummy::FoiAtingido(){
	vivo = false;
}
	
SDL_Rect Dummy::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}

unsigned int Dummy::PegaTipo(){
	return ATOR_INIMIGO;
}
	
bool Dummy::EstaNoJogo(){
	return vivo;
}

void Dummy::Colidiu(Ator* ator){

}

void Dummy::ColidiuMapa(cMap* tile, SDL_Rect* colisao){

}

void Dummy::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);
	vivo = true;
}		

void Dummy::Atualizar(Uint32 deltaTime, SDL_Rect* camera){

}	

void Dummy::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, 2);
}

void Dummy::Finalizar(){

}
