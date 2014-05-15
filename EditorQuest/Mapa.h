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
	void Novo(unsigned int _largura, unsigned int _altura);

	void Renderizar(SDL_Renderer* renderer, SDL_Rect* camera);

	bool Salvar(std::string nome);
	bool Carregar(std::string nome);

	bool Alterar(unsigned int x, unsigned int y, unsigned int id);

	SDL_Rect PegaDimensaoemTiles();
	SDL_Rect PegaDimensaoAbsoluta();
	cMap* PegaColisao();
	unsigned int PegaQtdColisao();
};
#endif
