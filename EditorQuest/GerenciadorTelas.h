#ifndef __GERENCIADORTELAS_H__
#define __GERENCIADORTELAS_H__

class Janela;
class Tela;

class GerenciadorTelas
{
	private:
		Tela* tela;
		Janela* janela;
	public:
		GerenciadorTelas(Tela* tela, Janela* _janela);
		void Atualizar();
		void Renderizar();
		bool Acabou();
		~GerenciadorTelas();
};

#endif