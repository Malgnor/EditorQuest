#include "Editor.h"
#include "Janela.h"



void Editor::Inicializar(Janela* _janela)
{
	janela = _janela;
	janela->SetaTitulo("Walachia - Editor");
	titulo.CriaTexturaDaImagem(janela->renderer, "resources/imgs/Walachia.png");
}

void Editor::Atualizar(Uint32 deltaTime)
{
}

void Editor::Renderizar()
{
	titulo.Renderizar(janela->renderer, ((800-(double)titulo.PegaDimensao().w)/2.0), 25.0);
}

void Editor::Finalizar()
{
}

Tela* Editor::ProximaTela()
{
	if(PegaTecla()[KB_ENCERRA].pressionado || PegaTecla()[KB_ESC].pressionado)
		return 0;
	return this;
}
	
Editor::~Editor()
{
}