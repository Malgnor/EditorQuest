#include "Editor.h"
#include "Janela.h"
#include <fstream>

using namespace std;

Editor::Editor(string _nome)
	: nome(_nome)
{
}

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
	TTF_Font* fonteS = TTF_OpenFont("resources/fonts/pix.ttf", 22);
	SDL_Color cor = {0, 0, 0};
	SDL_Color cor2 = {255, 255, 255};
	input.CriaTexturaDoTexto(janela->renderer, " ", fonte, cor);
	scrollSpd.CriaTexturaDoTexto(janela->renderer, to_string(scrollSpeed).c_str(), fonte, cor2);
	scrollTxt.CriaTexturaDoTexto(janela->renderer, "Scroll Speed", fonteS, cor2);
	nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonteS, cor2);
	botoes[BTN_MAPA].Inicializar(janela->renderer, "Tile", fonte, cor);
	botoes[BTN_INIMIGOS].Inicializar(janela->renderer, "Inimigo", fonte, cor);
	botoes[BTN_ARMADILHAS].Inicializar(janela->renderer, "Armadilha", fonte, cor);
	botoes[BTN_ITENS].Inicializar(janela->renderer, "Item", fonte, cor);
	botoes[BTN_MENU].Inicializar(janela->renderer, "Menu", fonte, cor);
	botoes[BTN_PROX].Inicializar(janela->renderer, ">", fonte, cor);
	botoes[BTN_ANT].Inicializar(janela->renderer, "<", fonte, cor);
	botoes[BTN_SAIR].Inicializar(janela->renderer, "Sair", fonte, cor);
	botoes[BTN_MINUS].Inicializar(janela->renderer, "-", fonte, cor);
	botoes[BTN_PLUS].Inicializar(janela->renderer, "+", fonte, cor);
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
	botoes[BTN_MINUS].SetaPosicao(5, 200);
	botoes[BTN_PLUS].SetaPosicao(bordaLateral-5-botoes[BTN_PLUS].PegaDimensao().w, 200);

	mapa.Carregar(nome);
	

	mapa.Inicializar(janela->renderer);
	camera.x = -bordaLateral;
	camera.y = -bordaHorizontal;
	camera.w = w;
	camera.h = h;
	
	TTF_CloseFont(fonte);
	TTF_CloseFont(fonteS);
}

void Editor::Atualizar(Uint32 deltaTime)
{
	//printf("%d\t", deltaTime);
	int largura, altura;
	M_Mouse* mouse = PegaMouse();
	KB_Botao* tecla = PegaTecla();
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	TTF_Font* fonte2 = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {255, 255, 255};
	largura = mapa.PegaDimensaoAbsoluta().w;
	altura = mapa.PegaDimensaoAbsoluta().h;

	for(int i = 0; i < EDIT_NONE; i++)
		if(estadoEditor != i)
			botoes[i].Atualizar(mouse);
	
	if(tecla[KB_BAIXO].pressionado || (mouse->wy < 0 && tecla[KB_LCONTROL].ativo) || (mouse->y > 400 && tecla[KB_LALT].ativo))
		camera.y+= scrollSpeed;
	else if(tecla[KB_CIMA].pressionado || (mouse->wy > 0 && tecla[KB_LCONTROL].ativo) || (mouse->y < 300 && tecla[KB_LALT].ativo))
		camera.y-= scrollSpeed;
	if(tecla[KB_DIREITA].pressionado || (mouse->wx > 0 && tecla[KB_LCONTROL].ativo) || (mouse->x > 600 && tecla[KB_LALT].ativo))
		camera.x+= scrollSpeed;
	else if(tecla[KB_ESQUERDA].pressionado || (mouse->wx < 0 && tecla[KB_LCONTROL].ativo) || (mouse->x < 300 && tecla[KB_LALT].ativo))
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
		input.CriaTexturaDoTexto(janela->renderer, janela->entrada.pegaTexto().c_str(), fonte, cor);
	}
	
	for(int i = 0; i < EDIT_NONE; i++)
		if(botoes[i].Pressionado()){
			estadoEditor = i;
			selecionado = 0;
		}

	if(tecla[KB_1].pressionado)
		selecionado = 1;
	else if(tecla[KB_2].pressionado)
		selecionado = 2;
	else if(tecla[KB_3].pressionado)
		selecionado = 3;
	else if(tecla[KB_4].pressionado)
		selecionado = 4;
	else if(tecla[KB_5].pressionado)
		selecionado = 5;
	else if(tecla[KB_6].pressionado)
		selecionado = 6;
	else if(tecla[KB_7].pressionado)
		selecionado = 7;
	else if(tecla[KB_8].pressionado)
		selecionado = 8;
	else if(tecla[KB_9].pressionado)
		selecionado = 9;
	else if(tecla[KB_0].pressionado)
		selecionado = 0;

	if(tecla[KB_ESC].pressionado)
		estadoEditor = EDIT_MENU;

	switch (estadoEditor)
	{
	case EDIT_MAPA:
		botoes[BTN_ANT].Atualizar(mouse);
		botoes[BTN_PROX].Atualizar(mouse);
		if(botoes[BTN_ANT].Pressionado())
			selecionado--;
		else if(botoes[BTN_PROX].Pressionado())
			selecionado++;
		if(selecionado > 9)
			selecionado = 0;
		else if(selecionado < 0)
			selecionado = 9;
		if(mouse->botoes[M_ESQUERDO].ativo && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal)
			if(mapa.Alterar((mouse->x+camera.x)/32, (mouse->y+camera.y)/32, selecionado))
				mapa.Inicializar(janela->renderer);
		break;
	case EDIT_INIMIGOS:
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Atualizar(mouse);
		botoes[BTN_SAIR].Atualizar(mouse);
		botoes[BTN_MINUS].Atualizar(mouse);
		botoes[BTN_PLUS].Atualizar(mouse);
		if(botoes[BTN_MINUS].Pressed() && scrollSpeed > 1){
			scrollSpeed--;
			scrollSpd.CriaTexturaDoTexto(janela->renderer, to_string(scrollSpeed).c_str(), fonte2, cor);

		}
		if(botoes[BTN_PLUS].Pressed() && scrollSpeed < 99){
			scrollSpeed++;
			scrollSpd.CriaTexturaDoTexto(janela->renderer, to_string(scrollSpeed).c_str(), fonte2, cor);
		}
		if(botoes[BTN_SALVAR].Pressionado()){
			mapa.Salvar(nome);
		}
		break;
	case EDIT_NONE:
		break;
	}
	
	TTF_CloseFont(fonte);
	TTF_CloseFont(fonte2);
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
	nomeMapa.Renderizar(janela->renderer, 5, bordaHorizontal +5);
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
		botoes[BTN_MINUS].Renderizar(janela->renderer);
		botoes[BTN_PLUS].Renderizar(janela->renderer);
		input.Renderizar(janela->renderer, 5, 5);
		scrollSpd.Renderizar(janela->renderer, (bordaLateral-scrollSpd.PegaDimensao().w)/2, 204);
		scrollTxt.Renderizar(janela->renderer, (bordaLateral-scrollTxt.PegaDimensao().w)/2, 170);
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