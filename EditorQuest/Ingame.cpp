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
		{ 0, 1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 4, 2, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 5, 2, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 6, 2, 6, 6, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 7, 2, 7, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
		{ 0, 1, 2, 2, 2, 2, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
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
	altura = largura = 32;
	std::ofstream out;
	out.open("teste.equest", std::ios_base::binary);
	if(out.is_open())
	{
		out << largura << " " << altura << std::endl;
		for(unsigned int i = 0; i < altura; i++)
		{
			for(unsigned int j = 0; j < largura; j++)
			{
				out << map[i][j] << " ";
			}
			out << std::endl;
		}
		out.close();
	}
	*/
	unsigned int** map = 0;
	unsigned int altura, largura;
	std::string buffer;
	std::ifstream in;
	in.open("teste.equest", std::ios_base::binary);
	if(in.is_open())
	{
		in >> largura  >> altura;
		map = new unsigned int*[altura];
		for(unsigned int i = 0; i < altura; i++)
		{
			map[i] = new unsigned int[largura];
			for(unsigned int j = 0; j < largura; j++)
			{
				in >> map[i][j];
			}
			in;
		}
		in.close();
	}
	mapa.Inicializar(janela->renderer, map, altura, largura);	
	int w, h;
	janela->PegaTamanho(w, h);
	camera.x = 0;
	camera.y = 0;
	camera.w = w;
	camera.h = h;
	gerenteAtor.Inicializar(janela);
	gerenteAtor.Adicionar(jogador = new Jogador(gerenteAtor));
}

void Ingame::Atualizar(Uint32 deltaTime){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	camera.x = jogador->PegaBoundingBox().x - camera.w/2;
	camera.y = jogador->PegaBoundingBox().y - camera.h/2;
	if(camera.x < 0) camera.x = 0;
	else if(camera.x > 32*32-camera.w) camera.x = 32*32-camera.w;
	if(camera.y < 0) camera.y = 0;
	else if(camera.y > 32*32-camera.h) camera.y = 32*32-camera.h;
	/*	
	//printf("%d\t", deltaTime);
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
}

void Ingame::Renderizar(){
	mapa.Renderizar(janela->renderer, &camera);
	gerenteAtor.Renderizar(&camera);
}

void Ingame::Finalizar(){
}

Tela* Ingame::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado)
		return nullptr;
	if(PegaTecla()[FW_ESC].pressionado)
		return new MenuInicial();
	return this;
}