#include "GerenciadorTelas.h"
#include "Janela.h"
#include "Tela.h"

GerenciadorTelas::GerenciadorTelas(Tela* _tela, Janela* _janela)
	:tela(_tela),janela(_janela)
{
	tela->Inicializar(janela);
}

void GerenciadorTelas::Atualizar(Uint32 deltaTime)
{
	Tela* proximaTela = tela->ProximaTela();

	//se mandar tela nula termina o programa
	if (proximaTela == 0) 
	{
		tela->Finalizar();
		delete tela;
		tela = 0;
	} 
	else
	{
		//se nao enviar uma tela igual a atual, termina essa e inicia a outra
		if (proximaTela != tela) 
		{
			tela->Finalizar();
			delete tela;
			tela = proximaTela;
			tela->Inicializar(janela);
		}

		//caso seja a mesma apenas atualiza
		tela->Atualizar(deltaTime);
	}
}

void GerenciadorTelas::Renderizar()
{
	if (tela != 0)
		tela->Renderizar();
}

bool GerenciadorTelas::Acabou()
{
	return tela == 0;
}

GerenciadorTelas::~GerenciadorTelas()
{
	if(tela != 0)
		tela->Finalizar();
	delete tela;
	tela = 0;
}