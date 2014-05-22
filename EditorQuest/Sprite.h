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

	bool CriaTexturaDaImagem(SDL_Renderer* renderer, const char *imagem, int largura = 0, int altura = 0);
	bool CriaTexturaDaImagemC(SDL_Renderer* renderer, const char *imagem, int largura = 0, int altura = 0, Uint8 r = 0xFF, Uint8 g = 0x00, Uint8 b = 0xFF);
	bool CriaTexturaDoTexto(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor);
	bool CriaTexturaDoTextoC(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor, Uint32 largura);
	bool CriaTexturaMenu(SDL_Renderer* renderer, const char *imagem, const char *texto, TTF_Font *fonte, SDL_Color cortexto);
	bool CriaTexturaMapa(SDL_Renderer* renderer, unsigned int **mapa, unsigned int largura, unsigned int altura);

	void Renderizar(SDL_Renderer *renderer, double posX, double posY, unsigned int indiceX = 0, unsigned int indiceY = 0, double angulo = 0.0, double escalaX = 1.0, double escalaY = 1.0, SDL_Point* centro = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Rect PegaDimensao();
	void PegaDimensao(int &w, int &h);

	int SetaAlphaMod(Uint8 alfa);
	int SetaBlendMode(SDL_BlendMode blend);
	int SetaColorMod(Uint8 r, Uint8 g, Uint8 b);
	int SetaColorMod(SDL_Color cor);

	void Destruir();
};
#endif