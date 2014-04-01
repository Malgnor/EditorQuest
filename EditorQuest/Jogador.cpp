#include "Jogador.h"
#include "Mapa.h"
#include "GerenteAtor.h"
#include "SDL.h"
#include "EnergyBall.h"
#include "Explosion.h"
#include "Slash.h"

Jogador::Jogador(GerenteAtor& _gerente) : Ator(_gerente)
{

}

Item** Jogador::PegaInventario(){
	return inventario;
}

Item** Jogador::PegaEquipamentos(){
	return equipamentos;
}

Atributos& Jogador::PegaAtributos(){
	return atributos;
}

SDL_Rect Jogador::PegaBoundingBox(){
	SDL_Rect ret = sprite.PegaDimensao();
	ret.x = (int)x;
	ret.y = (int)y;
	return ret;
}

unsigned int Jogador::PegaTipo(){
	return ATOR_JOGADOR;
}
	
bool Jogador::EstaNoJogo(){
	return atributos.hpatual > 0;
}

void Jogador::Colidiu(Ator* ator){

}

void Jogador::ColidiuMapa(cMap* tile, SDL_Rect* colisao){
	double dx,dy;
	switch (tile->id)
	{
	case 1:
		if(colisao->w > colisao->h)
		{
			dy = (double)(y-tile->rect.y);
			if( dy > 0)
			{
				y += colisao->h;
			}
			else
			{
				y -= colisao->h;
			}
		}
		else
		{			
			dx = (double)(x-tile->rect.x);
			if( dx > 0)
			{
				x += colisao->w;
			}
			else
			{
				x -= colisao->w;
			}
		}
		indice = 1;
		break;
	case 3:
		indice = 2;
		break;
	case 4:
		indice = 3;
		break;
	default:
		break;
	}
}

void Jogador::Inicializar(){
	sprite.CriaTexturaDaImagem(gerente.janela->renderer, "resources/imgs/torre.png", 32);
	x = 400.0;
	y = 300.0;
	direcao = 0.0;
	indice = skill = 0;
	atributos.hpatual = atributos.hp = 100;
	atributos.hpregen = 1;
	atributos.mpatual = atributos.mp = 100;
	atributos.mpregen = 2;
	atributos.forca = 5;
	atributos.defesa = 5;
	atributos.magia = 5;
	time = 0;
	for(int i = 0; i < 10; i++)
		inventario[i] = 0;
	for(int i = 0; i < 5; i++)
		equipamentos[i] = 0;
	inventario[2] = new Item(gerente.janela->renderer, "Item 0", "Descricao 0", "resources/imgs/botao.png", atributos);
	inventario[0] = new Item(gerente.janela->renderer, "Item 1", "Descricao 1", "resources/imgs/energyball.png", atributos);
	inventario[5] = new Item(gerente.janela->renderer, "Item 2", "Descricao 2", "resources/imgs/botaop.png", atributos);
}

void Jogador::Atualizar(Uint32 deltaTime, SDL_Rect* camera){
	FW_Botao* Teclas = PegaTecla();
	FW_Mouse* Mouse = PegaMouse();
	Atributos novos = {100, atributos.hpatual, 1, 100, atributos.mpatual, 2, 5, 5, 5};
	atributos = novos;
	for(int i = 0; i < 5; i++){
		if(equipamentos[i]){
			Atributos a = equipamentos[i]->PegaAtributos();
			atributos.hp += a.hp;
			atributos.hpregen += a.hpregen;
			atributos.mp += a.mp;
			atributos.mpregen += a.mpregen;
			atributos.forca += a.forca;
			atributos.defesa += a.defesa;
			atributos.magia += a.magia;
		}
	}
	time += deltaTime;
	if(time >= 1000){
		time -= 1000;
		atributos.hpatual += atributos.hpregen;
		atributos.mpatual += atributos.mpregen;
		if(atributos.hpatual > atributos.hp)
			atributos.hpatual = atributos.hp;
		if(atributos.mpatual > atributos.mp)
			atributos.mpatual = atributos.mp;
	}
	// SEG = 1000.0
	if(Teclas[FW_CIMA].ativo)
		atributos.hpatual++;
	if(Teclas[FW_BAIXO].ativo)
		atributos.hpatual--;
	if(Teclas[FW_DIREITA].ativo)
		atributos.mpatual++;
	if(Teclas[FW_ESQUERDA].ativo)
		atributos.mpatual--;
	if(Teclas[FW_1].pressionado)
		if(!equipamentos[EQUIP_ARMA])
			equipamentos[EQUIP_ARMA] = new Item(gerente.janela->renderer, "Arma", "Uma arma", "resources/imgs/A.png", novos);
	if(Teclas[FW_2].pressionado)
		if(!equipamentos[EQUIP_CABECA])
			equipamentos[EQUIP_CABECA] = new Item(gerente.janela->renderer, "Capacete", "Um capacete", "resources/imgs/C.png", novos);
	if(Teclas[FW_3].pressionado)
		if(!equipamentos[EQUIP_TRONCO])
			equipamentos[EQUIP_TRONCO] = new Item(gerente.janela->renderer, "Peitoral", "Um peitoral", "resources/imgs/T.png", novos);
	if(Teclas[FW_4].pressionado)
		if(!equipamentos[EQUIP_MAOS])
			equipamentos[EQUIP_MAOS] = new Item(gerente.janela->renderer, "Luvas", "Um par de luvas", "resources/imgs/M.png", novos);
	if(Teclas[FW_5].pressionado)
		if(!equipamentos[EQUIP_PES])
			equipamentos[EQUIP_PES] = new Item(gerente.janela->renderer, "Sapatos", "Um Par de sapatos", "resources/imgs/P.png", novos);
	if(Teclas[FW_W].ativo)
		y-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_S].ativo)
		y+=(300.0/SEG*deltaTime);
	if(Teclas[FW_A].ativo)
		x-=(300.0/SEG*deltaTime);
	else if(Teclas[FW_D].ativo)
		x+=(300.0/SEG*deltaTime);
	direcao = atan2(Mouse->y-(y-(double)camera->y)-16,Mouse->x-(x-(double)camera->x)-16)*180.0/M_PI;
	if(Mouse->wy){
		skill = (++skill)%3;
		printf("%d\n", skill);
	}
	if(Mouse->botoes[FW_MESQUERDO].pressionado){
		switch (skill)
		{
		case 0:
			gerente.Adicionar(new Slash(gerente, x, y, direcao));
			break;
		case 1:
			gerente.Adicionar(new EnergyBall(gerente, x, y, direcao));
			break;
		case 2:
			gerente.Adicionar(new Explosion(gerente, Mouse->x-(double)camera->x, Mouse->y-(double)camera->y, direcao));
			break;
		default:
			gerente.Adicionar(new Slash(gerente, x, y, direcao));
			break;
		}
	}
	//printf("%f %d %d\n", direcao, Mouse->x, Mouse->y);
	indice = 0;
}

void Jogador::Renderizar(SDL_Rect* camera){
	sprite.Renderizar(gerente.janela->renderer, x-(double)camera->x, y-(double)camera->y, indice, 0, direcao);
}

void Jogador::Finalizar(){	
	for(int i = 0; i < 10; i++){
		delete inventario[i];
		inventario[i] = 0;
	}
	for(int i = 0; i < 5; i++){
		delete equipamentos[i];
		equipamentos[i] = 0;
	}
}