#include "Editor.h"
#include "Janela.h"
#include <fstream>

using namespace std;

void Editor::Inicializar(Janela* _janela)
{
	janela = _janela;
	janela->SetaTitulo("Walachia - Editor");
	janela->SetaCorFundo(255, 255, 255);	
	int w, h;
	janela->PegaTamanho(w, h);
	bordaHorizontal = 60;
	bordaLateral = 150;
	estadoEditor = EDIT_NONE;
	selecionado = 0;
	scrollSpeed = 32;
	grid = false;
	janela->entrada.SetaTamanhoTexto(16);
	tileset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/tileset.png", 32);
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	input.CriaTexturaDoTexto(janela->renderer, " ", fonte, cor);
	botoes[BTN_MAPA].Inicializar(janela->renderer, "Tile", fonte, cor);
	botoes[BTN_INIMIGOS].Inicializar(janela->renderer, "Inimigo", fonte, cor);
	botoes[BTN_ARMADILHAS].Inicializar(janela->renderer, "Armadilha", fonte, cor);
	botoes[BTN_ITENS].Inicializar(janela->renderer, "Item", fonte, cor);
	botoes[BTN_MENU].Inicializar(janela->renderer, "Menu", fonte, cor);
	botoes[BTN_PROX].Inicializar(janela->renderer, ">", fonte, cor);
	botoes[BTN_ANT].Inicializar(janela->renderer, "<", fonte, cor);
	botoes[BTN_SAIR].Inicializar(janela->renderer, "Sair", fonte, cor);
	botoes[BTN_SALVAR].Inicializar(janela->renderer, "Salvar", fonte, cor);
	int px = 800;
	for(int i = EDIT_NONE; i > 0; i--){
		px -= 10+botoes[i-1].PegaDimensao().w;
		botoes[i-1].SetaPosicao(px, 10);
	}

	botoes[BTN_ANT].SetaPosicao(5, 300);
	botoes[BTN_PROX].SetaPosicao(bordaLateral-5-botoes[BTN_PROX].PegaDimensao().w, 300);

	botoes[BTN_SAIR].SetaPosicao((bordaLateral-botoes[BTN_SAIR].PegaDimensao().w)/2, 500);
	botoes[BTN_SALVAR].SetaPosicao((bordaLateral-botoes[BTN_SALVAR].PegaDimensao().w)/2, 400);

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

	for(int i = 0; i < EDIT_NONE; i++)
		if(estadoEditor != i)
			botoes[i].Atualizar();
	
	if(tecla[KB_BAIXO].pressionado || (mouse->wy < 0 && tecla[KB_LCONTROL].ativo) || (mouse->y > 500 && tecla[KB_LALT].ativo))
		camera.y+= scrollSpeed;
	else if(tecla[KB_CIMA].pressionado || (mouse->wy > 0 && tecla[KB_LCONTROL].ativo) || (mouse->y < 200 && tecla[KB_LALT].ativo))
		camera.y-= scrollSpeed;
	if(tecla[KB_DIREITA].pressionado || (mouse->wx > 0 && tecla[KB_LCONTROL].ativo) || (mouse->x > 700 && tecla[KB_LALT].ativo))
		camera.x+= scrollSpeed;
	else if(tecla[KB_ESQUERDA].pressionado || (mouse->wx < 0 && tecla[KB_LCONTROL].ativo) || (mouse->x < 200 && tecla[KB_LALT].ativo))
		camera.x-= scrollSpeed;
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

	if(janela->entrada.textoUpdate()){
		TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
		SDL_Color cor = {255, 255, 255};
		input.CriaTexturaDoTexto(janela->renderer, janela->entrada.pegaTexto().c_str(), fonte, cor);
		TTF_CloseFont(fonte);
	}
	
	for(int i = 0; i < EDIT_NONE; i++)
		if(botoes[i].Pressionado()){
			estadoEditor = i;
			selecionado = 0;
		}

	if(tecla[KB_ESC].pressionado)
		estadoEditor = EDIT_MENU;

	switch (estadoEditor)
	{
	case EDIT_MAPA:
		botoes[BTN_ANT].Atualizar();
		botoes[BTN_PROX].Atualizar();
		if(botoes[BTN_ANT].Pressionado())
			selecionado--;
		else if(botoes[BTN_PROX].Pressionado())
			selecionado++;
		if(selecionado > 9)
			selecionado = 0;
		else if(selecionado < 0)
			selecionado = 9;
		break;
	case EDIT_INIMIGOS:
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Atualizar();
		botoes[BTN_SAIR].Atualizar();
		break;
	case EDIT_NONE:
		break;
	}
}

void Editor::Renderizar()
{
	SDL_Rect rect = {0, 0, 800, bordaHorizontal};
	M_Mouse* mouse = PegaMouse();
	int a;
	int offX = (camera.x+bordaLateral)%32;
	int offY = (camera.y+bordaHorizontal)%32;
	mapa.Renderizar(janela->renderer, &camera);
	SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
	if(grid){
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

	for(int i = 0; i < EDIT_NONE; i++)
		if(estadoEditor != i)
			botoes[i].Renderizar(janela->renderer);

	switch (estadoEditor)
	{
	case EDIT_MAPA:
		botoes[BTN_ANT].Renderizar(janela->renderer);
		botoes[BTN_PROX].Renderizar(janela->renderer);
		tileset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 300.0, selecionado); 
		if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			a = mouse->x + offX;
			rect.x = a-bordaLateral-offX-(a-bordaLateral)%32+bordaLateral;
			rect.y = mouse->y-bordaHorizontal-offY-(mouse->y-bordaHorizontal)%32+bordaHorizontal;			
			rect.w = rect.h = 32;
			tileset.Renderizar(janela->renderer, rect.x, rect.y, selecionado); 
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
	case EDIT_MENU:
		botoes[BTN_SALVAR].Renderizar(janela->renderer);
		botoes[BTN_SAIR].Renderizar(janela->renderer);
		input.Renderizar(janela->renderer, 5, 5);
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
	if(PegaTecla()[KB_ENCERRA].pressionado || botoes[BTN_SAIR].Pressionado())
		return 0;
	return this;
}
	
Editor::~Editor()
{
}