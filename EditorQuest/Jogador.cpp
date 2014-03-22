#include "Jogador.h"
#include "GerenteAtor.h"
#include "SDL.h"

Jogador::Jogador(GerenteAtor& _gerente) : Ator(_gerente)
{

}
	
SDL_Rect Jogador::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
	
bool Jogador::EstaNoJogo(){
	return true;
}

void Jogador::Colidiu(Ator* ator){

}

void Jogador::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);
	x = 400;
	y = 300;
	indice = 0;
}

void Jogador::Atualizar(){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();	
	if(Teclas[FW_CIMA].ativo)
		y-=5;
	else if(Teclas[FW_BAIXO].ativo)
		y+=5;
	if(Teclas[FW_ESQUERDA].ativo)
		x-=5;
	else if(Teclas[FW_DIREITA].ativo)
		x+=5;
}

void Jogador::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, indice);
}

void Jogador::Finalizar(){

}