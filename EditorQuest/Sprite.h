#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "globaldef.h"

class Sprite{
private:
	SDL_Rect src;
	SDL_Texture* textura;
	void* pixels;
	int pitch;

public:
	Sprite();
	~Sprite();

	bool CarregaTexturaDaImagem(SDL_Renderer* renderer, const char *imagem, int largura = 0, int altura = 0);
	bool CarregaTexturaDoTextoS(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor);
	bool CarregaTexturaDoTextoC(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor);

	void Renderizar(SDL_Renderer *renderer, int x, int y,  unsigned int indice = 0, unsigned int indicey = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Rect PegaDimensao();
	void PegaDimensao(int &w, int &h);

	void Destruir();
};
#endif