#include "Ingame.h"
#include "Lobisomem.h"
#include "Crowley.h"
#include "Lucifer.h"
#include "janela.h"
#include "MenuInicial.h"
#include "Equipamento.h"
#include "Armadilha.h"
#include <fstream>
#include <iostream>

using namespace std;

void Ingame::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Walachia - Ingame");
	janela->SetaCorFundo(0, 0, 0);

	/*	
	unsigned int map[32][32] = { 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 3, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 4, 2, 4, 4, 4, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 5, 2, 5, 5, 5, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 6, 2, 6, 6, 6, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 7, 2, 7, 7, 7, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 7, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 8, 2, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 9, 2, 9, 9, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 0, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	
	unsigned int altura, largura;
	altura = 32;
	largura = 65;
	unsigned int** map = new unsigned int*[altura];
	for(unsigned int i = 0; i < altura; i++){
		map[i] = new unsigned int[largura];
	}

	for(unsigned int i = 0; i < altura; i++){
			for(unsigned int j = 0; j < largura; j++){
				if( i == 0 || j == 0 || j == largura-1 || i == altura-1 || (0 == j%16 && i > 4) || (0 == j%8 && i < altura-4 && 0 != j%16))
					map[i][j] = 1;
				else
					map[i][j] = 2;
			}
	}

	ofstream out;
	out.open("teste.equest", std::ios_base::binary);
	if(out.is_open())
	{
		out.write((char*)&largura,sizeof(unsigned int));
		out.write((char*)&altura,sizeof(unsigned int));
		for(unsigned int i = 0; i < altura; i++)
		{
			for(unsigned int j = 0; j < largura; j++)
			{
				out.write((char*)&map[i][j],sizeof(unsigned int));
			}
		}
		out.close();
	}
	*/

	mapa.Carregar("teste");

	mapa.Inicializar(janela->renderer);	
	int w, h;
	janela->PegaTamanho(w, h);
	camera.x = 0;
	camera.y = 0;
	camera.w = w;
	camera.h = h;
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	botoes[BOTAO_STATUS].Inicializar(janela->renderer, "resources/botoes/Status.png", 50, h/10.0);
	botoes[BOTAO_INVENTARIO].Inicializar(janela->renderer, "resources/botoes/itens.png", 50, h/10.0*2.25);
	botoes[BOTAO_MENUINICIAL].Inicializar(janela->renderer, "resources/botoes/Menu Inicial.png", 50, h/10.0*5.50);
	botoes[BOTAO_SAIR].Inicializar(janela->renderer, "resources/botoes/Sair do jogo.png", 50, h/10.0*6.75);
	botoes[BOTAO_VOLTAR].Inicializar(janela->renderer, "resources/botoes/Voltar.png", 50, h/10.0*8.75);
	botoes[BOTAO_USAR].Inicializar(janela->renderer, "resources/botoes/Usar.png", w/10.0*8.25, h/10.0*8.75);
	botoes[BOTAO_USAR2].Inicializar(janela->renderer, "resources/botoes/Remover.png", w/10.0*7.0, h/10.0*8.75);
	botoes[BOTAO_DESTRUIR].Inicializar(janela->renderer, "resources/botoes/Destruir.png", w/10.0*5.0, h/10.0*8.75);
	filtro.CriaTexturaDaImagem(janela->renderer, "resources/imgs/filtro.png");
	gameover.CriaTexturaDaImagem(janela->renderer, "resources/imgs/gameover.png");
	victory.CriaTexturaDaImagem(janela->renderer, "resources/imgs/vitoria.png");
	gerenteAtor.Inicializar(janela);
	gerenteAtor.Adicionar(jogador = new Jogador(gerenteAtor));
	gerenteAtor.Adicionar(boss = new Lucifer(gerenteAtor, 1888.0, 160.0, jogador, &mapa));
	int altura, largura;
	largura = mapa.PegaDimensaoemTiles().w;
	altura = mapa.PegaDimensaoemTiles().h;
	for(int i = 0; i < largura/8; i++){
		for(int j = 0; j < 7; j++){
			gerenteAtor.Adicionar(new Armadilha(gerenteAtor, 32.0+32.0*j+256*i, (altura-7)*32.0, 0.0, ARMADILHA_ESPINHOS));
		}
		gerenteAtor.Adicionar(new Armadilha(gerenteAtor, 32.0+256.0*i, (altura-7)*32.0+48.0, 0.0, ARMADILHA_FLECHA));
		gerenteAtor.Adicionar(new Armadilha(gerenteAtor, 32.0+256.0*i, (altura-7)*32.0-32.0, 0.0, ARMADILHA_FLECHA));
		if(i%2 == 0)
			gerenteAtor.Adicionar(new Lobisomem(gerenteAtor, i*256.0+128.0, (altura/2)*32.0, jogador, &mapa));
		else
			gerenteAtor.Adicionar(new Crowley(gerenteAtor, i*256.0+128.0, (altura/2)*32.0, jogador, &mapa));
	}
	Atributos a = jogador->PegaAtributos();
	status.str("");
	status << "HP/HPMax = " << a.hpatual << "/" << a.hp
		<< "\nMP/MPMax = " << a.mpatual << "/" << a.mp
		<< "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
		<< "\nForca = " << a.forca
		<< "\nDefesa = " << a.defesa
		<< "\nMagia = " << a.magia;
	txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, w);
	skills[0].CriaTexturaDaImagem(janela->renderer, "resources/imgs/1.png");
	skills[1].CriaTexturaDaImagem(janela->renderer, "resources/imgs/2.png");
	skills[2].CriaTexturaDaImagem(janela->renderer, "resources/imgs/3.png");
	estado = ESTADO_INGAME;
	invselecionado = 0;
	janela->entrada.SetaTamanhoTexto(10);
	janela->entrada.ativaInputTexto();
}

