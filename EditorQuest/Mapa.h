#ifndef _MAPA_H_
#define _MAPA_H_

#include "globaldef.h"
#include "Sprite.h"
#include <string>

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

	void Inicializar(SDL_Renderer* renderer);
	void Renderizar(SDL_Renderer* renderer, SDL_Rect* camera);
	void Salvar(std::string nome);
	void Carregar(std::string nome);

	SDL_Rect PegaDimensaoemTiles();
	SDL_Rect PegaDimensaoAbsoluta();
	cMap* PegaColisao();
	unsigned int PegaQtdColisao();
};
#endif
