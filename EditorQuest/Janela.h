#ifndef _JANELA_H_
#define _JANELA_H_

#include "globaldef.h"

class Janela{
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;

public:
	virtual void Inicializar() = 0;
	virtual void Atualizar() = 0;
	virtual void Renderizar() = 0;
	virtual void Encerrar() = 0;

	void ProcessarEventos(SDL_Event& evento);

	bool Existe();
	Uint32 PegaID();
	const char* PegaTitulo();
	void PegaPosicao(int *x, int *y);
	void PegaTamanho(int *w, int *h);

	void SetaTitulo(const char* titulo);
	void SetaIcone(SDL_Surface* icone);
	void SetaPosicao(int x, int y);
	void SetaTamanho(int w, int h);
};

#endif