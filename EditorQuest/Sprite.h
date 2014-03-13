#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "globaldef.h"

class Sprite{
private:
	SDL_Rect src;
	SDL_Texture* textura;

public:
	Sprite();
	~Sprite();

	bool CarregaTexturaDaImagem(SDL_Renderer* renderer, const char *imagem, int largura = 0, int altura = 0);
	bool CarregaTexturaDoTextoS(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor);
	bool CarregaTexturaDoTextoC(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor);

	void PegaDimensao(SDL_Rect &rect);
	void PegaDimensao(int &w, int &h);

	void Destruir();
};
#endif