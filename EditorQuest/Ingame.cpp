#include "Ingame.h"
#include "janela.h"
#include "Jogador.h"
#include "MenuInicial.h"
#include <fstream>
#include <string>

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
	std::ofstream out;
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
	std::string buffer;
	std::ifstream in;
	in.open("teste.equest", std::ios_base::binary);
	if(in.is_open())
	{
		in.read((char*)&largura, sizeof(unsigned int));
		in.read((char*)&altura, sizeof(unsigned int));
		//in >> largura  >> altura;
		mapp = new unsigned int*[altura];
		for(unsigned int i = 0; i < altura; i++)
		{
			mapp[i] = new unsigned int[largura];
			for(unsigned int j = 0; j < largura; j++)
			{
				in.read((char*)&mapp[i][j], sizeof(unsigned int));
				//in >> mapp[i][j];
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
	TTF_Font* fonte = TTF_OpenFont("resources/fonts/pix.ttf", 32);
	SDL_Color cor = {0, 0, 0};
	sair.Inicializar(janela->renderer, "Sair", w/2.0-25, 500, fonte, cor);
	TTF_CloseFont(fonte);
	filtro.CriaTexturaDaImagem(janela->renderer, "resources/imgs/pause.png");
	gerenteAtor.Inicializar(janela);
	gerenteAtor.Adicionar(jogador = new Jogador(gerenteAtor));
	estado = ESTADO_INGAME;
}

void Ingame::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	switch(estado)
	{
	case ESTADO_INGAME:
		camera.x = jogador->PegaBoundingBox().x - camera.w/2;
		camera.y = jogador->PegaBoundingBox().y - camera.h/2;
		if(camera.x < 0) camera.x = 0;
		else if(camera.x > 32*32-camera.w) camera.x = 32*32-camera.w;
		if(camera.y < 0) camera.y = 0;
		else if(camera.y > 32*32-camera.h) camera.y = 32*32-camera.h;
		/*	
		printf("%d\t", deltaTime);
		//Se o mouse está dentro da janela
		if(((Mouse->y > 0) && (Mouse->y < camera.h) && (Mouse->x > 0) && (Mouse->x < camera.w))){
			if(Mouse->y < 100)
				camera.y-=5;
			else if(Mouse->y > camera.h-100)
				camera.y+=5;
			if(Mouse->x < 100)
				camera.x-=5;
			else if(Mouse->x > camera.w-100)
				camera.x+=5;
		}
		*/
	
		gerenteAtor.Atualizar(deltaTime, &mapa);
		if(Teclas[FW_ESC].pressionado)
			estado = ESTADO_PAUSADO;
		break;
	case ESTADO_PAUSADO:
		sair.Atualizar();
		if(Teclas[FW_ESC].pressionado)
			estado = ESTADO_INGAME;
	break;
	default:
		break;
	}
}

void Ingame::Renderizar(){
	mapa.Renderizar(janela->renderer, &camera);
	gerenteAtor.Renderizar(&camera);
	if(estado == ESTADO_PAUSADO)
	{
		filtro.Renderizar(janela->renderer, 0.0, 0.0);
		//SDL_Rect rect = {0, 0, camera.w, camera.h};
		//SDL_SetRenderDrawColor(janela->renderer, 25, 25, 75, 255);
		//SDL_RenderFillRect(janela->renderer, &rect);
	}
	switch(estado)
	{
	case ESTADO_INGAME:
		break;
	case ESTADO_PAUSADO:
		sair.Renderizar(janela->renderer);
		break;
	default:
		break;
	}
}

void Ingame::Finalizar(){
}

Tela* Ingame::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado)
		return nullptr;
	if(sair.Pressionado())
		return new MenuInicial();
	return this;
}