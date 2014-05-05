#ifndef __FW_ENTRADA_H__
#define __FW_ENTRADA_H__

#include <SDL.h>

//defines para o indice do objeto teclas
#define FW_MAX_TECLAS	27
#define FW_CIMA		0
#define FW_DIREITA	1
#define FW_BAIXO	2
#define FW_ESQUERDA	3
#define FW_Z		4
#define FW_X		5
#define FW_C		6
#define FW_A		7
#define FW_S		8
#define FW_D		9
#define FW_W		10
#define FW_ESPACO	11
#define FW_ENTER	12
#define FW_CONTROL	13

#define FW_ESC		14
#define FW_ENCERRA	15

#define FW_0		16
#define FW_1		17
#define FW_2		18
#define FW_3		19
#define FW_4		20
#define FW_5		21
#define FW_6		22
#define FW_7		23
#define FW_8		24
#define FW_9		25
#define FW_M		26

//defines para o indice do objeto mouse
#define FW_MDIREITO	0
#define FW_MESQUERDO 1
#define FW_MMEIO	2

//struct para botoes
struct FW_Botao
{
	bool pressionado;
	bool liberado;
	bool ativo;
	int repeticao;
};

//struct para o mouse
struct FW_Mouse
{
	int x;
	int y;
	int wx;
	int wy;
	FW_Botao botoes[3];
};

class FW_Entrada
{
public:	
	FW_Entrada();

	FW_Mouse* pegaMouse();
	FW_Botao* pegaTecla();

	void reseta();
	void atualiza(SDL_Event& evento);
private:

	FW_Botao tecla[FW_MAX_TECLAS];
	FW_Mouse mouse;

	void processaTecla(FW_Botao* tecla, SDL_Event& event);
};

#endif //__FW_ENTRADA_H__