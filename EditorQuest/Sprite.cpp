#include "Sprite.h"
#include <string>

Sprite::Sprite(){
	src.x = src.y = src.w = src.h = 0;
	textura = 0;
	pixels = 0;
	pitch = 0;
}

Sprite::~Sprite(){
	this->Destruir();
}

bool Sprite::CriaTexturaDaImagem(SDL_Renderer* renderer, const char *imagem, int largura, int altura){
	this->Destruir();

	//The final texture
	SDL_Texture* newTexture = 0;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( imagem );
	if( loadedSurface == 0 )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imagem, IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
		if( formattedSurface == 0 )
		{
			printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == 0 )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );
				//Lock texture for manipulation
				SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &pixels, &pitch );

				//Copy loaded/formatted surface pixels
				memcpy( pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				src = formattedSurface->clip_rect;
				
				//Unlock texture to update
				SDL_UnlockTexture( newTexture );
				pixels = 0;
			}
			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}	
		
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	
	if(largura)
		src.w = largura;
	if(altura)
		src.h = altura;

	textura = newTexture;

	return (textura != 0);
}

bool Sprite::CriaTexturaDaImagemC(SDL_Renderer* renderer, const char *imagem, int largura, int altura, Uint8 r, Uint8 g, Uint8 b){
	this->Destruir();

	//The final texture
	SDL_Texture* newTexture = 0;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( imagem );
	if( loadedSurface == 0 )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imagem, IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
		if( formattedSurface == 0 )
		{
			printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == 0 )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

				//Lock texture for manipulation
				SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &pixels, &pitch );

				//Copy loaded/formatted surface pixels
				memcpy( pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Get image dimensions
				src = formattedSurface->clip_rect;

				//Get pixel data in editable format
				Uint32* Pixels = (Uint32*)pixels;
				int pixelCount = ( pitch / 4 ) * src.h;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB( formattedSurface->format, r, g, b );
				Uint32 transparent = SDL_MapRGBA( formattedSurface->format, r, g, b, 0x00 );

				//Color key pixels
				for( int i = 0; i < pixelCount; ++i )
				{
					if( Pixels[ i ] == colorKey )
					{
						Pixels[ i ] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture( newTexture );
				pixels = 0;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}	
		
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	
	if(largura)
		src.w = largura;
	if(altura)
		src.h = altura;

	textura = newTexture;

	return (textura != 0);
}

bool Sprite::CriaTexturaDoTexto(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor){
	this->Destruir();
	SDL_Surface* surface;
	if(*texto != '\0')
		surface = TTF_RenderText_Solid(fonte, texto, cor);
	else
		surface = TTF_RenderText_Solid(fonte, " ", cor);
	if(surface == 0){
		printf( "Falha ao criar Surface! SDL Error: %s\n",  SDL_GetError() );
	} else {
		textura = SDL_CreateTextureFromSurface(renderer, surface);
		if(textura == 0){
			printf( "Falha ao criar Texture! SDL Error: %s\n",  SDL_GetError() );
		} else {
		src = surface->clip_rect;
		}
	}
	SDL_FreeSurface(surface);

	return (textura != 0);
}

bool Sprite::CriaTexturaDoTextoC(SDL_Renderer* renderer, const char *texto, TTF_Font *fonte, SDL_Color cor, Uint32 largura){
	this->Destruir();

	SDL_Surface* txtSurface;
	if(*texto != '\0')
		txtSurface = TTF_RenderText_Blended_Wrapped(fonte, texto, cor, largura);
	else
		txtSurface = TTF_RenderText_Blended_Wrapped(fonte, " ", cor, largura);

	if(txtSurface == 0){
		printf( "Falha ao criar Surface! SDL Error: %s\n",  TTF_GetError() );
	} else {
		textura = SDL_CreateTextureFromSurface(renderer, txtSurface);
		if(textura == 0){
			printf( "Falha ao criar Texture! SDL Error: %s\n",  SDL_GetError() );
		} else {
			src = txtSurface->clip_rect;
		}
	}
	SDL_FreeSurface(txtSurface);

	return (textura != 0);
}

bool Sprite::CriaTexturaMenu(SDL_Renderer* renderer, const char *imagem, const char *texto, TTF_Font *fonte, SDL_Color cortexto){
	this->Destruir();

	SDL_Surface* txtSurface = TTF_RenderText_Solid(fonte, texto, cortexto);
	if(txtSurface == 0){
		printf( "Falha ao criar Surface! SDL Error: %s\n",  TTF_GetError() );
	} else {
		SDL_Surface* menuSurface = IMG_Load(imagem);
		if(menuSurface == 0){
			printf( "Falha ao criar Surface! Imagem: %s  SDL Error: %s\n", imagem, IMG_GetError() );
		} else {
			SDL_Rect srcrect = menuSurface->clip_rect;
			srcrect.w /= 3;
			srcrect.h /= 3;
			SDL_Rect dstrect = {0, 0, srcrect.w, srcrect.h};
			src.w = ((txtSurface->clip_rect.w/srcrect.w)+3)*srcrect.w;
			src.h = txtSurface->clip_rect.h < srcrect.h*2 ? srcrect.h*2 : ((txtSurface->clip_rect.h/srcrect.h)+1)*srcrect.h;

			SDL_Surface* endSurface = SDL_CreateRGBSurface(0, src.w, src.h, 32, rmask, gmask, bmask, amask);
			if(endSurface == 0){
				printf( "Falha ao criar Surface! SDL Error: %s\n",  SDL_GetError() );
			} else {
				for(int y = 0; y < src.h/srcrect.h; y++){
					for(int x = 0; x < src.w/srcrect.w; x++){
						dstrect.x = x*srcrect.w;
						dstrect.y = y*srcrect.h;
						if(y == 0)
							srcrect.y = 0;
						else if(y == (src.h/srcrect.h)-1)
							srcrect.y = srcrect.h*2;
						else
							srcrect.y = srcrect.h;
						if(x == 0)
							srcrect.x = 0;
						else if(x == (src.w/srcrect.w)-1)
							srcrect.x = srcrect.w*2;
						else
							srcrect.x = srcrect.w;
						SDL_BlitSurface(menuSurface, &srcrect, endSurface, &dstrect);
					}
				}
	
				srcrect = txtSurface->clip_rect;
				dstrect.x = (src.w-srcrect.w)/2;
				dstrect.y = (src.h-srcrect.h)/2;
				dstrect.w = srcrect.w;
				dstrect.h = srcrect.h;

				SDL_BlitSurface(txtSurface, &srcrect, endSurface, &dstrect);

				textura = SDL_CreateTextureFromSurface(renderer, endSurface);
				if(textura == 0){
					printf( "Falha ao criar Textura! SDL Error: %s\n",  SDL_GetError() );
				}
			}
			SDL_FreeSurface(endSurface);
		}
		SDL_FreeSurface(menuSurface);
	}
	SDL_FreeSurface(txtSurface);

	return (textura != 0);
}

bool Sprite::CriaTexturaMapa(SDL_Renderer* renderer, unsigned int **mapa, unsigned int largura, unsigned int altura){
	this->Destruir();

	SDL_Surface* tileSurface = IMG_Load("resources/imgs/tileset.png");
	if(tileSurface == 0){
		printf("Falha ao criar Surface! Path: resources/imgs/tileset.png IMG_Error: %s\n", IMG_GetError());
	} else {
		SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, largura*32, altura*32, 32, rmask, gmask, bmask, amask);
		if(mapSurface == 0){
			printf("Falha ao criar Surface! SDL Error: %s\n", SDL_GetError());
		} else {
			SDL_Rect srcrect = {0, 0, 32, 32};
			SDL_Rect dstrect = {0, 0, 32, 32};
			for(unsigned int i = 0; i < altura; i++){
				for(unsigned int j = 0; j < largura; j++){
					dstrect.x = j*32;
					dstrect.y = i*32;
					srcrect.x = mapa[i][j]*32;
					SDL_BlitSurface(tileSurface, &srcrect, mapSurface, &dstrect);
				}
			}
			textura = SDL_CreateTextureFromSurface(renderer, mapSurface);
			if(textura == 0){
				printf("Falha ao criar textura! SDL Error: %s\n", SDL_GetError());
			} else {
				src = mapSurface->clip_rect;
			}
		}
		SDL_FreeSurface(mapSurface);
	}

	SDL_FreeSurface(tileSurface);

	return (textura != 0);
}

