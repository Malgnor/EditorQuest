#include "Explosion.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "Jogador.h"
#include "Inimigo.h"

Explosion::Explosion(GerenteAtor& _gerente, Ator* _origem, int _dano) : Habilidades(_gerente, _origem, _dano)
{
}

void Explosion::Colidiu(Ator* ator, SDL_Rect* colisao){
	if(ator->PegaTipo() != origem->PegaTipo()){
		if(ator->PegaTipo() == ATOR_INIMIGO){			
			if(!explo){
				explo = true;
				tempodevida = 0;
				sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/explosion.png");
				x -= 16;
				y -= 16;
			}
			if(!atingidos.empty()){
				for(Ator* a : atingidos){
					if(a == ator)
						return;
				}
			}
			atingidos.push_back(ator);
			Inimigo* atingido = (Inimigo*)ator;
			atingido->FoiAtingido(dano, tipo, colisao);
		} else if(ator->PegaTipo() == ATOR_JOGADOR){	
			if(!explo){
				explo = true;
				tempodevida = 0;
				sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/explosion.png");
				x -= 16;
				y -= 16;
			}
			if(!atingidos.empty()){
				for(Ator* a : atingidos){
					if(a == ator)
						return;
				}
			}
			atingidos.push_back(ator);
			Jogador* atingido = (Jogador*)ator;
			atingido->FoiAtingido(dano, tipo, colisao);
		}
	}
}

void Explosion::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	switch (tile->id)
	{
	case 1:
		if(!explo){
			explo = true;
			tempodevida = 0;
			sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/explosion.png");
			x -= 16;
			y -= 16;
		}
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
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/energysmall.png");	
	x = origem->PegaBoundingBox().x;
	y = origem->PegaBoundingBox().y;
	direcao = origem->PegaDirecao();
	tipo = DANO_MAGICO;
	tempodevida = 0;
	vivo = true;
	explo = false;
}

void Explosion::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	if(!origem->EstaNoJogo())
		vivo = false;
	tempodevida += deltaTime;
	if(!explo){
		x += cos(direcao)*0.4*deltaTime;
		y += sin(direcao)*0.4*deltaTime;
	}
	//printf("%f %f %f\n", direcao, cos(direcao), sin(direcao));
	if(explo){
		if(tempodevida >= 500)
			vivo = false;
	} else {		
		if(tempodevida >= 750){
			x -= 16;
			y -= 16;
			tempodevida = 0;
			explo = true;
			sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/explosion.png");
		}
	}
}

void Explosion::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void Explosion::Finalizar(){

}