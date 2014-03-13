#include "SDLApp.h"
#include "Jogo.h"
#include "Debugger.h"
#include "GerenteJanela.h"

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

	new Jogo;
	dbg = new Debugger;

	bool sair = false;
	SDL_Event event;
	
	while(!sair) {
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT)
				sair = true;
			else if(event.type == SDL_WINDOWEVENT)				
				GJanela.ProcessarEventosW(event);
			else
				GJanela.PegaJanelaFocada()->ProcessarEventos(event);
			/*
			if(event.key.keysym.sym == SDLK_KP_7)
				GJanela.PegaJanelaFocada()->SetaPosicao(16, 32);
			if(event.key.keysym.sym == SDLK_KP_5)
				GJanela.PegaJanelaFocada()->SetaPosicao(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			*/
		}
		GJanela.Atualizar();
		GJanela.Renderizar();
	}
	return 0;
}

void SDLApp::Encerrar(){
	GJanela.Finalizar();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
