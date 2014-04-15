#include "DropItem.h"
#include "GerenteAtor.h"
#include "Jogador.h"

DropItem::DropItem(GerenteAtor& _gerente, Item* _item, double _x, double _y) : Ator(_gerente), item(_item), x(_x), y(_y)
{

}
	
SDL_Rect DropItem::PegaBoundingBox(){
	if(item){
		SDL_Rect ret = item->PegaIcone().PegaDimensao();
		ret.x = (int)x;
		ret.y = (int)y;
		return ret;
	}
	SDL_Rect ret = { -500, -500, 1, 1};
	return ret;
}

bool DropItem::EstaNoJogo(){
	return vivo;
}

unsigned int DropItem::PegaTipo(){
	return ATOR_ITEM;
}

double DropItem::PegaDirecao(){
	return 0.0;
}

void DropItem::Colidiu(Ator* ator){
	if(item)
		if(ator->PegaTipo() == ATOR_JOGADOR){
			Item** inventario = ((Jogador*)ator)->PegaInventario();
			for(int i = 0; i < 10; i++){
				if(inventario[i] != 0)
					continue;
				inventario[i] = item;
				item = 0;
				vivo = false;
			}
		}
}

void DropItem::ColidiuMapa(cMap* tile, SDL_Rect* colisao){

}

void DropItem::Inicializar(){
	time = 0;
	if(item)
		vivo = true;
	else
		vivo = false;
}		

void DropItem::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	time += deltaTime;
	if(time >= 10000 || !item)
		vivo = false;
}	

void DropItem::Renderizar(SDL_Rect* camera){
	if(item)
		item->PegaIcone().Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y);
}

void DropItem::Finalizar(){
	if(item)
		delete item;
	item = 0;
}