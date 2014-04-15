#include "Espinhos.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"

Espinhos::Espinhos(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

void Espinhos::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
}

void Espinhos::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/espinhos.png");
	x = origem->PegaBoundingBox().x;
	y = origem->PegaBoundingBox().y;
	direcao = origem->PegaDirecao();
	tipo = DANO_FISICO;
	tempodevida = 0;
	vivo = true;
}

void Espinhos::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	if(!origem->EstaNoJogo())
		vivo = false;
	tempodevida += deltaTime;
	if(tempodevida >= 500)
		vivo = false;
}

void Espinhos::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void Espinhos::Finalizar(){

}