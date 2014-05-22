#include "Editor.h"
#include "Janela.h"
#include "Lobisomem.h"
#include "Crowley.h"
#include "Lucifer.h"
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
	grid = input = false;
	inisel = 0;

	gerenteAtores.Inicializar(janela);

	janela->entrada.SetaTamanhoTexto(8);
	
	mapa.Carregar(nome);
	mapa.Inicializar(janela->renderer);
	ifstream mobfile("resources/maps/"+nome+"/mob.equest", ios_base::binary);
	if(mobfile.is_open()){
		unsigned int id, qtd;
		int posX, posY;
		Atributos atributos;
		mobfile.read((char*)&qtd, sizeof(unsigned int));
		for(unsigned int i = 0; i < qtd; i++){
			mobfile.read((char*)&id, sizeof(unsigned int));
			mobfile.read((char*)&posX, sizeof(int));
			mobfile.read((char*)&posY, sizeof(int));
			mobfile.read((char*)&atributos, sizeof(Atributos));
			Inimigo* a = 0;
			switch (id)
			{
			case 0:
				inimigos.push_back(a = new Lobisomem(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
				break;
			case 1:
				inimigos.push_back(a = new Crowley(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
				break;
			case 2:
				inimigos.push_back(a = new Lucifer(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
				break;
			default:
				break;
			}
			if(a){
				a->Inicializar();
			}
		}
		mobfile.close();
	}

	tileset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/tileset.png", 32);
	mobset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/mobset.png", 32);
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	TTF_Font* fonteS = TTF_OpenFont("resources/fonts/pix.ttf", 22);
	TTF_Font* fonte2 = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	SDL_Color cor = {0, 0, 0};
	SDL_Color cor2 = {255, 255, 255};
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
	botoes[BTN_MODIFICAR].Inicializar(janela->renderer, "Modificar", fonteS, cor);
	botoes[BTN_SAIR].Inicializar(janela->renderer, "Sair", fonte, cor);
	botoes[BTN_MINUS].Inicializar(janela->renderer, "-", fonte, cor);
	botoes[BTN_PLUS].Inicializar(janela->renderer, "+", fonte, cor);
	botoes[BTN_SALVAR].Inicializar(janela->renderer, "Salvar", fonte, cor);
	botoes[BTN_CARREGAR].Inicializar(janela->renderer, "Carregar", fonteS, cor);
	botoes[BTN_GRID].Inicializar(janela->renderer, "Grid", fonte, cor);
	botoes[BTN_ALTNOME].Inicializar(janela->renderer, "Alterar nome", fonte2, cor);
	int px = 800;
	for(int i = EDIT_NONE; i > 0; i--){
		px -= 10+botoes[i-1].PegaDimensao().w;
		botoes[i-1].SetaPosicao(px, 10);
	}
	
	botoes[BTN_ANT].SetaPosicao(5, 500);
	botoes[BTN_PROX].SetaPosicao(bordaLateral-5-botoes[BTN_PROX].PegaDimensao().w, 500);
	botoes[BTN_MODIFICAR].SetaPosicao((bordaLateral-botoes[BTN_MODIFICAR].PegaDimensao().w)/2, 350);

	botoes[BTN_SAIR].SetaPosicao((bordaLateral-botoes[BTN_SAIR].PegaDimensao().w)/2, 500);
	botoes[BTN_SALVAR].SetaPosicao((bordaLateral-botoes[BTN_SALVAR].PegaDimensao().w)/2, 400);
	botoes[BTN_CARREGAR].SetaPosicao((bordaLateral-botoes[BTN_CARREGAR].PegaDimensao().w)/2, 450);
	botoes[BTN_GRID].SetaPosicao((bordaLateral-botoes[BTN_GRID].PegaDimensao().w)/2, 300);
	botoes[BTN_ALTNOME].SetaPosicao((bordaLateral-botoes[BTN_ALTNOME].PegaDimensao().w)/2, bordaHorizontal+35);
	botoes[BTN_MINUS].SetaPosicao(5, 200);
	botoes[BTN_PLUS].SetaPosicao(bordaLateral-5-botoes[BTN_PLUS].PegaDimensao().w, 200);
	
	stats[STAT_LARGURA].botao.Inicializar(janela->renderer, "Largura", fonteS, cor);
	stats[STAT_LARGURA].data = mapa.PegaDimensaoemTiles().w;
	stats[STAT_LARGURA].min = 24;
	stats[STAT_LARGURA].estado = EDIT_MAPA;
	stats[STAT_LARGURA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_LARGURA].data).c_str(), fonte, cor2);
	stats[STAT_LARGURA].botao.SetaPosicao((bordaLateral-stats[STAT_LARGURA].botao.PegaDimensao().w)/2, 230);

	stats[STAT_ALTURA].botao.Inicializar(janela->renderer, "Altura", fonteS, cor);
	stats[STAT_ALTURA].data = mapa.PegaDimensaoemTiles().h;
	stats[STAT_ALTURA].min = 24;
	stats[STAT_ALTURA].estado = EDIT_MAPA;
	stats[STAT_ALTURA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_ALTURA].data).c_str(), fonte, cor2);
	stats[STAT_ALTURA].botao.SetaPosicao((bordaLateral-stats[STAT_ALTURA].botao.PegaDimensao().w)/2, 300);

	/*INIMIGO*/ //STAT_HP, STAT_HPR, STAT_FORCA, STAT_DEFESA, STAT_MAGIA
	stats[STAT_HP].botao.Inicializar(janela->renderer, "HP", fonteS, cor);
	stats[STAT_HP].data = 100;
	stats[STAT_HP].min = 0;
	stats[STAT_HP].estado = EDIT_INIMIGOS;
	stats[STAT_HP].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_HP].data).c_str(), fonte, cor2);
	stats[STAT_HP].botao.SetaPosicao((bordaLateral-stats[STAT_HP].botao.PegaDimensao().w)/2, 130);

	stats[STAT_HPR].botao.Inicializar(janela->renderer, "HP/S", fonteS, cor);
	stats[STAT_HPR].data = 1;
	stats[STAT_HPR].min = 0;
	stats[STAT_HPR].estado = EDIT_INIMIGOS;
	stats[STAT_HPR].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_HPR].data).c_str(), fonte, cor2);
	stats[STAT_HPR].botao.SetaPosicao((bordaLateral-stats[STAT_HPR].botao.PegaDimensao().w)/2, 200);

	stats[STAT_FORCA].botao.Inicializar(janela->renderer, "Forca", fonteS, cor);
	stats[STAT_FORCA].data = 5;
	stats[STAT_FORCA].min = 0;
	stats[STAT_FORCA].estado = EDIT_INIMIGOS;
	stats[STAT_FORCA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_FORCA].data).c_str(), fonte, cor2);
	stats[STAT_FORCA].botao.SetaPosicao((bordaLateral-stats[STAT_FORCA].botao.PegaDimensao().w)/2, 270);

	stats[STAT_DEFESA].botao.Inicializar(janela->renderer, "Defesa", fonteS, cor);
	stats[STAT_DEFESA].data = 5;
	stats[STAT_DEFESA].min = 0;
	stats[STAT_DEFESA].estado = EDIT_INIMIGOS;
	stats[STAT_DEFESA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_DEFESA].data).c_str(), fonte, cor2);
	stats[STAT_DEFESA].botao.SetaPosicao((bordaLateral-stats[STAT_DEFESA].botao.PegaDimensao().w)/2, 340);

	stats[STAT_MAGIA].botao.Inicializar(janela->renderer, "Magia", fonteS, cor);
	stats[STAT_MAGIA].data = 5;
	stats[STAT_MAGIA].min = 0;
	stats[STAT_MAGIA].estado = EDIT_INIMIGOS;
	stats[STAT_MAGIA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_MAGIA].data).c_str(), fonte, cor2);
	stats[STAT_MAGIA].botao.SetaPosicao((bordaLateral-stats[STAT_MAGIA].botao.PegaDimensao().w)/2, 410);

	camera.x = -bordaLateral;
	camera.y = -bordaHorizontal;
	camera.w = w;
	camera.h = h;
	
	TTF_CloseFont(fonte);
	TTF_CloseFont(fonteS);
	TTF_CloseFont(fonte2);
}

