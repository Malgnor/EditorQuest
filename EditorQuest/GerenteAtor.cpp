#include "GerenteAtor.h"
#include "Ator.h"
#include "Mapa.h"

using namespace std;

void GerenteAtor::Inicializar(Janela* _janela){
	janela = _janela;
}

void GerenteAtor::Adicionar(Ator* ator)
{
	adicionados.push_back(ator);
	ator->Inicializar();
}

void GerenteAtor::Atualizar(Uint32 deltaTime, Mapa* mapa)
{
	//1. Excluir os atores na lista excluido
	//para libera-la. 
	for (Ator* ator : excluidos)
	{
		delete ator;
	}
	excluidos.clear();

	//2. Mover os mortos para a lista de excluídos
	//para liberar a lista de mortos.
	for (Ator* ator : mortos)
	{
		excluidos.push_back(ator);
	}
	mortos.clear();

	//Adiciona todos os atores que foram adicionados no loop anterior
	//e coloca-los na lista de atores.
	for (Ator* ator : adicionados)
	{
		atores.push_back(ator);
	}
	adicionados.clear();

	//3. Atualiza a lógica do ator e, caso queira sair do jogo
	//finaliza e move para a lista de mortos. Caso contrário,
	//mantém o ator numa lista de vivos.
	if(atores.empty())
		return;
	std::vector<Ator*> vivos;

	for (Ator* ator : atores) 
	{
		ator->Atualizar(deltaTime);
		if (ator->EstaNoJogo())
		{
			vivos.push_back(ator);
		}
		else
		{
			ator->Finalizar();
			mortos.push_back(ator);
		}
	}

	//Substitui a lista de atores pela de vivos.
	swap(atores, vivos);

	//Checa colisão com o mapa
	if(atores.size() < 1)
		return;
	if(mapa != 0){
		SDL_Rect rcolisao;
		cMap* tiles = mapa->PegaColisao();
		for(Ator* ator : atores)
		{
			for(unsigned int i = 0; i < mapa->PegaQtdColisao(); i++){
				if(SDL_IntersectRect(&ator->PegaBoundingBox(), &tiles[i].rect, &rcolisao) == SDL_TRUE)
				{
					ator->ColidiuMapa(&tiles[i], &rcolisao);
				}
			}
		}
	}

	//Checa colisão entre atores
	if(atores.size() < 2)
		return;
	for(unsigned int i = 0; i < atores.size() - 1; i++){
		for(unsigned int j = i + 1; j < atores.size(); j++){
			if(SDL_IntersectRect(&atores[i]->PegaBoundingBox(), &atores[j]->PegaBoundingBox(), 0) == SDL_TRUE){
				atores[i]->Colidiu(atores[j]);
				atores[j]->Colidiu(atores[i]);
			}
		}
	}
}


void GerenteAtor::Renderizar(SDL_Rect* camera)
{
	if(!atores.empty())
		for (Ator* ator : atores) 
		{
			ator->Renderizar(camera);
		}
}

GerenteAtor::~GerenteAtor()
{
	for (Ator* ator : atores) 
	{
		delete ator;
	}
}
