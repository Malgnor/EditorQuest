#pragma once

#include <vector>
#include "Janela.h"

class Ator;

class GerenteAtor
{
	private:
		std::vector<Ator*> adicionados;
		std::vector<Ator*> atores;
		std::vector<Ator*> mortos;
		std::vector<Ator*> excluidos;

	public:
		Janela& janela;

		GerenteAtor(Janela& _janela);
		void Adicionar(Ator* ator);
		void Atualizar();
		void Renderizar();
		~GerenteAtor();
};