void Editor::Atualizar(Uint32 deltaTime)
{
	//printf("%d\t", deltaTime);
	int largura, altura;
	M_Mouse* mouse = PegaMouse();
	KB_Botao* tecla = PegaTecla();
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 22);
	TTF_Font* fonte2 = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {255, 255, 255};
	SDL_Color cor2 = {255, 0, 0};
	SDL_Rect mouserect = {mouse->x+camera.x, mouse->y+camera.y, 1, 1};
	
	largura = mapa.PegaDimensaoAbsoluta().w;
	altura = mapa.PegaDimensaoAbsoluta().h;

	for(int i = 0; i < EDIT_NONE; i++)
		if(estadoEditor != i)
			botoes[i].Atualizar(mouse);

	for(int i = 0; i < EDIT_NONE; i++){
		if(botoes[i].Pressionado()){
			estadoEditor = i;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		}
	}

	if(!input){
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

		if(tecla[KB_ESC].pressionado || tecla[KB_M].pressionado){
			estadoEditor = EDIT_MENU;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		} else if(tecla[KB_Q].pressionado){
			estadoEditor = EDIT_MAPA;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		} else if(tecla[KB_W].pressionado){
			estadoEditor = EDIT_INIMIGOS;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		} else if(tecla[KB_E].pressionado){
			estadoEditor = EDIT_ARMADILHAS;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		} else if(tecla[KB_R].pressionado){
			estadoEditor = EDIT_ITENS;
			selecionado = 0;
			if(input)
				input = janela->entrada.toggleInputTexto();
		}
	}

	for(int i = 0; i < STAT_MAX; i++){
		if(stats[i].estado == estadoEditor){
			stats[i].botao.Atualizar(mouse);
			if(stats[i].botao.Hover()){
				if(mouse->wy > 0){
					stats[i].data += tecla[KB_LSHIFT].ativo ? 10 : 1;
					stats[i].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[i].data).c_str(), fonte2, cor);
				}
				else if(mouse->wy < 0){
					stats[i].data -= tecla[KB_LSHIFT].ativo ? 10 : 1;
					if(stats[i].data < stats[i].min)
						stats[i].data = stats[i].min;
					stats[i].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[i].data).c_str(), fonte2, cor);
				}
			}
		}
	}
	switch (estadoEditor)
	{
	case EDIT_MAPA:
		botoes[BTN_ANT].Atualizar(mouse);
		botoes[BTN_PROX].Atualizar(mouse);
		botoes[BTN_MODIFICAR].Atualizar(mouse);
		if(botoes[BTN_ANT].Pressionado())
			selecionado--;
		else if(botoes[BTN_PROX].Pressionado())
			selecionado++;
		if(selecionado > 9)
			selecionado = 0;
		else if(selecionado < 0)
			selecionado = 9;
		if(botoes[BTN_MODIFICAR].Pressionado()){
			mapa.Novo(stats[STAT_LARGURA].data, stats[STAT_ALTURA].data);
			mapa.Inicializar(janela->renderer);
		}
		if(mouse->botoes[M_ESQUERDO].ativo && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			if(mapa.Alterar((mouse->x+camera.x)/32, (mouse->y+camera.y)/32, selecionado)){
				mapa.Inicializar(janela->renderer);
			}
		}
		break;
	case EDIT_INIMIGOS:
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
		if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			bool colidiu = false;
			SDL_Rect col;
			if(!inimigos.empty()){
				for(unsigned int i = 0; i < inimigos.size(); i++){
					if(SDL_IntersectRect(&mouserect, &inimigos[i]->PegaBoundingBox(), &col) == SDL_TRUE){
						colidiu = true;
					}
				}
			}
			if(!colidiu){
				Atributos atributos = {stats[STAT_HP].data, stats[STAT_HP].data, stats[STAT_HPR].data, 0, 0, 0, stats[STAT_FORCA].data, stats[STAT_DEFESA].data, stats[STAT_MAGIA].data};
				Inimigo* a = 0;
				switch (selecionado)
				{
				case 0:
					inimigos.push_back(a = new Lobisomem(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
					break;
				case 1:
					inimigos.push_back(a = new Crowley(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
					break;
				case 2:
					inimigos.push_back(a = new Lucifer(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
					break;
				default:
					break;
				}
				if(a){
					a->Inicializar();
				}
			}
		}
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Atualizar(mouse);
		botoes[BTN_CARREGAR].Atualizar(mouse);
		botoes[BTN_SAIR].Atualizar(mouse);
		botoes[BTN_MINUS].Atualizar(mouse);
		botoes[BTN_PLUS].Atualizar(mouse);
		botoes[BTN_ALTNOME].Atualizar(mouse);
		botoes[BTN_GRID].Atualizar(mouse);
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
			if(!inimigos.empty()){
				ofstream mobfile("resources/maps/"+nome+"/mob.equest", ios_base::binary);
				if(mobfile.is_open()){
					unsigned int id, qtd;
					int posX, posY;
					qtd = inimigos.size();
					mobfile.write((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < inimigos.size(); i++){
						id = inimigos[i]->PegaId();
						posX = inimigos[i]->PegaBoundingBox().x;
						posY = inimigos[i]->PegaBoundingBox().y;
						mobfile.write((char*)&id, sizeof(unsigned int));
						mobfile.write((char*)&posX, sizeof(int));
						mobfile.write((char*)&posY, sizeof(int));
						mobfile.write((char*)&inimigos[i]->PegaAtributos(), sizeof(Atributos));
					}
					mobfile.close();
				}
			}
		}
		if(botoes[BTN_CARREGAR].Pressionado()){
			if(mapa.Carregar(nome)){
				mapa.Inicializar(janela->renderer);
				if(!inimigos.empty()){
					for(unsigned int i = 0; i < inimigos.size(); i++){
						inimigos[i]->Finalizar();
						delete inimigos[i];
						inimigos[i] = 0;
					}
				}
				inimigos.clear();
				ifstream mobfile("resources/maps/"+nome+"/mob.equest", ios_base::binary);
				if(mobfile.is_open()){
					unsigned int id, qtd;
					int posX, posY;
					Atributos atributos;
					mobfile.read((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < qtd; i++){
						mobfile.read((char*)&id, sizeof(unsigned int));
						mobfile.read((char*)&posX, sizeof(int));
						mobfile.read((char*)&posY, sizeof(int));
						mobfile.read((char*)&atributos, sizeof(Atributos));
						Inimigo* a = 0;
						switch (id)
						{
						case 0:
							inimigos.push_back(a = new Lobisomem(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
							break;
						case 1:
							inimigos.push_back(a = new Crowley(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
							break;
						case 2:
							inimigos.push_back(a = new Lucifer(gerenteAtores, posX, posY, atributos, 0, &mapa)); 
							break;
						default:
							break;
						}
						if(a){
							a->Inicializar();
						}
					}
					mobfile.close();
				}
			}
		}
		if(botoes[BTN_GRID].Pressionado()){
			grid = !grid;
		}
		if(botoes[BTN_ALTNOME].Pressionado()){
			input = janela->entrada.toggleInputTexto();
			if(!input)
				nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonte, cor);
		}
		break;
	case EDIT_NONE:
		break;
	}
	
	if(janela->entrada.textoUpdate()){
		nome = janela->entrada.pegaTexto();
		nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonte, cor2);
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

	if(!inimigos.empty()){
		for(unsigned int i = 0; i < inimigos.size(); i++){
			inimigos[i]->Renderizar(&camera);
		}
	}
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

	for(int i = 0; i < EDIT_NONE; i++){
		if(estadoEditor != i){
			botoes[i].Renderizar(janela->renderer);
		}
	}

	for(int i = 0; i < STAT_MAX; i++){
		if(stats[i].estado == estadoEditor){
			stats[i].botao.Renderizar(janela->renderer);
			stats[i].sprite.Renderizar(janela->renderer, (bordaLateral-stats[i].sprite.PegaDimensao().w)/2, stats[i].botao.PegaPosicao().y-30);
		}
	}

	nomeMapa.Renderizar(janela->renderer, (bordaLateral-nomeMapa.PegaDimensao().w)/2, bordaHorizontal +5);

	switch (estadoEditor)
	{
	case EDIT_MAPA:
		botoes[BTN_ANT].Renderizar(janela->renderer);
		botoes[BTN_PROX].Renderizar(janela->renderer);
		botoes[BTN_MODIFICAR].Renderizar(janela->renderer);
		tileset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 500.0, selecionado);
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
		botoes[BTN_ANT].Renderizar(janela->renderer);
		botoes[BTN_PROX].Renderizar(janela->renderer);
		mobset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 500.0, selecionado);
		if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			mobset.Renderizar(janela->renderer, mouse->x, mouse->y, selecionado);
		}
		break;
	case EDIT_ARMADILHAS:
		break;
	case EDIT_ITENS:
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Renderizar(janela->renderer);
		botoes[BTN_CARREGAR].Renderizar(janela->renderer);
		botoes[BTN_SAIR].Renderizar(janela->renderer);
		botoes[BTN_MINUS].Renderizar(janela->renderer);
		botoes[BTN_PLUS].Renderizar(janela->renderer);
		botoes[BTN_ALTNOME].Renderizar(janela->renderer);
		botoes[BTN_GRID].Renderizar(janela->renderer);
		scrollSpd.Renderizar(janela->renderer, (bordaLateral-scrollSpd.PegaDimensao().w)/2, 204);
		scrollTxt.Renderizar(janela->renderer, (bordaLateral-scrollTxt.PegaDimensao().w)/2, 170);
		break;
	case EDIT_NONE:
		break;
	}
}

void Editor::Finalizar()
{
	if(!inimigos.empty()){
		for(unsigned int i = 0; i < inimigos.size(); i++){
			inimigos[i]->Finalizar();
			delete inimigos[i];
			inimigos[i] = 0;
		}
	}
	inimigos.clear();
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