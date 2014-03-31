#include "SDLApp.h"
#include "GerenteJanela.h"
#include "Janela.h"
#include "MenuInicial.h"
#include "DebugJanelas.h"

SDLApp::SDLApp(){
	this->Inicializar();
}

void SDLApp::Inicializar(){
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
		printf_s("Falha ao iniciar a SDL! Erro: %s\n", SDL_GetError());
		return;
	}
	
	
	if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
	{
		printf( "Warning: VSync not enabled!" );
	}

	if(IMG_Init(IMG_INIT_PNG) == 0){
		printf_s("Falha ao iniciar a SDL_Image! Erro: %s\n", IMG_GetError());
	}
	if(TTF_Init() == -1){		
		printf_s("Falha ao iniciar a SDL_ttf! Erro: %s\n", TTF_GetError());
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

int SDLApp::Executar(){
	if(!(SDL_WasInit(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))){
		printf_s("Algum subsistema do SDL não foi inicializado.\n");
		return 1;
	}

	new Janela(new MenuInicial());
#ifdef DEBUG
	new Janela(new DebugJanelas());
#endif

	bool sair = false;
	SDL_Event event;
	Uint32 deltaTime = 0;
	Uint32 ticks = SDL_GetTicks();
	GerenteJanela gerente = GerenteJanela::PegaGerenteJanela();
	while(!sair) {
		while(SDL_GetTicks() < ticks+(1000/60))
			SDL_Delay(ticks+(1000/60)-SDL_GetTicks());
		deltaTime = SDL_GetTicks() - ticks;
		ticks = SDL_GetTicks();
		gerente.PegaJanelaFocada()->entrada.reseta();
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT)
				sair = true;
			else if(event.type == SDL_WINDOWEVENT)				
				gerente.ProcessarEventosW(event);
			gerente.PegaJanelaFocada()->ProcessarEventos(event);
		}
		gerente.Atualizar(deltaTime);
		gerente.Renderizar();
		if(gerente.PegaQtdJanelas() == 0)
			sair = true;
	}
	gerente.Finalizar();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}