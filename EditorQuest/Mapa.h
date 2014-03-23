#ifndef _MAPA_H_
#define _MAPA_H_

#include "globaldef.h"
#include "Sprite.h"

struct cMap
{
	unsigned int id;
	SDL_Rect rect;
};

class Mapa
{
private:
	unsigned int **mapa, altura, largura, qtdColisao;
	Sprite sprite;
	cMap* colisao;

public:
	Mapa();
	~Mapa();

	void Inicializar(SDL_Renderer* renderer, unsigned int **_mapa, unsigned int _altura, unsigned int _largura);
	void Renderizar(SDL_Renderer* renderer, SDL_Rect* camera);

	SDL_Rect PegaDimensaoemTiles();
	SDL_Rect PegaDimensaoAbsoluta();
	cMap* PegaColisao();
	unsigned int PegaQtdColisao();
};
#endif
