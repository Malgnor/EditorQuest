#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include "Janela.h"
#include <sstream>

class Debugger : public Janela
{
private:
	TTF_Font *fonte;
	SDL_Rect r;
	SDL_Texture *texto;
	std::stringstream txt;

public:
	Debugger();
	~Debugger();

	virtual void Inicializar();
	virtual void Atualizar();
	virtual void Renderizar();
	virtual void Encerrar();

	SDL_Texture* loadFromRenderedText(const char *textureText, TTF_Font *font, SDL_Color textColor, SDL_Rect &dst);
};
#endif