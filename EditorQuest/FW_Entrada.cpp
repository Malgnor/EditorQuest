#include "FW_Entrada.h"

FW_Entrada::FW_Entrada(){
	for(int i=0; i<FW_MAX_TECLAS; i++){
        tecla[i].pressionado = false;
        tecla[i].liberado = false;
        tecla[i].ativo = false;
        tecla[i].repeticao = 0;
	}
    for(int i=0; i<3; i++){
        mouse.botoes[i].pressionado = false;
        mouse.botoes[i].liberado = false;
        mouse.botoes[i].ativo = false;
        mouse.botoes[i].repeticao = 0;
	}
	mouse.wx = mouse.wy = mouse.x = mouse.y = 0;
}

//funções de retorno de entrada, mouse e teclado
FW_Botao* FW_Entrada::pegaTecla()
{
	return tecla;
}

FW_Mouse* FW_Entrada::pegaMouse()
{
	return &mouse;
}

//funções para atualizar os estados do input
void FW_Entrada::processaTecla(FW_Botao* tecla,SDL_Event& event)
{
	switch(event.type)
    {
    case SDL_KEYDOWN:
        tecla->pressionado = true;
        tecla->liberado = false;
        tecla->ativo = true;
		tecla->repeticao = event.key.repeat;
        break;
    case SDL_KEYUP:
        tecla->ativo = false;
        tecla->liberado = true;
        tecla->pressionado = false;
		tecla->repeticao = 0;
        break;
    }

}

void FW_Entrada::reseta(){
	// Remove o pressionamento das teclas do passo anterior
    // Remove o liberamento das teclas do passo anterior
    for(int i=0;i<FW_MAX_TECLAS;i++){
        tecla[i].pressionado = false;
        tecla[i].liberado= false;
	}
    // Remove o pressionamento do mouse do passo anterior
    // Remove o liberamento do mouse do passo anterior
    for(int i=0;i<3;i++){
        mouse.botoes[i].pressionado = false;
        mouse.botoes[i].liberado = false;
	}
	mouse.wx = mouse.wy = 0;
}

void FW_Entrada::atualiza(SDL_Event& event)
{	
	// Trata de acordo com o tipo de evento
	switch( event.type )
	{
		case SDL_QUIT:
			tecla[FW_ENCERRA].pressionado = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					processaTecla(&tecla[FW_CIMA],event);
					break;
				case SDLK_RIGHT:
					processaTecla(&tecla[FW_DIREITA],event);
					break;
				case SDLK_DOWN:
					processaTecla(&tecla[FW_BAIXO],event);
					break;
				case SDLK_LEFT:
					processaTecla(&tecla[FW_ESQUERDA],event);
					break;
				case SDLK_z:
					processaTecla(&tecla[FW_Z],event);
					break;
				case SDLK_x:
					processaTecla(&tecla[FW_X],event);
					break;
				case SDLK_c:
					processaTecla(&tecla[FW_C],event);
					break;
				case SDLK_a:
					processaTecla(&tecla[FW_A],event);
					break;
				case SDLK_s:
					processaTecla(&tecla[FW_S],event);
					break;
				case SDLK_d:
					processaTecla(&tecla[FW_D],event);
					break;
				case SDLK_w:
					processaTecla(&tecla[FW_W],event);
					break;
				case SDLK_SPACE:
					processaTecla(&tecla[FW_ESPACO],event);
					break;
				case SDLK_LCTRL:
					processaTecla(&tecla[FW_CONTROL],event);
					break;
				case SDLK_RETURN:
					processaTecla(&tecla[FW_ENTER],event);
					break;
				case SDLK_ESCAPE:
					processaTecla(&tecla[FW_ESC],event);
					break;
				case SDLK_0:
					processaTecla(&tecla[FW_0],event);
					break;
				case SDLK_1:
					processaTecla(&tecla[FW_1],event);
					break;
				case SDLK_2:
					processaTecla(&tecla[FW_2],event);
					break;
				case SDLK_3:
					processaTecla(&tecla[FW_3],event);
					break;
				case SDLK_4:
					processaTecla(&tecla[FW_4],event);
					break;
				case SDLK_5:
					processaTecla(&tecla[FW_5],event);
					break;
				case SDLK_6:
					processaTecla(&tecla[FW_6],event);
					break;
				case SDLK_7:
					processaTecla(&tecla[FW_7],event);
					break;
				case SDLK_8:
					processaTecla(&tecla[FW_8],event);
					break;
				case SDLK_9:
					processaTecla(&tecla[FW_9],event);
					break;
			}
			break; //break dos eventos de tipo teclado
				
		case SDL_MOUSEMOTION:
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			break;// break da posição do mouse

		case SDL_MOUSEWHEEL:
			mouse.wx = event.wheel.x;
			mouse.wy = event.wheel.y;
			break;// break da posição do mouse

		case SDL_MOUSEBUTTONDOWN:
			mouse.x=event.button.x;
			mouse.y=event.button.y;
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					mouse.botoes[FW_MESQUERDO].pressionado=true;
					mouse.botoes[FW_MESQUERDO].liberado=false;
					mouse.botoes[FW_MESQUERDO].ativo=true;
					mouse.botoes[FW_MESQUERDO].repeticao = event.button.clicks;
					break;
				case SDL_BUTTON_RIGHT:
					mouse.botoes[FW_MDIREITO].pressionado=true;
					mouse.botoes[FW_MDIREITO].liberado=false;
					mouse.botoes[FW_MDIREITO].ativo=true;
					mouse.botoes[FW_MDIREITO].repeticao = event.button.clicks;
					break;
				case SDL_BUTTON_MIDDLE:
					mouse.botoes[FW_MMEIO].pressionado=true;
					mouse.botoes[FW_MMEIO].liberado=false;
					mouse.botoes[FW_MMEIO].ativo=true;
					mouse.botoes[FW_MMEIO].repeticao = event.button.clicks;
					break;
			}
			break; //break dos eventos de mouse button down

		case SDL_MOUSEBUTTONUP:
			mouse.x=event.button.x;
			mouse.y=event.button.y;
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					mouse.botoes[FW_MESQUERDO].ativo=false;
					mouse.botoes[FW_MESQUERDO].liberado=true;
					mouse.botoes[FW_MESQUERDO].pressionado=false;
					mouse.botoes[FW_MESQUERDO].repeticao = 0;
					break;
				case SDL_BUTTON_RIGHT:
					mouse.botoes[FW_MDIREITO].ativo=false;
					mouse.botoes[FW_MDIREITO].liberado=true;
					mouse.botoes[FW_MDIREITO].pressionado=false;
					mouse.botoes[FW_MDIREITO].repeticao = 0;
					break;
				case SDL_BUTTON_MIDDLE:
					mouse.botoes[FW_MMEIO].ativo=false;
					mouse.botoes[FW_MMEIO].liberado=true;
					mouse.botoes[FW_MMEIO].pressionado=false;
					mouse.botoes[FW_MMEIO].repeticao = 0;
					break;
			}
			break; //break dos eventos de mouse button up
	}
}