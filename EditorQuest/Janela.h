#ifndef _JANELA_H_
#define _JANELA_H_

#include "globaldef.h"

class GerenciadorTelas;
class Tela;

class Janela{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	GerenciadorTelas* gerente;

public:
	Janela(Tela* telainicial);
	void Inicializar(Tela* telainicial);
	void ProcessarEventos(SDL_Event& evento);
	void Atualizar();
	void Renderizar();
	void Encerrar();
	~Janela();

	void ProcessarEventosW(SDL_Event& evento);

	void Mostrar();
	void Esconder();
	void Remover();

	bool Existe();

	SDL_Renderer* PegaRenderder();
	Uint32 PegaID();
	const char* PegaTitulo();
	void PegaPosicao(int &x, int &y);
	void PegaTamanho(int &w, int &h);

	void SetaTitulo(const char* titulo);
	void SetaIcone(SDL_Surface* icone);
	void SetaPosicao(int x, int y);
	void SetaTamanho(int w, int h);
};

#endif