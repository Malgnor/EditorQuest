#include "MenuInicial.h"
#include "Janela.h"

void MenuInicial::Inicializar(Janela* _janela){
	x1 = y1 = 100.0;
	x2 = y2 = 200.0;
	ind1 = ind2 = 0;
	janela = _janela;
	janela->SetaTitulo("Editor's Quest - Menu Inicial");
	janela->SetaTamanho(800, 600);
	janela->SetaPosicao(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	janela->SetaCorFundo(255, 255, 255);
	janela->Mostrar();
	t.CriaTexturaDaImagem(janela->PegaRenderer(), "resources/imgs/torre.png", 32);
	t_.CriaTexturaDaImagemC(janela->PegaRenderer(), "resources/imgs/torre_.png", 32, 0, 0x00, 0xFF, 0x00);
}

void MenuInicial::Atualizar(){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	if(Teclas[FW_1].pressionado)
		janela->SetaCorFundo(255, 255, 255);
	if(Teclas[FW_2].pressionado)
		janela->SetaCorFundo(0, 255, 255);
	if(Teclas[FW_3].pressionado)
		janela->SetaCorFundo(255, 0, 255);
	if(Teclas[FW_4].pressionado)
		janela->SetaCorFundo(255, 255, 0);
	if(Teclas[FW_W].ativo)
		y1--;
	else if(Teclas[FW_S].ativo)
		y1++;
	if(Teclas[FW_CIMA].ativo)
		y2--;
	else if(Teclas[FW_BAIXO].ativo)
		y2++;
	if(Teclas[FW_D].ativo)
		x1++;
	else if(Teclas[FW_A].ativo)
		x1--;
	if(Teclas[FW_DIREITA].ativo)
		x2++;
	else if(Teclas[FW_ESQUERDA].ativo)
		x2--;
	if(Mouse->botoes[FW_MESQUERDO].pressionado)
		ind1++;
	if(Mouse->botoes[FW_MDIREITO].pressionado)
		ind2++;
}

void MenuInicial::Renderizar(){
	t.Renderizar(janela->PegaRenderer(), x1, y1, ind1%4);
	t_.Renderizar(janela->PegaRenderer(), x2, y2, ind2%4);
}

void MenuInicial::Finalizar(){
}

Tela* MenuInicial::ProximaTela(){
	if(PegaTecla()[FW_ENCERRA].pressionado)
		return nullptr;
	return this;
}
	
MenuInicial::~MenuInicial(){
}