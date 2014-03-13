#include "Sprite.h"
#include <string>

Sprite::Sprite(){
	src.x = src.y = src.w = src.h = 0;
	textura = 0;
}

Sprite::~Sprite(){
	this->Destruir();
}

bool Sprite::CarregaTexturaDaImagem(SDL_Renderer* renderer, const char *imagem, int largura, int altura){
	this->Destruir();
	
	if(largura)
		src.w = largura;
	else
		src.w = 0;
	if(altura)
		src.h = altura;
	else
		src.h = 0;
	return (textura != 0);
}

bool Sprite::CarregaTexturaDoTextoS(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor){
	this->Destruir();
	SDL_Surface* surface = TTF_RenderText_Solid(fonte, texto, cor);
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	src = surface->clip_rect;
	SDL_FreeSurface(surface);
	return (textura != 0);
}

bool Sprite::CarregaTexturaDoTextoC(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor){
	this->Destruir();
	SDL_Surface* textSurface = SDL_CreateRGBSurface(0, 2048, 2048, 32, rmask, gmask, bmask, amask);
	SDL_Surface* tmpSurface = 0;
	SDL_Rect dest;
	src.x = dest.x = 0;
	src.y = dest.y = 0;
	src.w = 0;
	int i = 0;
	while(texto[i] != '\0'){
		std::string tmp = "";
		while(texto[i] != '\n' && texto[i] != '\0'){
			if(texto[i] == '\t')
				tmp += "    ";
			else
				tmp.push_back(texto[i]);
			i++;
		}

		tmpSurface = TTF_RenderText_Solid(fonte, tmp.c_str(), cor);
		dest.w = tmpSurface->w;
		dest.h = tmpSurface->h;
		SDL_BlitSurface(tmpSurface, NULL, textSurface, &dest);
		SDL_FreeSurface(tmpSurface);
		dest.y += tmpSurface->h;
		if(dest.w > src.w)
			src.w = dest.w;
		if(texto[i++] == '\0')
			break;
	}
	src.h = dest.y;
	dest.x = 0;
	dest.y = 0;
	dest.w = src.w;
	dest.h = src.h;
	tmpSurface = SDL_CreateRGBSurface(0, src.w, src.h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(textSurface, &dest, tmpSurface, NULL);
	textura = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_FreeSurface(textSurface);
	return (textura != 0);
}

void Sprite::PegaDimensao(SDL_Rect &rect){
	rect.w = src.w;
	rect.h = src.h;
}

void Sprite::PegaDimensao(int &w, int &h){
	w = src.w;
	h = src.h;
}

void Sprite::Destruir(){
	SDL_DestroyTexture(textura);
	src.x = src.y = src.w = src.h = 0;
	textura = 0;
}