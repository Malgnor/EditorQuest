#include "Debugger.h"
#include "Jogo.h"
#include "GerenteJanela.h"

using namespace std;

Debugger::Debugger(){	
	renderer = NULL;
	window = NULL;
	this->Inicializar();
	GJanela.Adicionar(this);
}

Debugger::~Debugger(){
	GJanela.Remover(this);
}

void Debugger::Inicializar(){
	window = SDL_CreateWindow("Debugger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Color black = {0, 0, 0};
	txt.str("Texto");
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	texto = loadFromRenderedText(txt.str().c_str(), fonte, black, r);
	r.x = 6;
	r.y = 6;
}

void Debugger::ProcessarEventos(SDL_Event& evento){
	if(evento.key.keysym.sym == SDLK_KP_PLUS && evento.key.state == SDL_RELEASED)
		new Jogo;
	if(evento.type == SDL_MOUSEWHEEL)
		r.y += evento.wheel.y*10;
}

void Debugger::Atualizar(){
	SDL_Color black = {0, 0, 0};
	int x, y;
	stringstream ntxt;
	ntxt.str("");
	ntxt << "Janelas ativas: " << GJanela.janelas.size() << endl;
	if(!GJanela.janelas.empty())
		for(Janela* j: GJanela.janelas){
			j->PegaPosicao(&x, &y);
			ntxt << "Janela ID: " << j->PegaID() << " Titulo: " << j->PegaTitulo() << " (" << x << ", " << y << ") (";
			j->PegaTamanho(&x, &y);
			ntxt << x << ", " << y << ") Foco: " << ((GJanela.PegaJanelaFocada() == j) ? "V" : "F") << endl;
		}
	if(ntxt.str() != txt.str()){
		txt.str(ntxt.str());
		SDL_DestroyTexture(texto);
		texto = loadFromRenderedText(txt.str().c_str(), fonte, black, r);
	}
	/*
	ntxt.str("");
	SDL_GetMouseState(&x, &y);
	ntxt << "Debugger (" << x << "," << y << ")";
	this->SetaTitulo(ntxt.str().c_str());
	*/
}

void Debugger::Renderizar(){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texto, NULL, &r);
	SDL_RenderPresent(renderer);
}

SDL_Texture* Debugger::loadFromRenderedText(const char *textureText, TTF_Font *font, SDL_Color textColor, SDL_Rect &dst)
{
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	SDL_Texture *texture;

	SDL_Surface* textSurface = SDL_CreateRGBSurface(0, 2048, 2048, 32, rmask, gmask, bmask, amask);
	SDL_Surface* tmpSurface = 0;
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dst.w = 0;
	int i = 0;
	while(textureText[i] != '\0'){
		string tmp = "";
		while(textureText[i] != '\n' && textureText[i] != '\0'){
			if(textureText[i] == '\t')
				tmp += "    ";
			else
				tmp.push_back(textureText[i]);
			i++;
		}

		tmpSurface = TTF_RenderText_Solid(font, tmp.c_str(), textColor);
		dest.w = tmpSurface->w;
		dest.h = tmpSurface->h;
		SDL_BlitSurface(tmpSurface, NULL, textSurface, &dest);
		SDL_FreeSurface(tmpSurface);
		dest.y += tmpSurface->h;
		if(dest.w > dst.w)
			dst.w = dest.w;
		if(textureText[i++] == '\0')
			break;
	}
	dst.h = dest.y;
	dest.x = 0;
	dest.y = 0;
	dest.w = dst.w;
	dest.h = dst.h;
	tmpSurface = SDL_CreateRGBSurface(0, dst.w, dst.h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(textSurface, &dest, tmpSurface, NULL);
	texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_FreeSurface(textSurface);
	
	return texture;
}

void Debugger::Encerrar(){
	TTF_CloseFont(fonte);
	SDL_DestroyTexture(texto);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
}
