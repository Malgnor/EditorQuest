#include "Entrada.h"

bool Entrada::textInput = false;
bool Entrada::textUpdate = false;
std::string Entrada::texto = "";

Entrada::Entrada(){
	for(int i=0; i<KB_MAX_TECLAS; i++){
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
	mouse.wx = mouse.wy = 0;
}

//funções de retorno de entrada, mouse e teclado
KB_Botao* Entrada::pegaTecla()
{
	return tecla;
}

M_Mouse* Entrada::pegaMouse()
{
	return &mouse;
}

std::string& Entrada::pegaTexto(){
	return texto;
}

bool Entrada::textoUpdate(){
	return textUpdate;
}

void Entrada::ativaInputTexto(){
	if(!textInput){
		texto = "";
		textInput = true;
		SDL_StartTextInput();
	}
}

void Entrada::desativaInputTexto(){
	if(textInput){
		textInput = false;
		SDL_StopTextInput();
	}
}

bool Entrada::toggleInputTexto(){	
	if(textInput){
		textInput = false;
		SDL_StopTextInput();
	} else{
		texto = "";
		textInput = true;
		SDL_StartTextInput();
	}
	return textInput;
}

//funções para atualizar os estados do input
void Entrada::processaTecla(KB_Botao* tecla,SDL_Event& event)
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

void Entrada::reseta(){
	// Remove o pressionamento das teclas do passo anterior
    // Remove o liberamento das teclas do passo anterior
    for(int i=0;i<KB_MAX_TECLAS;i++){
        tecla[i].pressionado = false;
        tecla[i].liberado = false;
	}
    // Remove o pressionamento do mouse do passo anterior
    // Remove o liberamento do mouse do passo anterior
    for(int i=0;i<3;i++){
        mouse.botoes[i].pressionado = false;
        mouse.botoes[i].liberado = false;
	}
	mouse.wx = mouse.wy = 0;
	textUpdate = false;
}

void Entrada::atualiza(SDL_Event& event)
{	
	// Trata de acordo com o tipo de evento
	switch( event.type )
	{
		case SDL_QUIT:
			tecla[KB_ENCERRA].pressionado = true;
			tecla[KB_ENCERRA].ativo = true;
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					processaTecla(&tecla[KB_CIMA],event);
					break;
				case SDLK_RIGHT:
					processaTecla(&tecla[KB_DIREITA],event);
					break;
				case SDLK_DOWN:
					processaTecla(&tecla[KB_BAIXO],event);
					break;
				case SDLK_LEFT:
					processaTecla(&tecla[KB_ESQUERDA],event);
					break;
				case SDLK_z:
					processaTecla(&tecla[KB_Z],event);
					break;
				case SDLK_x:
					processaTecla(&tecla[KB_X],event);
					break;
				case SDLK_c:
					processaTecla(&tecla[KB_C],event);
					break;
				case SDLK_a:
					processaTecla(&tecla[KB_A],event);
					break;
				case SDLK_s:
					processaTecla(&tecla[KB_S],event);
					break;
				case SDLK_d:
					processaTecla(&tecla[KB_D],event);
					break;
				case SDLK_w:
					processaTecla(&tecla[KB_W],event);
					break;
				case SDLK_SPACE:
					processaTecla(&tecla[KB_ESPACO],event);
					break;
				case SDLK_LCTRL:
					processaTecla(&tecla[KB_LCONTROL],event);
					break;
				case SDLK_RETURN:
					processaTecla(&tecla[KB_ENTER],event);
					break;
				case SDLK_ESCAPE:
					processaTecla(&tecla[KB_ESC],event);
					break;
				case SDLK_0:
					processaTecla(&tecla[KB_0],event);
					break;
				case SDLK_1:
					processaTecla(&tecla[KB_1],event);
					break;
				case SDLK_2:
					processaTecla(&tecla[KB_2],event);
					break;
				case SDLK_3:
					processaTecla(&tecla[KB_3],event);
					break;
				case SDLK_4:
					processaTecla(&tecla[KB_4],event);
					break;
				case SDLK_5:
					processaTecla(&tecla[KB_5],event);
					break;
				case SDLK_6:
					processaTecla(&tecla[KB_6],event);
					break;
				case SDLK_7:
					processaTecla(&tecla[KB_7],event);
					break;
				case SDLK_8:
					processaTecla(&tecla[KB_8],event);
					break;
				case SDLK_9:
					processaTecla(&tecla[KB_9],event);
					break;
				case SDLK_m:
					processaTecla(&tecla[KB_M], event);
					break;
				case SDLK_e:
					processaTecla(&tecla[KB_E], event);
					break;
				case SDLK_i:
					processaTecla(&tecla[KB_I], event);
					break;
				case SDLK_t:
					processaTecla(&tecla[KB_T], event);
					break;
				case SDLK_o:
					processaTecla(&tecla[KB_O], event);
					break;
				case SDLK_r:
					processaTecla(&tecla[KB_R], event);
					break;
				case SDLK_q:
					processaTecla(&tecla[KB_Q], event);
					break;
				case SDLK_u:
					processaTecla(&tecla[KB_U], event);
					break;
				case SDLK_g:
					processaTecla(&tecla[KB_G], event);
					break;
				case SDLK_LALT:
					processaTecla(&tecla[KB_LALT], event);
					break;
				case SDLK_BACKSPACE:
					if(textInput){
						texto.pop_back();
						textUpdate = true;
					}
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
					mouse.botoes[M_ESQUERDO].pressionado=true;
					mouse.botoes[M_ESQUERDO].liberado=false;
					mouse.botoes[M_ESQUERDO].ativo=true;
					mouse.botoes[M_ESQUERDO].repeticao = event.button.clicks;
					break;
				case SDL_BUTTON_RIGHT:
					mouse.botoes[M_DIREITO].pressionado=true;
					mouse.botoes[M_DIREITO].liberado=false;
					mouse.botoes[M_DIREITO].ativo=true;
					mouse.botoes[M_DIREITO].repeticao = event.button.clicks;
					break;
				case SDL_BUTTON_MIDDLE:
					mouse.botoes[M_MEIO].pressionado=true;
					mouse.botoes[M_MEIO].liberado=false;
					mouse.botoes[M_MEIO].ativo=true;
					mouse.botoes[M_MEIO].repeticao = event.button.clicks;
					break;
			}
			break; //break dos eventos de mouse button down

		case SDL_MOUSEBUTTONUP:
			mouse.x=event.button.x;
			mouse.y=event.button.y;
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					mouse.botoes[M_ESQUERDO].ativo=false;
					mouse.botoes[M_ESQUERDO].liberado=true;
					mouse.botoes[M_ESQUERDO].pressionado=false;
					mouse.botoes[M_ESQUERDO].repeticao = 0;
					break;
				case SDL_BUTTON_RIGHT:
					mouse.botoes[M_DIREITO].ativo=false;
					mouse.botoes[M_DIREITO].liberado=true;
					mouse.botoes[M_DIREITO].pressionado=false;
					mouse.botoes[M_DIREITO].repeticao = 0;
					break;
				case SDL_BUTTON_MIDDLE:
					mouse.botoes[M_MEIO].ativo=false;
					mouse.botoes[M_MEIO].liberado=true;
					mouse.botoes[M_MEIO].pressionado=false;
					mouse.botoes[M_MEIO].repeticao = 0;
					break;
			}
			break; //break dos eventos de mouse button up
		case SDL_TEXTINPUT:
			if(textInput){
				texto += event.text.text;
				textUpdate = true;
			}
			break;
	}
	if(event.window.event == SDL_WINDOWEVENT_CLOSE){
		tecla[KB_ENCERRA].pressionado = true;
		tecla[KB_ENCERRA].ativo = true;
	}
}