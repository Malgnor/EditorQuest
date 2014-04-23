#include "Armadilha.h"
#include "GerenteAtor.h"
#include "Flecha.h"
#include "Espinhos.h"

Armadilha::Armadilha(GerenteAtor& _gerente, double _x, double _y, double _direcao, unsigned int _tipo) : Ator(_gerente), x(_x), y(_y), direcao(_direcao), tipo(_tipo)
{}

unsigned int Armadilha::PegaTipoArmadilha(){
	return tipo;
}

SDL_Rect Armadilha::PegaBoundingBox(){
	SDL_Rect ret = {(int)x, (int)y, 1, 1};
	return ret;
}

unsigned int Armadilha::PegaTipo(){
	return ATOR_ARMADILHA;
}

double Armadilha::PegaDirecao(){
	return direcao;
}
	
bool Armadilha::EstaNoJogo(){
	return true;
}

void Armadilha::Colidiu(Ator* ator, SDL_Rect* colisao){

}

void Armadilha::ColidiuMapa(cMap* tile, SDL_Rect* colisao){

}

void Armadilha::Inicializar(){
	time = 0;
}

void Armadilha::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	time += deltaTime;
	switch (tipo)
	{
	case ARMADILHA_FLECHA:
		if(time >= 1500){
			time -= 1500;
			gerente.Adicionar(new Flecha(gerente, this, 10));
		}
		break;
	case ARMADILHA_ESPINHOS:
		if(time >= 2000){
			time -= 2000;
			gerente.Adicionar(new Espinhos(gerente, this, 15));
		}
		break;
	}
}

void Armadilha::Renderizar(SDL_Rect* camera){

}

void Armadilha::Finalizar(){

}