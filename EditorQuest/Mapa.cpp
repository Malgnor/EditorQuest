#include "Mapa.h"
#include <vector>

using namespace std;

Mapa::Mapa()
{
	mapa = 0;
	altura = largura = qtdColisao = 0;
	colisao = 0;
}

Mapa::~Mapa()
{
	for(unsigned int i = 0; i < altura; i++)
	{
		delete[] mapa[i];
		mapa[i] = 0;
	}
	delete[] mapa;
	mapa = 0;
	delete[] colisao;
	colisao = 0;
	largura = altura = qtdColisao = 0;
}

void Mapa::Inicializar(SDL_Renderer* renderer, unsigned int **_mapa, unsigned int _altura, unsigned int _largura)
{
	mapa = _mapa;
	largura = _largura;
	altura = _altura;
	sprite.CriaTexturaMapa(renderer, mapa, largura, altura);

	for(unsigned int i = 0; i < altura; i++)
	{
		for(unsigned int j = 0; j < largura; j++)
		{
			if(mapa[i][j] == 1 || mapa[i][j] == 3 || mapa[i][j] == 4)
			{
				qtdColisao++;
			}
		}
	}

	colisao = new cMap[qtdColisao];
	unsigned int qtdc = 0;
	for(unsigned int i = 0; i < altura; i++)
	{
		for(unsigned int j = 0; j < largura; j++)
		{
			if(mapa[i][j] == 1 || mapa[i][j] == 3 || mapa[i][j] == 4)
			{
				colisao[qtdc].id = mapa[i][j];
				colisao[qtdc].rect.x = j*32;
				colisao[qtdc].rect.y = i*32;
				colisao[qtdc++].rect.w = colisao[qtdc].rect.h = 32;
			}
		}
	}

	/*printf("%d\t%d\n", qtdc, qtdColisao); // 139
	unsigned int qtdo = 0;
	vector<cMap> colisaoo;
	vector<vector<cMap>> vect;
	for(unsigned int i = 0; i < qtdColisao - 1; i++)
	{
	}
	*/

}

void Mapa::Renderizar(SDL_Renderer* renderer, SDL_Rect* camera)
{
	sprite.Renderizar(renderer, (double)-camera->x, (double)-camera->y);
}

SDL_Rect Mapa::PegaDimensaoemTiles()
{
	SDL_Rect ret = {0, 0, largura, altura};
	return ret;
}

SDL_Rect Mapa::PegaDimensaoAbsoluta()
{
	return sprite.PegaDimensao();
}

cMap* Mapa::PegaColisao()
{
	return colisao;
}
unsigned int Mapa::PegaQtdColisao(){
	return qtdColisao;
}
