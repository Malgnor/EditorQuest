#include "Editor.h"
#include "Janela.h"
#include <fstream>

using namespace std;

void Editor::Inicializar(Janela* _janela)
{
	janela = _janela;
	janela->SetaTitulo("Walachia - Editor");
	janela->SetaCorFundo(0, 0, 0);	
	int w, h;
	janela->PegaTamanho(w, h);
	bordaHorizontal = 60;
	bordaLateral = 150;
	estadoEditor = EDIT_NONE;
	grid = false;
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	botoes[BTN_MAPA].Inicializar(janela->renderer, "Tile", fonte, cor);
	botoes[BTN_INIMIGOS].Inicializar(janela->renderer, "Inimigo", fonte, cor);
	botoes[BTN_ARMADILHAS].Inicializar(janela->renderer, "Armadilha", fonte, cor);
	botoes[BTN_ITENS].Inicializar(janela->renderer, "Item", fonte, cor);
	botoes[BTN_CIMA].Inicializar(janela->renderer, "/\\", bordaLateral+(800-bordaLateral)/2, bordaHorizontal+10, fonte, cor);
	botoes[BTN_BAIXO].Inicializar(janela->renderer, "\\/", bordaLateral+(800-bordaLateral)/2, 550, fonte, cor);
	botoes[BTN_ESQUERDA].Inicializar(janela->renderer, " < ", bordaLateral+10, bordaHorizontal+(600-bordaHorizontal)/2, fonte, cor);
	botoes[BTN_DIREITA].Inicializar(janela->renderer, " > ", 700, bordaHorizontal+(600-bordaHorizontal)/2, fonte, cor);
	int px = 800;
	for(int i = 4; i > 0; i--){
		px -= 10+botoes[i-1].PegaDimensao().w;
		botoes[i-1].SetaPosicao(px, 10);
	}

	unsigned int altura, largura;
	unsigned int** mapp = 0;
	ifstream in;
	in.open("teste.equest", std::ios_base::binary);
	if(in.is_open())
	{
		in.read((char*)&largura, sizeof(unsigned int));
		in.read((char*)&altura, sizeof(unsigned int));
		mapp = new unsigned int*[altura];
		for(unsigned int i = 0; i < altura; i++)
		{
			mapp[i] = new unsigned int[largura];
			for(unsigned int j = 0; j < largura; j++)
			{
				in.read((char*)&mapp[i][j], sizeof(unsigned int));
			}
		}
		in.close();
	}

	mapa.Inicializar(janela->renderer, mapp, altura, largura);
	camera.x = -bordaLateral;
	camera.y = -bordaHorizontal;
	camera.w = w;
	camera.h = h;
	TTF_CloseFont(fonte);
}

void Editor::Atualizar(Uint32 deltaTime)
{
	int largura, altura;
	M_Mouse* mouse = PegaMouse();
	KB_Botao* tecla = PegaTecla();
	largura = mapa.PegaDimensaoAbsoluta().w;
	altura = mapa.PegaDimensaoAbsoluta().h;

	for(int i = 0; i < BTN_MAX; i++)
		if(estadoEditor != i || i > 3)
			botoes[i].Atualizar();
	
	if(tecla[KB_BAIXO].pressionado || botoes[BTN_BAIXO].Pressed() || (mouse->wy < 0 && tecla[KB_LCONTROL].ativo) || (mouse->y > 500 && tecla[KB_LALT].ativo))
		camera.y+= 32;
	else if(tecla[KB_CIMA].pressionado || botoes[BTN_CIMA].Pressed() || (mouse->wy > 0 && tecla[KB_LCONTROL].ativo) || (mouse->y < 200 && tecla[KB_LALT].ativo))
		camera.y-= 32;
	if(tecla[KB_DIREITA].pressionado || botoes[BTN_DIREITA].Pressed() || (mouse->wx > 0 && tecla[KB_LCONTROL].ativo) || (mouse->x > 700 && tecla[KB_LALT].ativo))
		camera.x+= 32;
	else if(tecla[KB_ESQUERDA].pressionado || botoes[BTN_ESQUERDA].Pressed() || (mouse->wx < 0 && tecla[KB_LCONTROL].ativo) || (mouse->x < 200 && tecla[KB_LALT].ativo))
		camera.x-= 32;
	if(camera.x < -bordaLateral)
		camera.x = -bordaLateral;
	else if(camera.x > largura-camera.w)
		camera.x = largura-camera.w;
	if(camera.y < -bordaHorizontal)
		camera.y = -bordaHorizontal;
	else if(camera.y > altura-camera.h)
		camera.y = altura-camera.h;

	if(tecla[KB_G].pressionado)
		grid = !grid;
	for(int i = 0; i < 4; i++)
		if(botoes[i].Pressionado())
			estadoEditor = i;
	switch (estadoEditor)
	{
	case EDIT_MAPA:
		break;
	case EDIT_INIMIGOS:
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_NONE:
		break;
	}
}

void Editor::Renderizar()
{
	SDL_Rect rect = {0, 0, 800, bordaHorizontal};
	M_Mouse* mouse = PegaMouse();
	int offX, offY;
	mapa.Renderizar(janela->renderer, &camera);
	SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
	if(grid){
		offX = (camera.x+bordaLateral)%32;
		offY = (camera.y+bordaHorizontal)%32;
		for(int y = 0; y < 1+(600-bordaHorizontal)/32; y++){
			SDL_RenderDrawLine(janela->renderer, bordaLateral, bordaHorizontal-offY+y*32, 800, bordaHorizontal-offY+y*32);
		}
		for(int x = 0; x < 1+(800-bordaLateral)/32; x++){
			SDL_RenderDrawLine(janela->renderer, bordaLateral-offX+x*32, bordaHorizontal, bordaLateral-offX+x*32, 600);
		}
	}
	SDL_SetRenderDrawColor(janela->renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(janela->renderer, &rect);
	rect.w = bordaLateral;
	rect.h = 600;
	SDL_RenderFillRect(janela->renderer, &rect);
	SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(janela->renderer, 0, bordaHorizontal, 800, bordaHorizontal);
	SDL_RenderDrawLine(janela->renderer, bordaLateral, bordaHorizontal, bordaLateral, 600);
	for(int i = 0; i < 4; i++)
		if(estadoEditor != i)
			botoes[i].Renderizar(janela->renderer);
	for(int i = 0; i < 4; i++)
		if(botoes[i+4].Hover())
			botoes[i+4].Renderizar(janela->renderer);
	switch (estadoEditor)
	{
	case EDIT_MAPA:
		if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			offX = mouse->x-bordaLateral;
			offY = mouse->y-bordaHorizontal;
			rect.x = offX-offX%32-(camera.x+bordaLateral)%32+bordaLateral;
			rect.y = offY-offY%32-(camera.y+bordaHorizontal)%32+bordaHorizontal;
			rect.w = rect.h = 32;
			SDL_SetRenderDrawColor(janela->renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(janela->renderer, &rect);
		}
		break;
	case EDIT_INIMIGOS:
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_NONE:
		break;
	}
}

void Editor::Finalizar()
{
}

Tela* Editor::ProximaTela()
{
	if(PegaTecla()[KB_ENCERRA].pressionado || PegaTecla()[KB_ESC].pressionado)
		return 0;
	return this;
}
	
Editor::~Editor()
{
}