void Ingame::Atualizar(Uint32 deltaTime){
	KB_Botao* Teclas = PegaTecla();
	M_Mouse* Mouse = PegaMouse();
	Atributos a = jogador->PegaAtributos();
	stringstream newstatus;
	SDL_Color cor = {0, 0, 0};
	Item** inventario;
	int altura, largura;
	//printf("%d\t", deltaTime);
	largura = mapa.PegaDimensaoAbsoluta().w;
	altura = mapa.PegaDimensaoAbsoluta().h;

	switch(estado)
	{
	case ESTADO_INGAME:
		camera.x = jogador->PegaBoundingBox().x - camera.w/2;
		camera.y = jogador->PegaBoundingBox().y - camera.h/2;
		if(camera.x < 0)
			camera.x = 0;
		else if(camera.x > largura-camera.w)
			camera.x = largura-camera.w;
		if(camera.y < 0)
			camera.y = 0;
		else if(camera.y > altura-camera.h)
			camera.y = altura-camera.h;

		gerenteAtor.Atualizar(deltaTime, &mapa, &camera);
		
		if(janela->entrada.pegaTexto() == "reload"){
			mapa.Carregar("teste");
			mapa.Inicializar(janela->renderer);
			janela->entrada.toggleInputTexto();
			janela->entrada.toggleInputTexto();
		} else if(janela->entrada.pegaTexto() == "godmode"){
			jogador->Godmode();
			janela->entrada.toggleInputTexto();
			janela->entrada.toggleInputTexto();
		} else if(janela->entrada.pegaTexto() == "ghost"){
			jogador->Ghost();
			janela->entrada.toggleInputTexto();
			janela->entrada.toggleInputTexto();
		} else if(janela->entrada.pegaTexto() == "aspirina"){
			jogador->PegaAtributos().hpatual = jogador->PegaAtributos().hp;
			janela->entrada.toggleInputTexto();
			janela->entrada.toggleInputTexto();
		}

		if(Teclas[KB_ESC].pressionado){
			estado = ESTADO_PAUSADO;			
			janela->entrada.toggleInputTexto();
			janela->entrada.toggleInputTexto();
		}
		if(!jogador->EstaNoJogo())
			estado = ESTADO_LOSE;
		if(!boss->EstaNoJogo())
			estado = ESTADO_WIN;
		break;
	case ESTADO_PAUSADO:
		for(int i = 0; i < BOTAO_QTD; i++)
			botoes[i].Atualizar(Mouse);				
		newstatus.str("");
		newstatus << "HP/HPMax = " << a.hpatual << "/" << a.hp
				 << "\nMP/MPMax = " << a.mpatual << "/" << a.mp
				 << "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
				 << "\nForca = " << a.forca
				 << "\nDefesa = " << a.defesa
				 << "\nMagia = " << a.magia;
		if(newstatus.str() != status.str()){
			status.str(newstatus.str());
			txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, janela->PegaPosicaoeTamanho().w);
		}
		if(Teclas[KB_ESC].pressionado || botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_INGAME;
		if(botoes[BOTAO_INVENTARIO].Pressionado()){
			estado = ESTADO_INVENTARIO;
			invselecionado = 0;
		}
		if(botoes[BOTAO_STATUS].Pressionado()){
			estado = ESTADO_STATUS;
			invselecionado = 0;
		}
	break;
	case ESTADO_STATUS:
		botoes[BOTAO_VOLTAR].Atualizar(Mouse);		
		botoes[BOTAO_USAR2].Atualizar(Mouse);
		newstatus.str("");
		newstatus << "HP/HPMax = " << a.hpatual << "/" << a.hp
				 << "\nMP/MPMax = " << a.mpatual << "/" << a.mp
				 << "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
				 << "\nForca = " << a.forca
				 << "\nDefesa = " << a.defesa
				 << "\nMagia = " << a.magia;
		if(newstatus.str() != status.str()){
			status.str(newstatus.str());
			txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, janela->PegaPosicaoeTamanho().w);
		}
		inventario = (Item**)jogador->PegaEquipamentos();
		if(inventario[EQUIP_CABECA] && Mouse->x > 600 && Mouse->x < 632 && Mouse->y > 100 && Mouse->y < 132 && Mouse->botoes[M_ESQUERDO].ativo)
			invselecionado = EQUIP_CABECA;
		if(inventario[EQUIP_ARMA] && Mouse->x > 550 && Mouse->x < 582 && Mouse->y > 150 && Mouse->y < 182 && Mouse->botoes[M_ESQUERDO].ativo)
			invselecionado = EQUIP_ARMA;
		if(inventario[EQUIP_TRONCO] && Mouse->x > 600 && Mouse->x < 632 && Mouse->y > 150 && Mouse->y < 182 && Mouse->botoes[M_ESQUERDO].ativo)
			invselecionado = EQUIP_TRONCO;
		if(inventario[EQUIP_PERNAS] && Mouse->x > 650 && Mouse->x < 682 && Mouse->y > 150 && Mouse->y < 182 && Mouse->botoes[M_ESQUERDO].ativo)
			invselecionado = EQUIP_PERNAS;
		if(inventario[EQUIP_PES] && Mouse->x > 600 && Mouse->x < 632 && Mouse->y > 200 && Mouse->y < 232 && Mouse->botoes[M_ESQUERDO].ativo)
			invselecionado = EQUIP_PES;
		if(botoes[BOTAO_USAR2].Pressionado() && inventario[invselecionado])
			inventario[invselecionado]->Usar(jogador);
		if(botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_PAUSADO;
		break;
	case ESTADO_INVENTARIO:
		inventario = jogador->PegaInventario();
		botoes[BOTAO_USAR].Atualizar(Mouse);		
		botoes[BOTAO_VOLTAR].Atualizar(Mouse);		
		botoes[BOTAO_DESTRUIR].Atualizar(Mouse);		
		newstatus.str("");
		newstatus << "HP/HPMax = " << a.hpatual << "/" << a.hp
				 << "\nMP/MPMax = " << a.mpatual << "/" << a.mp
				 << "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
				 << "\nForca = " << a.forca
				 << "\nDefesa = " << a.defesa
				 << "\nMagia = " << a.magia;
		if(newstatus.str() != status.str()){
			status.str(newstatus.str());
			txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, janela->PegaPosicaoeTamanho().w);
		}
		for(int i = 0; i < 10; i++){
			if(Mouse->x > 100 && Mouse->x < 700 && Mouse->y > 50.0+i*45.0 && Mouse->y < 90.0+i*45.0 && Mouse->botoes[M_ESQUERDO].ativo)
				invselecionado = i;
		}
		if(botoes[BOTAO_USAR].Pressionado() && inventario[invselecionado])
			inventario[invselecionado]->Usar(jogador);
		if(botoes[BOTAO_DESTRUIR].Pressionado() && inventario[invselecionado]){
			delete inventario[invselecionado];
			inventario[invselecionado] = 0;
		}
		if(botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_PAUSADO;
		break;
	case ESTADO_WIN:
	case ESTADO_LOSE:
		botoes[BOTAO_MENUINICIAL].Atualizar(Mouse);
		break;
	}
}

