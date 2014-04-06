#include "Habilidades.h"
#include "GerenteAtor.h"
#include "Inimigo.h"
#include "Jogador.h"

Habilidades::Habilidades(GerenteAtor& _gerente, Ator* _origem, int _dano) : Ator(_gerente), origem(_origem), dano(_dano)
{}
	
SDL_Rect Habilidades::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}
	
bool Habilidades::EstaNoJogo(){
	return vivo;
}

unsigned int Habilidades::PegaTipo(){
	return ATOR_HABILIDADE;
}

double Habilidades::PegaDirecao(){
	return direcao;
}

void Habilidades::Colidiu(Ator* ator){
	if(ator->PegaTipo() != origem->PegaTipo()){
		if(ator->PegaTipo() == ATOR_INIMIGO){
			if(!atingidos.empty()){
				for(Ator* a : atingidos){
					if(a == ator)
						return;
				}
			}
			atingidos.push_back(ator);
			Inimigo* atingido = (Inimigo*)ator;
			atingido->FoiAtingido(dano, tipo);
		} else if(ator->PegaTipo() == ATOR_JOGADOR){
			if(!atingidos.empty()){
				for(Ator* a : atingidos){
					if(a == ator)
						return;
				}
			}
			atingidos.push_back(ator);
			Jogador* atingido = (Jogador*)ator;
			atingido->FoiAtingido(dano, tipo);
		}
	}
}