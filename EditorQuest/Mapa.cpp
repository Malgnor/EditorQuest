#include "Mapa.h"
#include <vector>
#include <fstream>


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

void Mapa::Inicializar(SDL_Renderer* renderer)
{
	if(colisao){
		delete[] colisao;
		colisao = 0;
	}

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

void Mapa::Novo(unsigned int _largura, unsigned int _altura){
	altura = _altura;
	largura = _largura;

	if(mapa){
		for(unsigned int i = 0; i < altura; i++)
		{

			delete[] mapa[i];
			mapa[i] = 0;
		}
		delete[] mapa;
		mapa = 0;	
	}

	mapa = new unsigned int*[altura];
	for(unsigned int i = 0; i < altura; i++)
	{
		mapa[i] = new unsigned int[largura];
		for(unsigned int j = 0; j < largura; j++)
		{
			mapa[i][j] = 0;
		}
	}
}

void Mapa::Renderizar(SDL_Renderer* renderer, SDL_Rect* camera)
{
	if(camera)
		sprite.Renderizar(renderer, (double)-camera->x, (double)-camera->y);
	else
		sprite.Renderizar(renderer, 0.0, 0.0);
}

bool Mapa::Salvar(std::string nome)
{
	ofstream out;
	out.open("resources/maps/"+nome+"/map.equest", std::ios_base::binary);
	if(out.is_open())
	{
		out.write((char*)&largura,sizeof(unsigned int));
		out.write((char*)&altura,sizeof(unsigned int));
		for(unsigned int i = 0; i < altura; i++)
		{
			for(unsigned int j = 0; j < largura; j++)
			{
				out.write((char*)&mapa[i][j],sizeof(unsigned int));
			}
		}
		out.close();
		return true;
	}
	out.close();
	return false;
}

bool Mapa::Carregar(std::string nome)
{
	ifstream in;
	in.open("resources/maps/"+nome+"/map.equest", std::ios_base::binary);
	if(in.is_open())
	{
		in.read((char*)&largura, sizeof(unsigned int));
		in.read((char*)&altura, sizeof(unsigned int));
		mapa = new unsigned int*[altura];
		for(unsigned int i = 0; i < altura; i++)
		{
			mapa[i] = new unsigned int[largura];
			for(unsigned int j = 0; j < largura; j++)
			{
				in.read((char*)&mapa[i][j], sizeof(unsigned int));
			}
		}
		in.close();
		return true;
	}
	in.close();
	return false;
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
