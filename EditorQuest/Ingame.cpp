#include "Ingame.h"
#include "janela.h"
#include "MenuInicial.h"
#include <fstream>
#include <iostream>

using namespace std;

void Ingame::Inicializar(Janela* _janela){
	janela = _janela;
	janela->SetaTitulo("Editor's Quest - Ingame");
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
	altura = largura = 32;
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

	unsigned int altura, largura;
	unsigned int** mapp = 0;
	string buffer;
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
	int w, h;
	janela->PegaTamanho(w, h);
	camera.x = 0;
	camera.y = 0;
	camera.w = w;
	camera.h = h;
	fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	botoes[BOTAO_STATUS].Inicializar(janela->renderer, "Status", 50, 75, fonte, cor);
	botoes[BOTAO_INVENTARIO].Inicializar(janela->renderer, "Inventario", 50, 175, fonte, cor);
	botoes[BOTAO_MENUINICIAL].Inicializar(janela->renderer, "Menu Inicial", 50, 375, fonte, cor);
	botoes[BOTAO_SAIR].Inicializar(janela->renderer, "Sair do jogo", 50, 450, fonte, cor);
	botoes[BOTAO_VOLTAR].Inicializar(janela->renderer, "Voltar", 50, 525, fonte, cor);
	filtro.CriaTexturaDaImagem(janela->renderer, "resources/imgs/pause.png");
	gerenteAtor.Inicializar(janela);
	gerenteAtor.Adicionar(jogador = new Jogador(gerenteAtor));
	Atributos a = jogador->PegaAtributos();
	status.str("");
	status << "HP/HPMax = " << a.hpatual << "/" << a.hp
		<< "\nMP/MPMax = " << a.mpatual << "/" << a.mp
		<< "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
		<< "\nForca = " << a.forca
		<< "\nDefesa = " << a.defesa
		<< "\nMagia = " << a.magia;
	txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, 600);
	estado = ESTADO_INGAME;
	invselecionado = 0;	
}

void Ingame::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	//printf("%d\t", deltaTime);
	Atributos a = jogador->PegaAtributos();
	stringstream newstatus;
	SDL_Color cor = {0, 0, 0};
	switch(estado)
	{
	case ESTADO_INGAME:
		camera.x = jogador->PegaBoundingBox().x - camera.w/2;
		camera.y = jogador->PegaBoundingBox().y - camera.h/2;
		if(camera.x < 0) camera.x = 0;
		else if(camera.x > 32*32-camera.w) camera.x = 32*32-camera.w;
		if(camera.y < 0) camera.y = 0;
		else if(camera.y > 32*32-camera.h) camera.y = 32*32-camera.h;
		gerenteAtor.Atualizar(deltaTime, &mapa, &camera);
		if(Teclas[FW_ESC].pressionado)
			estado = ESTADO_PAUSADO;
		break;
	case ESTADO_PAUSADO:
		for(int i = 0; i < 5; i++)
			botoes[i].Atualizar();
		if(Teclas[FW_ESC].pressionado || botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_INGAME;
		if(botoes[BOTAO_INVENTARIO].Pressionado()){
			estado = ESTADO_INVENTARIO;
			invselecionado = 0;
		}
		if(botoes[BOTAO_STATUS].Pressionado())
			estado = ESTADO_STATUS;
	break;
	case ESTADO_STATUS:
		botoes[BOTAO_VOLTAR].Atualizar();		
		newstatus.str("");
		newstatus << "HP/HPMax = " << a.hpatual << "/" << a.hp
				 << "\nMP/MPMax = " << a.mpatual << "/" << a.mp
				 << "\nHPRegen/MPRegen = " << a.hpregen << "/" << a.mpregen 
				 << "\nForca = " << a.forca
				 << "\nDefesa = " << a.defesa
				 << "\nMagia = " << a.magia;
		if(newstatus.str() != status.str()){
			status.str(newstatus.str());
			txtstatus.CriaTexturaDoTextoC(janela->renderer, status.str().c_str(), fonte, cor, 600);
		}
		if(botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_INGAME;
		break;
	case ESTADO_INVENTARIO:
		botoes[BOTAO_VOLTAR].Atualizar();
		for(int i = 0; i < 10; i++){
			if(Mouse->x > 100 && Mouse->x < 700 && Mouse->y > 50.0+i*45.0 && Mouse->y < 90.0+i*45.0)
				invselecionado = i;
		}
		if(botoes[BOTAO_VOLTAR].Pressionado())
			estado = ESTADO_INGAME;
		break;
	default:
		break;
	}
}

void Ingame::Renderizar(){
	mapa.Renderizar(janela->renderer, &camera);
	gerenteAtor.Renderizar(&camera);
	Atributos a = jogador->PegaAtributos();
	SDL_Rect hpbar = { 16, 16, (int)((double)a.hpatual/(double)a.hp*100.0), 16};
	SDL_Rect mpbar = { 16, 36, (int)((double)a.mpatual/(double)a.mp*100.0), 16};
	SDL_SetRenderDrawColor(janela->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(janela->renderer, &hpbar);
	SDL_SetRenderDrawColor(janela->renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(janela->renderer, &mpbar);
	hpbar.w = 101;
	hpbar.x = 15;
	mpbar.w = 101;
	mpbar.x = 15;
	SDL_SetRenderDrawColor(janela->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(janela->renderer, &hpbar);
	SDL_RenderDrawRect(janela->renderer, &mpbar);
	if(estado != ESTADO_INGAME)
	{
		//filtro.Renderizar(janela->renderer, 0.0, 0.0);
		SDL_SetRenderDrawColor(janela->renderer, 255, 255, 255, 255);
		SDL_Rect rect = {0, 0, 800, 600};
		SDL_RenderFillRect(janela->renderer, &rect);
	}
	
	Item** inventario;
	switch(estado)
	{
	case ESTADO_INGAME:
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
					inventario[i]->PegaTxtDesc().Renderizar(janela->renderer, 225.0, 525.0);
			}				
		}
		botoes[BOTAO_VOLTAR].Renderizar(janela->renderer);
		break;
	case ESTADO_STATUS:
		txtstatus.Renderizar(janela->renderer, 50.0, 50.0);
		inventario = jogador->PegaEquipamentos();
		if(inventario[EQUIP_CABECA])
			inventario[EQUIP_CABECA]->PegaIcone().Renderizar(janela->renderer, 600.0, 100.0);
		if(inventario[EQUIP_ARMA])
			inventario[EQUIP_ARMA]->PegaIcone().Renderizar(janela->renderer, 550.0, 150.0);
		if(inventario[EQUIP_TRONCO])
			inventario[EQUIP_TRONCO]->PegaIcone().Renderizar(janela->renderer, 600.0, 150.0);
		if(inventario[EQUIP_MAOS])
			inventario[EQUIP_MAOS]->PegaIcone().Renderizar(janela->renderer, 650.0, 150.0);
		if(inventario[EQUIP_PES])
			inventario[EQUIP_PES]->PegaIcone().Renderizar(janela->renderer, 600.0, 200.0);
		botoes[BOTAO_VOLTAR].Renderizar(janela->renderer);
		break;
	default:
		break;
	}
}

void Ingame::Finalizar(){	
	TTF_CloseFont(fonte);
}

Tela* Ingame::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado || botoes[BOTAO_SAIR].Pressionado())
		return 0;
	if(botoes[BOTAO_MENUINICIAL].Pressionado() || !jogador->EstaNoJogo())
		return new MenuInicial();
	return this;
}