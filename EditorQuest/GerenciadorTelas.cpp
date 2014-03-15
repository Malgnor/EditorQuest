#include "GerenciadorTelas.h"
#include "Janela.h"
#include "Tela.h"

GerenciadorTelas::GerenciadorTelas(Tela* _tela, Janela* _janela)
	:tela(_tela),janela(_janela)
{
	tela->Inicializar(janela);
}

void GerenciadorTelas::Atualizar()
{
	Tela* proximaTela = tela->ProximaTela();

	//se mandar tela nula termina o programa
	if (proximaTela == nullptr) 
	{
		tela->Finalizar();
		delete tela;
		tela = nullptr;
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
		tela->Atualizar();
	}
}

void GerenciadorTelas::Renderizar()
{
	if (tela != nullptr)
		tela->Renderizar();
}

bool GerenciadorTelas::Acabou()
{
	return tela == nullptr;
}

GerenciadorTelas::~GerenciadorTelas()
{
	if(tela)
		tela->Finalizar();
	delete tela;
	tela = 0;
}