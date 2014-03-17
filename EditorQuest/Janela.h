#ifndef _JANELA_H_
#define _JANELA_H_

#include "globaldef.h"
#include "FW_Entrada.h"

class GerenciadorTelas;
class Tela;

class Janela{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	GerenciadorTelas* gerente;
	SDL_Color corfundo;

public:	
	FW_Entrada entrada;
	Janela(Tela* telainicial);
	void Inicializar(Tela* telainicial);
	void ProcessarEventos(SDL_Event& evento);
	void ProcessarEventosW(SDL_Event& evento);
	void Atualizar();
	void Renderizar();
	void Finalizar();
	~Janela();
	
	void Mostrar();
	void Esconder();
	void Remover();

	bool Existe();

	SDL_Renderer* PegaRenderer();
	SDL_Color PegaCorFundo();
	Uint32 PegaID();
	const char* PegaTitulo();
	void PegaPosicao(int &x, int &y);
	void PegaTamanho(int &w, int &h);
	SDL_Rect PegaPosicaoeTamanho();

	void SetaCorFundo(SDL_Color cor);
	void SetaCorFundo(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void SetaTitulo(const char* titulo);
	void SetaIcone(SDL_Surface* icone);
	void SetaPosicao(int x, int y);
	void SetaTamanho(int w, int h);
};

#endif