bool Sprite::CriaTexturaIcone(SDL_Renderer* renderer, unsigned int x, unsigned int y){
	this->Destruir();

	SDL_Surface* itemSurface = IMG_Load("resources/imgs/itemset.png");
	if(itemSurface == 0){
		printf("Falha ao criar Surface! Path: resources/imgs/itemset.png IMG_Error: %s\n", IMG_GetError());
	} else {
		SDL_Surface* iconeSurface = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
		if(iconeSurface == 0){
			printf("Falha ao criar Surface! SDL Error: %s\n", SDL_GetError());
		} else {
			SDL_Rect srcrect = {x*32, y*32, 32, 32};
			SDL_Rect dstrect = {0, 0, 32, 32};

			SDL_BlitSurface(itemSurface, &srcrect, iconeSurface, &dstrect);

			textura = SDL_CreateTextureFromSurface(renderer, iconeSurface);
			if(textura == 0){
				printf("Falha ao criar textura! SDL Error: %s\n", SDL_GetError());
			} else {
				src = iconeSurface->clip_rect;
			}
		}
		SDL_FreeSurface(iconeSurface);
	}

	SDL_FreeSurface(itemSurface);

	return (textura != 0);
}

void Sprite::Renderizar(SDL_Renderer *renderer, double posX, double posY, unsigned int indiceX, unsigned int indiceY, double angulo, double escalaX, double escalaY, SDL_Point* centro, SDL_RendererFlip flip)
{
	if(textura == 0){		
		printf( "Falha ao renderizar Sprite! Textura nula\n");
		return;
	}
	else if(renderer == 0){
		printf( "Falha ao renderizar Sprite! Renderer nulo\n" );
		return;
	}
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { (int)posX, (int)posY, (int)(src.w*escalaX), (int)(src.h*escalaY) };

	//Set clip rendering dimensions
	if( indiceX != 0 || indiceY != 0){
		src.x = indiceX*src.w;
		src.y = indiceY*src.h;
	}
	else{		
		src.x = 0;
		src.y = 0;
	}

	angulo = angulo*180.0/M_PI;

	//Render to screen
	SDL_RenderCopyEx(renderer, textura, &src, &renderQuad, angulo, centro, flip );
}

SDL_Rect Sprite::PegaDimensao(){
	SDL_Rect dms = {0, 0, src.w, src.h};
	return dms;
}

void Sprite::PegaDimensao(int &w, int &h){
	w = src.w;
	h = src.h;
}

int Sprite::SetaAlphaMod(Uint8 alfa){
	return SDL_SetTextureAlphaMod(textura, alfa);
}

int Sprite::SetaBlendMode(SDL_BlendMode blend){
	return SDL_SetTextureBlendMode(textura, blend);
}

int Sprite::SetaColorMod(Uint8 r, Uint8 g, Uint8 b){
	return SDL_SetTextureColorMod(textura, r, g, b);
}

int Sprite::SetaColorMod(SDL_Color cor){
	return SDL_SetTextureColorMod(textura, cor.r, cor.g, cor.b);
}

void Sprite::Destruir(){
	SDL_DestroyTexture(textura);
	src.x = src.y = src.w = src.h = 0;
	textura = 0;
	pixels = 0;
	pitch = 0;
}