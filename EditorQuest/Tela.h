#ifndef _TELA_H_
#define _TELA_H_

class Janela;

#define PegaTecla() janela->entrada.pegaTecla()
#define PegaMouse() janela->entrada.pegaMouse()

class Tela
{
protected:
	Janela* janela;

public:
	virtual void Inicializar(Janela* _janela) = 0;
	virtual void Atualizar() = 0;
	virtual void Renderizar() = 0;
	virtual void Finalizar() = 0;

	virtual Tela* ProximaTela() = 0;

	virtual ~Tela() {}
};
#endif
