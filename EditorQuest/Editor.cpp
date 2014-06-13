#include "Editor.h"
#include "Janela.h"
#include "Lobisomem.h"
#include "Crowley.h"
#include "Lucifer.h"
#include "Consumavel.h"
#include "Equipamento.h"
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
	selecionado = selecionado2 = eInput = 0;
	grid = input = edit = false;
	inisel = 0;
	armsel = 0;
	itemsel = 0;

	initX = initY = -100;

	nomes[0] = "Arma";
	nomes[1] = "Capacete";
	nomes[2] = "Peitoral";
	nomes[3] = "Calca";
	nomes[4] = "Botas";
	nomes[5] = "Pocao";

	desc[0] = "Uma arma";
	desc[1] = "Um capacete";
	desc[2] = "Um peitoral";
	desc[3] = "Uma calca";
	desc[4] = "Um par de botas";
	desc[5] = "Uma pocao";

	gerenteAtores.Inicializar(janela);

	janela->entrada.SetaTamanhoTexto(8);
	
	mapa.Carregar(nome);
	mapa.Inicializar(janela->renderer);
	ifstream headerfile("resources/maps/"+nome+".header", ios_base::binary);
	if(headerfile.is_open()){
		unsigned int size;
		headerfile.read((char*)&initX, sizeof(int));
		headerfile.read((char*)&initY, sizeof(int));
		headerfile.read((char*)&size, sizeof(unsigned int));
		headerfile.read((char*)proxMapa.c_str(), size);
		proxMapa = proxMapa.c_str();
		headerfile.close();
	}

	ifstream mobfile("resources/maps/"+nome+".mob", ios_base::binary);
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

	ifstream armfile("resources/maps/"+nome+".arm", ios_base::binary);
	if(armfile.is_open()){
		unsigned int id, qtd;
		int posX, posY, dano;
		double dir;
		armfile.read((char*)&qtd, sizeof(unsigned int));
		for(unsigned int i = 0; i < qtd; i++){
			armfile.read((char*)&id, sizeof(unsigned int));
			armfile.read((char*)&posX, sizeof(int));
			armfile.read((char*)&posY, sizeof(int));
			armfile.read((char*)&dano, sizeof(int));
			armfile.read((char*)&dir, sizeof(double));
			Armadilha* a = 0;
			armadilhas.push_back(a = new Armadilha(gerenteAtores, posX, posY, dir, id, dano));
			if(a){
				a->Inicializar();
			}
		}
		armfile.close();
	}

	ifstream itemfile("resources/maps/"+nome+".item", ios_base::binary);
	if(itemfile.is_open()){
		unsigned int id, id2, qtd;
		int posX, posY;
		Atributos atributos;
		itemfile.read((char*)&qtd, sizeof(unsigned int));
		for(unsigned int i = 0; i < qtd; i++){
			itemfile.read((char*)&id, sizeof(unsigned int));
			itemfile.read((char*)&id2, sizeof(unsigned int));
			itemfile.read((char*)&posX, sizeof(int));
			itemfile.read((char*)&posY, sizeof(int));
			itemfile.read((char*)&atributos, sizeof(Atributos));
			DropItem* a = 0;
			Item* b = 0;
			if(id2 == 5){
				b = new Consumavel(janela->renderer, nomes[id2], desc[id2], atributos, id);
			} else {
				b = new Equipamento(janela->renderer, nomes[id2], desc[id2], atributos, id2, id);
			}
			if(b){
				items.push_back(a = new DropItem(gerenteAtores, b, posX, posY, true));
				if(a){
					a->Inicializar();
				} 
			}
		}
		itemfile.close();
	}

	tileset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/tileset.png", 32);
	mobset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/mobset.png", 32);
	armset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/armset.png", 32);
	itemset.CriaTexturaDaImagem(janela->renderer, "resources/imgs/itemset.png", 32, 32);
	player.CriaTexturaDaImagemC(janela->renderer, "resources/sprites/vlad.png", 33, 48);
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	TTF_Font* fonteS = TTF_OpenFont("resources/fonts/pix.ttf", 22);
	TTF_Font* fonte2 = TTF_OpenFont("resources/fonts/pix.ttf", 16);
	SDL_Color cor = {0, 0, 0};
	SDL_Color cor2 = {255, 255, 255};
	nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonteS, cor2);
	nomeprox.CriaTexturaDoTexto(janela->renderer, proxMapa.c_str(), fonteS, cor2);
	botoes[BTN_MAPA].Inicializar(janela->renderer, "Tile", fonte, cor);
	botoes[BTN_INIMIGOS].Inicializar(janela->renderer, "Inimigo", fonte, cor);
	botoes[BTN_ARMADILHAS].Inicializar(janela->renderer, "Armadilha", fonte, cor);
	botoes[BTN_ITENS].Inicializar(janela->renderer, "Item", fonte, cor);
	botoes[BTN_MENU].Inicializar(janela->renderer, "Menu", fonte, cor);
	botoes[BTN_PROX].Inicializar(janela->renderer, ">", fonte, cor);
	botoes[BTN_ANT].Inicializar(janela->renderer, "<", fonte, cor);
	botoes[BTN_MODIFICAR].Inicializar(janela->renderer, "Modificar", fonteS, cor);
	botoes[BTN_BOSS].Inicializar(janela->renderer, "Boss", fonteS, cor);
	botoes[BTN_REMOVER].Inicializar(janela->renderer, "Remover", fonteS, cor);
	botoes[BTN_BAIXO].Inicializar(janela->renderer, "\\/", fonteS, cor);
	botoes[BTN_SAIR].Inicializar(janela->renderer, "Sair", fonte, cor);
	botoes[BTN_SALVAR].Inicializar(janela->renderer, "Salvar", fonte, cor);
	botoes[BTN_CARREGAR].Inicializar(janela->renderer, "Carregar", fonteS, cor);
	botoes[BTN_GRID].Inicializar(janela->renderer, "Grid", fonte, cor);
	botoes[BTN_ALTNOME].Inicializar(janela->renderer, "Alterar nome", fonte2, cor);
	botoes[BTN_PROXNOME].Inicializar(janela->renderer, "Proximo mapa", fonte2, cor);
	int px = 800;
	for(int i = EDIT_NONE; i > 0; i--){
		px -= 10+botoes[i-1].PegaDimensao().w;
		botoes[i-1].SetaPosicao(px, 10);
	}
	
	botoes[BTN_BAIXO].SetaPosicao((bordaLateral-botoes[BTN_BAIXO].PegaDimensao().w)/2, 535);

	botoes[BTN_ANT].SetaPosicao(5, 500);
	botoes[BTN_PROX].SetaPosicao(bordaLateral-5-botoes[BTN_PROX].PegaDimensao().w, 500);
	botoes[BTN_MODIFICAR].SetaPosicao((bordaLateral-botoes[BTN_MODIFICAR].PegaDimensao().w)/2, 350);

	botoes[BTN_BOSS].SetaPosicao((bordaLateral-botoes[BTN_BOSS].PegaDimensao().w)/2, 500);
	botoes[BTN_REMOVER].SetaPosicao((bordaLateral-botoes[BTN_REMOVER].PegaDimensao().w)/2, 550);

	botoes[BTN_SAIR].SetaPosicao((bordaLateral-botoes[BTN_SAIR].PegaDimensao().w)/2, 500);
	botoes[BTN_SALVAR].SetaPosicao((bordaLateral-botoes[BTN_SALVAR].PegaDimensao().w)/2, 400);
	botoes[BTN_CARREGAR].SetaPosicao((bordaLateral-botoes[BTN_CARREGAR].PegaDimensao().w)/2, 450);
	botoes[BTN_GRID].SetaPosicao((bordaLateral-botoes[BTN_GRID].PegaDimensao().w)/2, 300);
	botoes[BTN_ALTNOME].SetaPosicao((bordaLateral-botoes[BTN_ALTNOME].PegaDimensao().w)/2, bordaHorizontal+35);
	botoes[BTN_PROXNOME].SetaPosicao((bordaLateral-botoes[BTN_PROXNOME].PegaDimensao().w)/2, bordaHorizontal+100);
	
	stats[STAT_LARGURA].botao.Inicializar(janela->renderer, "Largura", fonteS, cor);
	stats[STAT_LARGURA].data = mapa.PegaDimensaoemTiles().w;
	stats[STAT_LARGURA].min = 1;
	stats[STAT_LARGURA].estado = EDIT_MAPA;
	stats[STAT_LARGURA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_LARGURA].data).c_str(), fonte, cor2);
	stats[STAT_LARGURA].botao.SetaPosicao((bordaLateral-stats[STAT_LARGURA].botao.PegaDimensao().w)/2, 230);

	stats[STAT_ALTURA].botao.Inicializar(janela->renderer, "Altura", fonteS, cor);
	stats[STAT_ALTURA].data = mapa.PegaDimensaoemTiles().h;
	stats[STAT_ALTURA].min = 1;
	stats[STAT_ALTURA].estado = EDIT_MAPA;
	stats[STAT_ALTURA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_ALTURA].data).c_str(), fonte, cor2);
	stats[STAT_ALTURA].botao.SetaPosicao((bordaLateral-stats[STAT_ALTURA].botao.PegaDimensao().w)/2, 300);

	/*INIMIGO*/ //STAT_HP, STAT_HPR, STAT_FORCA, STAT_DEFESA, STAT_MAGIA
	stats[STAT_HP].botao.Inicializar(janela->renderer, "HP", fonteS, cor);
	stats[STAT_HP].data = 100;
	stats[STAT_HP].min = 1;
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
	stats[STAT_DEFESA].min = -999;
	stats[STAT_DEFESA].estado = EDIT_INIMIGOS;
	stats[STAT_DEFESA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_DEFESA].data).c_str(), fonte, cor2);
	stats[STAT_DEFESA].botao.SetaPosicao((bordaLateral-stats[STAT_DEFESA].botao.PegaDimensao().w)/2, 340);

	stats[STAT_MAGIA].botao.Inicializar(janela->renderer, "Magia", fonteS, cor);
	stats[STAT_MAGIA].data = 5;
	stats[STAT_MAGIA].min = -999;
	stats[STAT_MAGIA].estado = EDIT_INIMIGOS;
	stats[STAT_MAGIA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_MAGIA].data).c_str(), fonte, cor2);
	stats[STAT_MAGIA].botao.SetaPosicao((bordaLateral-stats[STAT_MAGIA].botao.PegaDimensao().w)/2, 410);

	/*ARMADILHA*/// STAT_DIR, STAT_DANO
	stats[STAT_DIR].botao.Inicializar(janela->renderer, "Direcao", fonteS, cor);
	stats[STAT_DIR].data = 0;
	stats[STAT_DIR].min = 0;
	stats[STAT_DIR].estado = EDIT_ARMADILHAS;
	stats[STAT_DIR].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_DIR].data).c_str(), fonte, cor2);
	stats[STAT_DIR].botao.SetaPosicao((bordaLateral-stats[STAT_DIR].botao.PegaDimensao().w)/2, 130);

	stats[STAT_DANO].botao.Inicializar(janela->renderer, "Dano", fonteS, cor);
	stats[STAT_DANO].data = 5;
	stats[STAT_DANO].min = -999;
	stats[STAT_DANO].estado = EDIT_ARMADILHAS;
	stats[STAT_DANO].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_DANO].data).c_str(), fonte, cor2);
	stats[STAT_DANO].botao.SetaPosicao((bordaLateral-stats[STAT_DANO].botao.PegaDimensao().w)/2, 200);

	/*ITENS*/// STAT_IHP, STAT_IHPR, STAT_IMP, STAT_IMPR, STAT_IFORCA, STAT_IDEFESA, STAT_IMAGIA,
	stats[STAT_IHP].botao.Inicializar(janela->renderer, "HP", fonteS, cor);
	stats[STAT_IHP].data = 5;
	stats[STAT_IHP].min = -999;
	stats[STAT_IHP].estado = EDIT_ITENS;
	stats[STAT_IHP].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IHP].data).c_str(), fonte, cor2);
	stats[STAT_IHP].botao.SetaPosicao((bordaLateral-stats[STAT_IHP].botao.PegaDimensao().w)/2, 125);

	stats[STAT_IHPR].botao.Inicializar(janela->renderer, "HP/s", fonteS, cor);
	stats[STAT_IHPR].data = 5;
	stats[STAT_IHPR].min = -999;
	stats[STAT_IHPR].estado = EDIT_ITENS;
	stats[STAT_IHPR].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IHPR].data).c_str(), fonte, cor2);
	stats[STAT_IHPR].botao.SetaPosicao((bordaLateral-stats[STAT_IHPR].botao.PegaDimensao().w)/2, 180);

	stats[STAT_IMP].botao.Inicializar(janela->renderer, "MP", fonteS, cor);
	stats[STAT_IMP].data = 5;
	stats[STAT_IMP].min = -999;
	stats[STAT_IMP].estado = EDIT_ITENS;
	stats[STAT_IMP].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IMP].data).c_str(), fonte, cor2);
	stats[STAT_IMP].botao.SetaPosicao((bordaLateral-stats[STAT_IMP].botao.PegaDimensao().w)/2, 235);

	stats[STAT_IMPR].botao.Inicializar(janela->renderer, "MP/s", fonteS, cor);
	stats[STAT_IMPR].data = 5;
	stats[STAT_IMPR].min = -999;
	stats[STAT_IMPR].estado = EDIT_ITENS;
	stats[STAT_IMPR].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IMPR].data).c_str(), fonte, cor2);
	stats[STAT_IMPR].botao.SetaPosicao((bordaLateral-stats[STAT_IMPR].botao.PegaDimensao().w)/2, 290);

	stats[STAT_IFORCA].botao.Inicializar(janela->renderer, "Forca", fonteS, cor);
	stats[STAT_IFORCA].data = 5;
	stats[STAT_IFORCA].min = -999;
	stats[STAT_IFORCA].estado = EDIT_ITENS;
	stats[STAT_IFORCA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IFORCA].data).c_str(), fonte, cor2);
	stats[STAT_IFORCA].botao.SetaPosicao((bordaLateral-stats[STAT_IFORCA].botao.PegaDimensao().w)/2, 345);

	stats[STAT_IDEFESA].botao.Inicializar(janela->renderer, "Defesa", fonteS, cor);
	stats[STAT_IDEFESA].data = 5;
	stats[STAT_IDEFESA].min = -999;
	stats[STAT_IDEFESA].estado = EDIT_ITENS;
	stats[STAT_IDEFESA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IDEFESA].data).c_str(), fonte, cor2);
	stats[STAT_IDEFESA].botao.SetaPosicao((bordaLateral-stats[STAT_IDEFESA].botao.PegaDimensao().w)/2, 400);

	stats[STAT_IMAGIA].botao.Inicializar(janela->renderer, "Magia", fonteS, cor);
	stats[STAT_IMAGIA].data = 5;
	stats[STAT_IMAGIA].min = -999;
	stats[STAT_IMAGIA].estado = EDIT_ITENS;
	stats[STAT_IMAGIA].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[STAT_IMAGIA].data).c_str(), fonte, cor2);
	stats[STAT_IMAGIA].botao.SetaPosicao((bordaLateral-stats[STAT_IMAGIA].botao.PegaDimensao().w)/2, 455);

	camera.x = -bordaLateral;
	camera.y = -bordaHorizontal;
	camera.w = w-bordaLateral;
	camera.h = h-bordaHorizontal;
	
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
		if(camera.w < largura){
			if(tecla[KB_DIREITA].pressionado || (mouse->wx > 0 && tecla[KB_LCONTROL].ativo) || (mouse->x > 600 && tecla[KB_LALT].ativo))
				camera.x+= 32;
			else if(tecla[KB_ESQUERDA].pressionado || (mouse->wx < 0 && tecla[KB_LCONTROL].ativo) || (mouse->x < 300 && tecla[KB_LALT].ativo))
				camera.x-= 32;
			if(camera.x < -bordaLateral)
				camera.x = -bordaLateral;
			else if(camera.x > largura-camera.w-bordaLateral)
				camera.x = largura-camera.w-bordaLateral;
		} else {
			camera.x = -bordaLateral;
		}

		if(altura > camera.h){
			if(tecla[KB_BAIXO].pressionado || (mouse->wy < 0 && tecla[KB_LCONTROL].ativo) || (mouse->y > 400 && tecla[KB_LALT].ativo))
				camera.y+= 32;
			else if(tecla[KB_CIMA].pressionado || (mouse->wy > 0 && tecla[KB_LCONTROL].ativo) || (mouse->y < 300 && tecla[KB_LALT].ativo))
				camera.y-= 32;
			if(camera.y < -bordaHorizontal)
				camera.y = -bordaHorizontal;
			else if(camera.y > altura-camera.h-bordaHorizontal)
				camera.y = altura-camera.h-bordaHorizontal;
		} else {
			camera.y = -bordaHorizontal;
		}

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
			if(!inimigos.empty()){
				for(unsigned int i = 0; i < inimigos.size(); i++){
					inimigos[i]->Finalizar();
					delete inimigos[i];
					inimigos[i] = 0;
				}
			}
			inimigos.clear();
			inisel = 0;

			if(!armadilhas.empty()){
				for(unsigned int i = 0; i < armadilhas.size(); i++){
					armadilhas[i]->Finalizar();
					delete armadilhas[i];
					armadilhas[i] = 0;
				}
			}
			armadilhas.clear();
			armsel = 0;

			mapa.Novo(stats[STAT_LARGURA].data, stats[STAT_ALTURA].data);
			mapa.Inicializar(janela->renderer);
		}
		if(mouse->botoes[M_ESQUERDO].ativo && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
			if(tecla[KB_ESPACO].ativo){				
				if(mapa.AlterarBloco((mouse->x+camera.x)/32, (mouse->y+camera.y)/32, selecionado)){
					mapa.Inicializar(janela->renderer);
				}
			} else{
				if(mapa.Alterar((mouse->x+camera.x)/32, (mouse->y+camera.y)/32, selecionado)){
					mapa.Inicializar(janela->renderer);
				}
			}
		}
		break;
	case EDIT_INIMIGOS:
		if(tecla[KB_ESPACO].pressionado)
			edit = !edit;
		if(!edit){
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
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal && mouse->x+camera.x <= largura && mouse->y+camera.y <= altura){
				SDL_Rect col;
				inisel = 0;
				if(!inimigos.empty()){
					for(unsigned int i = 0; i < inimigos.size(); i++){
						if(SDL_IntersectRect(&mouserect, &inimigos[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							inisel = inimigos[i];
						}
					}
				}
				if(!inisel){
					Atributos atributos = {stats[STAT_HP].data, stats[STAT_HP].data, stats[STAT_HPR].data, 0, 0, 0, stats[STAT_FORCA].data, stats[STAT_DEFESA].data, stats[STAT_MAGIA].data};
					switch (selecionado)
					{
					case 0:
						inimigos.push_back(inisel = new Lobisomem(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
						break;
					case 1:
						inimigos.push_back(inisel = new Crowley(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
						break;
					case 2:
						inimigos.push_back(inisel = new Lucifer(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), atributos, 0, &mapa)); 
						break;
					default:
						break;
					}
					if(inisel){
						inisel->Inicializar();
					}
				}
			}
		} else {
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				SDL_Rect col;
				inisel = 0;
				if(!inimigos.empty()){
					for(unsigned int i = 0; i < inimigos.size(); i++){
						if(SDL_IntersectRect(&mouserect, &inimigos[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							inisel = inimigos[i];
						}
					}
				}
				if(inisel){
					Atributos atributos = inisel->PegaAtributos();
					stats[STAT_HP].data = atributos.hp;
					stats[STAT_HPR].data = atributos.hpregen;
					stats[STAT_FORCA].data = atributos.forca;
					stats[STAT_DEFESA].data = atributos.defesa;
					stats[STAT_MAGIA].data = atributos.magia;
					for(int i = 0; i < STAT_MAX; i++){
						if(stats[i].estado == estadoEditor){
							stats[i].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[i].data).c_str(), fonte2, cor);
						}
					}
				}
			}
			if(inisel){
				Atributos& atributos = inisel->PegaAtributos();
				atributos.hp = atributos.hpatual = stats[STAT_HP].data;
				atributos.hpregen = stats[STAT_HPR].data;
				atributos.forca = stats[STAT_FORCA].data;
				atributos.defesa = stats[STAT_DEFESA].data;
				atributos.magia = stats[STAT_MAGIA].data;

				if(inisel != inimigos[inimigos.size()-1]){
					botoes[BTN_BOSS].Atualizar(mouse);
					if(botoes[BTN_BOSS].Pressionado()){
						Inimigo* aux = inimigos[inimigos.size()-1];
						for(unsigned int i = 0; i < inimigos.size(); i++){
							if(inimigos[i] == inisel){
								inimigos[inimigos.size()-1] = inisel;
								inimigos[i] = aux;
								break;
							}
						}
					}
				}
				botoes[BTN_REMOVER].Atualizar(mouse);
				if (botoes[BTN_REMOVER].Pressionado()){
					std::vector<Inimigo*> a;
					for (unsigned int i = 0; i < inimigos.size(); i++){
						if (!(inimigos[i] == inisel)){
							a.push_back(inimigos[i]);
						}
					}
					swap(a, inimigos);
					delete inisel;
					inisel = 0;
					a.clear();
				}
			}
		}
		break;
	case EDIT_ARMADILHAS:
		if(tecla[KB_ESPACO].pressionado)
			edit = !edit;
		if(!edit){
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
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal && mouse->x+camera.x <= largura && mouse->y+camera.y <= altura){
				SDL_Rect col;
				armsel = 0;
				if(!armadilhas.empty()){
					for(unsigned int i = 0; i < armadilhas.size(); i++){
						if(SDL_IntersectRect(&mouserect, &armadilhas[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							armsel = armadilhas[i];
						}
					}
				}
				if(!armsel){
					armadilhas.push_back(armsel = new Armadilha(gerenteAtores, (mouse->x+camera.x), (mouse->y+camera.y), stats[STAT_DIR].data*M_PI/180.0, selecionado%2, stats[STAT_DANO].data));
					if(armsel){
						armsel->Inicializar();
					}
				}
			}
		} else {
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				SDL_Rect col;
				armsel = 0;
				if(!armadilhas.empty()){
					for(unsigned int i = 0; i < armadilhas.size(); i++){
						if(SDL_IntersectRect(&mouserect, &armadilhas[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							armsel = armadilhas[i];
						}
					}
				}
				if(armsel){
					stats[STAT_DIR].data = (int)(armsel->PegaDir()*180.0/M_PI);
					stats[STAT_DANO].data = armsel->PegaDano();
					for(int i = 0; i < STAT_MAX; i++){
						if(stats[i].estado == estadoEditor){
							stats[i].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[i].data).c_str(), fonte2, cor);
						}
					}
				}
			}
			if(armsel){
				armsel->PegaDir() = (double)stats[STAT_DIR].data*M_PI/180.0;
				armsel->PegaDano() = stats[STAT_DANO].data;
				botoes[BTN_REMOVER].Atualizar(mouse);
				if (botoes[BTN_REMOVER].Pressionado()){
					std::vector<Armadilha*> a;
					for (unsigned int i = 0; i < armadilhas.size(); i++){
						if (!(armadilhas[i] == armsel)){
							a.push_back(armadilhas[i]);
						}
					}
					swap(a, armadilhas);
					delete armsel;
					armsel = 0;
					a.clear();
				}
			}
		}
		break;
	case EDIT_ITENS:
		if(tecla[KB_ESPACO].pressionado)
			edit = !edit;
		if(!edit){
			botoes[BTN_ANT].Atualizar(mouse);
			botoes[BTN_PROX].Atualizar(mouse);
			botoes[BTN_BAIXO].Atualizar(mouse);
			if(botoes[BTN_ANT].Pressionado())
				selecionado--;
			else if(botoes[BTN_PROX].Pressionado())
				selecionado++;
			if(botoes[BTN_BAIXO].Pressionado()){
				selecionado2++;
				selecionado = 0;
			}
			if(selecionado > 9)
				selecionado = 0;
			else if(selecionado < 0)
				selecionado = 9;
			if(selecionado2 > 5)
				selecionado2 = 0;
			else if(selecionado2 < 0)
				selecionado2 = 5;
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal && mouse->x+camera.x <= largura && mouse->y+camera.y <= altura){
				SDL_Rect col;
				itemsel = 0;
				if(!items.empty()){
					for(unsigned int i = 0; i < items.size(); i++){
						if(SDL_IntersectRect(&mouserect, &items[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							itemsel = items[i];
						}
					}
				}
				if(!itemsel){
					Atributos atributos = {stats[STAT_IHP].data, 0, stats[STAT_IHPR].data, stats[STAT_IMP].data, 0, stats[STAT_IMPR].data, stats[STAT_IFORCA].data, stats[STAT_IDEFESA].data, stats[STAT_IMAGIA].data};
					Item* item = 0;
					if(selecionado2 == 5){
						atributos.defesa = atributos.forca = atributos.magia = atributos.hpregen = atributos.mpregen = 0;
						item = new Consumavel(janela->renderer, nomes[selecionado2], desc[selecionado2], atributos, selecionado);
					} else {
						item = new Equipamento(janela->renderer, nomes[selecionado2], desc[selecionado2], atributos, selecionado2, selecionado);
					}
					if(item){
						items.push_back(itemsel = new DropItem(gerenteAtores, item, (mouse->x+camera.x), (mouse->y+camera.y), true));
						if(itemsel){
							itemsel->Inicializar();
						} 
					}
				}
			}
		} else {
			if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				SDL_Rect col;
				itemsel = 0;
				if(!items.empty()){
					for(unsigned int i = 0; i < items.size(); i++){
						if(SDL_IntersectRect(&mouserect, &items[i]->PegaBoundingBox(), &col) == SDL_TRUE){
							itemsel = items[i];
						}
					}
				}
				if(itemsel){
					Atributos atributos = itemsel->PegaItem()->PegaAtributos();
					stats[STAT_IHP].data = atributos.hp;
					stats[STAT_IHPR].data = atributos.hpregen;
					stats[STAT_IMP].data = atributos.mp;
					stats[STAT_IMPR].data = atributos.mpregen;
					stats[STAT_IFORCA].data = atributos.forca;
					stats[STAT_IDEFESA].data = atributos.defesa;
					stats[STAT_IMAGIA].data = atributos.magia;
					for(int i = 0; i < STAT_MAX; i++){
						if(stats[i].estado == estadoEditor){
							stats[i].sprite.CriaTexturaDoTexto(janela->renderer, to_string(stats[i].data).c_str(), fonte2, cor);
						}
					}
				}
			}
			if(itemsel){
				Atributos& atributos = itemsel->PegaItem()->PegaAtributos();
				atributos.hp = stats[STAT_IHP].data;
				atributos.hpregen = stats[STAT_IHPR].data;
				atributos.mp = stats[STAT_IMP].data;
				atributos.mpregen = stats[STAT_IMPR].data;
				atributos.forca = stats[STAT_IFORCA].data;
				atributos.defesa = stats[STAT_IDEFESA].data;
				atributos.magia = stats[STAT_IMAGIA].data;

				botoes[BTN_REMOVER].Atualizar(mouse);
				if (botoes[BTN_REMOVER].Pressionado()){
					std::vector<DropItem*> a;
					for (unsigned int i = 0; i < items.size(); i++){
						if (!(items[i] == itemsel)){
							a.push_back(items[i]);
						}
					}
					swap(a, items);
					delete itemsel;
					itemsel = 0;
					a.clear();
				}
			}
		}
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Atualizar(mouse);
		botoes[BTN_CARREGAR].Atualizar(mouse);
		botoes[BTN_SAIR].Atualizar(mouse);
		botoes[BTN_ALTNOME].Atualizar(mouse);
		botoes[BTN_PROXNOME].Atualizar(mouse);
		botoes[BTN_GRID].Atualizar(mouse);

		if(mouse->botoes[M_ESQUERDO].pressionado && mouse->x >= bordaLateral && mouse->y >= bordaHorizontal && mouse->x+camera.x <= largura && mouse->y+camera.y <= altura){
			initX = (mouse->x+camera.x);
			initY = (mouse->y+camera.y);
		}

		if(botoes[BTN_SALVAR].Pressionado()){
			mapa.Salvar(nome);
			ofstream headerfile("resources/maps/"+nome+".header", ios_base::binary);
			if(headerfile.is_open()){
				headerfile.write((char*)&initX, sizeof(int));
				headerfile.write((char*)&initY, sizeof(int));
				unsigned int size = proxMapa.size()+1;
				headerfile.write((char*)&size, sizeof(unsigned int));
				headerfile.write((char*)proxMapa.c_str(), size);
				headerfile.close();
			}			

			if(!inimigos.empty()){
				ofstream mobfile("resources/maps/"+nome+".mob", ios_base::binary);
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

			if(!armadilhas.empty()){
				ofstream armfile("resources/maps/"+nome+".arm", ios_base::binary);
				if(armfile.is_open()){
					unsigned int id, qtd;
					int posX, posY, dano;
					double dir;
					qtd = armadilhas.size();
					armfile.write((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < armadilhas.size(); i++){
						id = armadilhas[i]->PegaTipoArmadilha();
						posX = armadilhas[i]->PegaBoundingBox().x;
						posY = armadilhas[i]->PegaBoundingBox().y;
						dir = armadilhas[i]->PegaDirecao();
						dano = armadilhas[i]->PegaDano();
						armfile.write((char*)&id, sizeof(unsigned int));
						armfile.write((char*)&posX, sizeof(int));
						armfile.write((char*)&posY, sizeof(int));
						armfile.write((char*)&dano, sizeof(int));
						armfile.write((char*)&dir, sizeof(double));
					}
					armfile.close();
				}
			}

			if(!items.empty()){
				ofstream itemfile("resources/maps/"+nome+".item", ios_base::binary);
				if(itemfile.is_open()){
					unsigned int id, id2, qtd;
					int posX, posY;
					qtd = items.size();
					itemfile.write((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < items.size(); i++){
						items[i]->PegaItem()->PegaXY(id, id2);
						posX = items[i]->PegaBoundingBox().x;
						posY = items[i]->PegaBoundingBox().y;
						itemfile.write((char*)&id, sizeof(unsigned int));
						itemfile.write((char*)&id2, sizeof(unsigned int));
						itemfile.write((char*)&posX, sizeof(int));
						itemfile.write((char*)&posY, sizeof(int));
						itemfile.write((char*)&items[i]->PegaItem()->PegaAtributos(), sizeof(Atributos));
					}
					itemfile.close();
				}
			}
		}
		if(botoes[BTN_CARREGAR].Pressionado()){
			if(mapa.Carregar(nome)){
				mapa.Inicializar(janela->renderer);

				ifstream headerfile("resources/maps/"+nome+".header", ios_base::binary);
				if(headerfile.is_open()){
					int size;
					headerfile.read((char*)&initX, sizeof(int));
					headerfile.read((char*)&initY, sizeof(int));
					headerfile.read((char*)&size, sizeof(int));
					headerfile.read((char*)proxMapa.c_str(), size);
					proxMapa = proxMapa.c_str();
					nomeprox.CriaTexturaDoTexto(janela->renderer, proxMapa.c_str(), fonte, cor);
					headerfile.close();
				}

				if(!inimigos.empty()){
					for(unsigned int i = 0; i < inimigos.size(); i++){
						inimigos[i]->Finalizar();
						delete inimigos[i];
						inimigos[i] = 0;
					}
				}
				inimigos.clear();
				inisel = 0;

				ifstream mobfile("resources/maps/"+nome+".mob", ios_base::binary);
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

				if(!armadilhas.empty()){
					for(unsigned int i = 0; i < armadilhas.size(); i++){
						armadilhas[i]->Finalizar();
						delete armadilhas[i];
						armadilhas[i] = 0;
					}
				}
				armadilhas.clear();
				armsel = 0;

				ifstream armfile("resources/maps/"+nome+".arm", ios_base::binary);
				if(armfile.is_open()){
					unsigned int id, qtd;
					int posX, posY, dano;
					double dir;
					armfile.read((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < qtd; i++){
						armfile.read((char*)&id, sizeof(unsigned int));
						armfile.read((char*)&posX, sizeof(int));
						armfile.read((char*)&posY, sizeof(int));
						armfile.read((char*)&dano, sizeof(int));
						armfile.read((char*)&dir, sizeof(double));
						Armadilha* a = 0;
						armadilhas.push_back(a = new Armadilha(gerenteAtores, posX, posY, dir, id, dano));
						if(a){
							a->Inicializar();
						}
					}
					armfile.close();
				}	

				if(!items.empty()){
					for(unsigned int i = 0; i < items.size(); i++){
						items[i]->Finalizar();
						delete items[i];
						items[i] = 0;
					}
				}
				items.clear();
				inisel = 0;

				ifstream itemfile("resources/maps/"+nome+".item", ios_base::binary);
				if(itemfile.is_open()){
					unsigned int id, id2, qtd;
					int posX, posY;
					Atributos atributos;
					itemfile.read((char*)&qtd, sizeof(unsigned int));
					for(unsigned int i = 0; i < qtd; i++){
						itemfile.read((char*)&id, sizeof(unsigned int));
						itemfile.read((char*)&id2, sizeof(unsigned int));
						itemfile.read((char*)&posX, sizeof(int));
						itemfile.read((char*)&posY, sizeof(int));
						itemfile.read((char*)&atributos, sizeof(Atributos));
						DropItem* a = 0;
						Item* b = 0;
						if(id2 == 5){
							b = new Consumavel(janela->renderer, nomes[id2], desc[id2], atributos, id);
						} else {
							b = new Equipamento(janela->renderer, nomes[id2], desc[id2], atributos, id2, id);
						}
						if(b){
							items.push_back(a = new DropItem(gerenteAtores, b, posX, posY, true));
							if(a){
								a->Inicializar();
							} 
						}
					}
					itemfile.close();
				}
			}
		}
		if(botoes[BTN_GRID].Pressionado()){
			grid = !grid;
		}
		if(botoes[BTN_ALTNOME].Pressionado() && eInput != 2){
			input = janela->entrada.toggleInputTexto();
			if(!input){
				eInput = 0;
				nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonte, cor);
			}
			else
				eInput = 1;
		}
		if(botoes[BTN_PROXNOME].Pressionado() && eInput != 1){
			input = janela->entrada.toggleInputTexto();
			if(!input){
				nomeprox.CriaTexturaDoTexto(janela->renderer, proxMapa.c_str(), fonte, cor);
				eInput = 0;
			}
			else
				eInput = 2;
		}
		break;
	case EDIT_NONE:
		break;
	}
	
	if(janela->entrada.textoUpdate()){
		if(eInput == 1){
			nome = janela->entrada.pegaTexto();
			nomeMapa.CriaTexturaDoTexto(janela->renderer, nome.c_str(), fonte, cor2);
		} else if(eInput == 2){			
			proxMapa = janela->entrada.pegaTexto();
			nomeprox.CriaTexturaDoTexto(janela->renderer, proxMapa.c_str(), fonte, cor2);
		}
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
	
	player.Renderizar(janela->renderer, initX-camera.x, initY-camera.y);

	if(!inimigos.empty()){
		for(unsigned int i = 0; i < inimigos.size(); i++){
			inimigos[i]->Renderizar(&camera);
		}
	}

	if(!armadilhas.empty()){
		for(unsigned int i = 0; i < armadilhas.size(); i++){
			armadilhas[i]->Render(&camera);
		}
	}

	if(!items.empty()){
		for(unsigned int i = 0; i < items.size(); i++){
			items[i]->Renderizar(&camera);
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
		if(!edit){
			botoes[BTN_ANT].Renderizar(janela->renderer);
			botoes[BTN_PROX].Renderizar(janela->renderer);
			mobset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 500.0, selecionado);
			if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				mobset.Renderizar(janela->renderer, mouse->x, mouse->y, selecionado);
			}
		} else {
			if(inisel){
				botoes[BTN_REMOVER].Renderizar(janela->renderer);
				rect = inisel->PegaBoundingBox();
				rect.x -= camera.x;
				rect.y -= camera.y;
				SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
				if(inisel == inimigos[inimigos.size()-1]){
					SDL_SetRenderDrawColor(janela->renderer, 255, 0, 0, 255);
				} else {
					botoes[BTN_BOSS].Renderizar(janela->renderer);
				}
				SDL_RenderDrawRect(janela->renderer, &rect);
			}
		}
		break;
	case EDIT_ARMADILHAS:
		if(!edit){
			botoes[BTN_ANT].Renderizar(janela->renderer);
			botoes[BTN_PROX].Renderizar(janela->renderer);
			armset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 500.0, selecionado);
			if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				armset.Renderizar(janela->renderer, mouse->x, mouse->y, selecionado, 0, selecionado%2 == 0 ? (double)stats[STAT_DIR].data*M_PI/180.0 : 0.0);
			}
		} else {
			if(armsel){
				botoes[BTN_REMOVER].Renderizar(janela->renderer);
				rect = armsel->PegaBoundingBox();
				rect.x -= camera.x;
				rect.y -= camera.y;
				SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(janela->renderer, &rect);
			}
		}
		break;
	case EDIT_ITENS:
		if(!edit){
			botoes[BTN_ANT].Renderizar(janela->renderer);
			botoes[BTN_PROX].Renderizar(janela->renderer);
			botoes[BTN_BAIXO].Renderizar(janela->renderer);
			itemset.Renderizar(janela->renderer, bordaLateral/2.0-16.0, 500.0, selecionado, selecionado2);
			if(mouse->x >= bordaLateral && mouse->y >= bordaHorizontal){
				itemset.Renderizar(janela->renderer, mouse->x, mouse->y, selecionado, selecionado2);
			}
		} else {
			if(itemsel){
				botoes[BTN_REMOVER].Renderizar(janela->renderer);
				rect = itemsel->PegaBoundingBox();
				rect.x -= camera.x;
				rect.y -= camera.y;
				SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(janela->renderer, &rect);
			}
		}
		break;
	case EDIT_MENU:
		botoes[BTN_SALVAR].Renderizar(janela->renderer);
		botoes[BTN_CARREGAR].Renderizar(janela->renderer);
		botoes[BTN_SAIR].Renderizar(janela->renderer);
		botoes[BTN_ALTNOME].Renderizar(janela->renderer);
		botoes[BTN_PROXNOME].Renderizar(janela->renderer);
		botoes[BTN_GRID].Renderizar(janela->renderer);
		nomeprox.Renderizar(janela->renderer, (bordaLateral-nomeprox.PegaDimensao().w)/2, bordaHorizontal + 75);
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
	inisel = 0;

	if(!armadilhas.empty()){
		for(unsigned int i = 0; i < armadilhas.size(); i++){
			armadilhas[i]->Finalizar();
			delete armadilhas[i];
			armadilhas[i] = 0;
		}
	}
	armadilhas.clear();
	armsel = 0;

	if(!items.empty()){
		for(unsigned int i = 0; i < items.size(); i++){
			items[i]->Finalizar();
			delete items[i];
			items[i] = 0;
		}
	}
	items.clear();
	itemsel = 0;
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