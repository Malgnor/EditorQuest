#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include "Ator.h"
#include "Sprite.h"
#include "Item.h"

enum {EQUIP_ARMA, EQUIP_CABECA, EQUIP_TRONCO, EQUIP_PERNAS, EQUIP_PES, EQUIP_QTD};
class Equipamento;

class Jogador : public Ator
{
private:
	Sprite sprite;
	double x, y, direcao;
	unsigned int indicex, indicey, skill;
	Item* inventario[10];
	Equipamento* equipamentos[EQUIP_QTD];
	Atributos atributos;
	Uint32 time, animtime;
	bool andando;
	friend class Item;

	bool gm, ghost;

public:
	Jogador(GerenteAtor& _gerente, double posX, double posY);
	
	virtual SDL_Rect PegaBoundingBox();

	void AtualizarAtributos();

	void FoiAtingido(int dano, unsigned int tipo, SDL_Rect* colisao);

	Item** PegaInventario();
	Equipamento** PegaEquipamentos();
	Atributos& PegaAtributos();
	unsigned int PegaSkillSelecionada();
	virtual double PegaDirecao();

	virtual bool EstaNoJogo();
	virtual unsigned int PegaTipo();

	virtual void Colidiu(Ator* ator, SDL_Rect* colisao);
	virtual void ColidiuMapa(cMap* tile, SDL_Rect* colisao);

	virtual void Inicializar();		
	virtual void Atualizar(Uint32 deltaTime, SDL_Rect* camera);	
	virtual void Renderizar(SDL_Rect* camera);
	virtual void Finalizar();

	void Godmode();
	void Ghost();
};
#endif