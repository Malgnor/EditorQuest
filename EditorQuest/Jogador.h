#ifndef _JOGADOR_H_
#define _JOGADOR_H_

enum { EQUIP_ARMA, EQUIP_CABECA, EQUIP_TRONCO, EQUIP_MAOS, EQUIP_PES};

#include "Ator.h"
#include "Sprite.h"
#include "Item.h"
class Equipamento;

class Jogador : public Ator
{
private:
	Sprite sprite;
	double x, y, direcao;
	unsigned int indice, skill;
	Item* inventario[10];
	Equipamento* equipamentos[5];
	Atributos atributos;
	Uint32 time;
	friend class Item;

public:
	Jogador(GerenteAtor& _gerente);
	
	virtual SDL_Rect PegaBoundingBox();

	Item** PegaInventario();
	Equipamento** PegaEquipamentos();
	Atributos& PegaAtributos();
	unsigned int PegaSkillSelecionada();
	double PegaDirecao();

	virtual bool EstaNoJogo();
	virtual unsigned int PegaTipo();

	virtual void Colidiu(Ator* ator);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();
};
#endif