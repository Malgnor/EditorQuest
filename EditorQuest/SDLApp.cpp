#include "SDLApp.h"
#include "Jogo.h"

SDLApp::SDLApp(){
	this->Inicializar();
}

SDLApp::~SDLApp(){
	this->Encerrar();
}

void SDLApp::Inicializar(){
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
		printf_s("Falha ao iniciar a SDL! Erro: %s\n", SDL_GetError());
		return;
	}
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	janela = new Jogo;
		
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

int SDLApp::Executar(){
	if(!(SDL_WasInit(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))){
		printf_s("Algum subsistema do SDL não foi inicializado.\n");
		return 1;
	}
	bool sair = false;
	SDL_Event event;
	
	while(!sair) {
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT)
			{
				sair = true;
			}
		}

		janela->Renderizar();
	}
	return 0;
}

void SDLApp::Encerrar(){
	delete janela;
	janela = 0;
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
