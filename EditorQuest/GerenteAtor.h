#ifndef _GERENTEATOR_H_
#define _GERENTEATOR_H_

#include <vector>
#include "Janela.h"

class Ator;
class Mapa;

class GerenteAtor
{
	private:
		std::vector<Ator*> adicionados;
		std::vector<Ator*> atores;
		std::vector<Ator*> mortos;
		std::vector<Ator*> excluidos;

	public:
		Janela* janela;

		void Inicializar(Janela* _janela);
		void Adicionar(Ator* ator);
		void Atualizar(Uint32 deltaTime, Mapa* mapa, SDL_Rect* camera);
		void Renderizar(SDL_Rect* camera);

		Ator* PegaAtormaisProximo(double x, double y);
		Ator* PegaAtormaisProximo(double x, double y, unsigned int tipo);
		//Ator* PegaPrimeiroAtornaLista(unsigned int tipo = ATOR_JOGADOR);

		~GerenteAtor();
};

#endif