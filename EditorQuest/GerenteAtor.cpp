#include "GerenteAtor.h"
#include "Ator.h"

using namespace std;

GerenteAtor::GerenteAtor(Janela& _janela)
	:janela(_janela)
{
}

void GerenteAtor::Adicionar(Ator* ator)
{
	adicionados.push_back(ator);
	ator->Inicializar();
}

void GerenteAtor::Atualizar()
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
		ator->Atualizar();
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
}


void GerenteAtor::Renderizar()
{
	if(!atores.empty())
		for (Ator* ator : atores) 
		{
			ator->Renderizar();
		}
}

GerenteAtor::~GerenteAtor()
{
	for (Ator* ator : atores) 
	{
		delete ator;
	}
}