void Ingame::Renderizar(){
	M_Mouse* Mouse = PegaMouse();
	Atributos a = jogador->PegaAtributos();
	SDL_Rect hpbar = { 16, 16, (int)((double)a.hpatual/(double)a.hp*100.0), 16};
	SDL_Rect mpbar = { 16, 36, (int)((double)a.mpatual/(double)a.mp*100.0), 16};
	SDL_Rect selectrect;
	Item** inventario;
	mapa.Renderizar(janela->renderer, &camera);
	gerenteAtor.Renderizar(&camera);
	
	if(estado != ESTADO_INGAME)
	{
		filtro.Renderizar(janela->renderer, 0.0, 0.0);
	}
	
	switch(estado)
	{
	case ESTADO_INGAME:	
		SDL_SetRenderDrawColor(janela->renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(janela->renderer, &hpbar);
		SDL_SetRenderDrawColor(janela->renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(janela->renderer, &mpbar);
		hpbar.w = 102;
		hpbar.x = 15;
		mpbar.w = 102;
		mpbar.x = 15;
		SDL_SetRenderDrawColor(janela->renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(janela->renderer, &hpbar);
		SDL_RenderDrawRect(janela->renderer, &mpbar);
		skills[jogador->PegaSkillSelecionada()].Renderizar(janela->renderer, camera.w/2.0, camera.h-50.0, 0, 0, -M_PI/2.0);
		hpbar.x = (int)(camera.w/2.0)-1;
		hpbar.y = camera.h-51;
		hpbar.w = 34;
		hpbar.h = 34;
		SDL_RenderDrawRect(janela->renderer, &hpbar);
		break;
	case ESTADO_PAUSADO:		
		for(int i = 0; i < 5; i++)
			botoes[i].Renderizar(janela->renderer);
		break;
	case ESTADO_INVENTARIO:
		inventario = jogador->PegaInventario();
		for(int i = 0; i < 10; i++){
			if(inventario[i] != 0){
				inventario[i]->PegaIcone().Renderizar(janela->renderer, 100.0, 50.0+i*45.0);
				inventario[i]->PegaTxtNome().Renderizar(janela->renderer, 150.0, 50.0+i*45.0);
				if(i == invselecionado)
					inventario[i]->PegaTxtDesc().Renderizar(janela->renderer, (double)Mouse->x+16.0, (double)Mouse->y);
			}				
		}
		if(inventario[invselecionado]){
			botoes[BOTAO_USAR].Renderizar(janela->renderer);
			botoes[BOTAO_DESTRUIR].Renderizar(janela->renderer);
			SDL_SetRenderDrawColor(janela->renderer, 0, 0, 0, 255);
			selectrect.x = 99;
			selectrect.y = 49+invselecionado*45;
			selectrect.w = 602;
			selectrect.h = 42;
			SDL_RenderDrawRect(janela->renderer, &selectrect);
		}
		botoes[BOTAO_VOLTAR].Renderizar(janela->renderer);
		break;
	case ESTADO_STATUS:
		txtstatus.Renderizar(janela->renderer, 50.0, 50.0);
		inventario = (Item**)jogador->PegaEquipamentos();
		if(inventario[EQUIP_CABECA])
			inventario[EQUIP_CABECA]->PegaIcone().Renderizar(janela->renderer, 600.0, 100.0);
		if(inventario[EQUIP_ARMA])
			inventario[EQUIP_ARMA]->PegaIcone().Renderizar(janela->renderer, 550.0, 150.0);
		if(inventario[EQUIP_TRONCO])
			inventario[EQUIP_TRONCO]->PegaIcone().Renderizar(janela->renderer, 600.0, 150.0);
		if(inventario[EQUIP_PERNAS])
			inventario[EQUIP_PERNAS]->PegaIcone().Renderizar(janela->renderer, 650.0, 150.0);
		if(inventario[EQUIP_PES])
			inventario[EQUIP_PES]->PegaIcone().Renderizar(janela->renderer, 600.0, 200.0);
		if(inventario[invselecionado]){
			inventario[invselecionado]->PegaTxtDesc().Renderizar(janela->renderer, (double)Mouse->x+16.0, (double)Mouse->y);
			botoes[BOTAO_USAR2].Renderizar(janela->renderer);
			SDL_SetRenderDrawColor(janela->renderer, 0, 0, 0, 255);
			switch (invselecionado)
			{
			case EQUIP_CABECA:
				selectrect.x = 599;
				selectrect.y = 99;
				break;
			case EQUIP_ARMA:
				selectrect.x = 549;
				selectrect.y = 149;
				break;
			case EQUIP_TRONCO:
				selectrect.x = 599;
				selectrect.y = 149;
				break;
			case EQUIP_PERNAS:
				selectrect.x = 649;
				selectrect.y = 149;
				break;
			case EQUIP_PES:
				selectrect.x = 599;
				selectrect.y = 199;
				break;
			}
			selectrect.w = 34;
			selectrect.h = 34;
			SDL_RenderDrawRect(janela->renderer, &selectrect);
		}
		botoes[BOTAO_VOLTAR].Renderizar(janela->renderer);
		break;
	case ESTADO_LOSE:
		gameover.Renderizar(janela->renderer, (800.0-(double)gameover.PegaDimensao().w)/2.0, 50.0);
		botoes[BOTAO_MENUINICIAL].Renderizar(janela->renderer);
		break;
	case ESTADO_WIN:
		victory.Renderizar(janela->renderer, (800.0-(double)gameover.PegaDimensao().w)/2.0, 50.0);
		botoes[BOTAO_MENUINICIAL].Renderizar(janela->renderer);
		break;
	}
}

void Ingame::Finalizar(){	
	TTF_CloseFont(fonte);
}

Tela* Ingame::ProximaTela(){
	if(PegaTecla()[KB_ENCERRA].pressionado || botoes[BOTAO_SAIR].Pressionado())
		return 0;
	if(botoes[BOTAO_MENUINICIAL].Pressionado())
		return new MenuInicial();
	return this;
}