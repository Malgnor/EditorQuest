#ifndef __ENTRADA_H__
#define __ENTRADA_H__

#include <SDL.h>
#include <string>

//defines para o indice do objeto teclas
enum { KB_CIMA, KB_DIREITA, KB_BAIXO, KB_ESQUERDA, KB_Z, KB_X, KB_C, KB_A, KB_S, KB_D, KB_W, KB_ESPACO, KB_ENTER, KB_LCONTROL, KB_ESC,
	KB_ENCERRA, KB_0, KB_1, KB_2, KB_3, KB_4, KB_5, KB_6, KB_7, KB_8, KB_9, KB_M, KB_E, KB_I, KB_T, KB_O, KB_R, KB_Q, KB_U, KB_G, KB_LALT, KB_MAX_TECLAS };

//defines para o indice do objeto mouse
enum { M_DIREITO, M_ESQUERDO, M_MEIO };

//struct para botoes
struct KB_Botao
{
	bool pressionado;
	bool liberado;
	bool ativo;
	int repeticao;
};

//struct para o mouse
struct M_Mouse
{
	int x;
	int y;
	int wx;
	int wy;
	KB_Botao botoes[3];
};

class Entrada
{
public:	
	Entrada();

	M_Mouse* pegaMouse();
	KB_Botao* pegaTecla();

	std::string& pegaTexto();
	bool textoUpdate();
	void ativaInputTexto();
	void desativaInputTexto();
	bool toggleInputTexto();

	void reseta();
	void atualiza(SDL_Event& evento);

private:
	KB_Botao tecla[KB_MAX_TECLAS];
	M_Mouse mouse;
	static bool textInput, textUpdate;
	static std::string texto;

	void processaTecla(KB_Botao* tecla, SDL_Event& event);
};

#endif //__ENTRADA_H__