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
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( imagem );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imagem, IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == NULL )
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
				pixels = NULL;
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
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( imagem );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imagem, IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( newTexture == NULL )
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
				pixels = NULL;
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

	SDL_Surface* surface = TTF_RenderText_Solid(fonte, texto, cor);
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

	SDL_Surface* txtSurface = TTF_RenderText_Blended_Wrapped(fonte, texto, cor, largura);
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

	/*
	SDL_Surface* textSurface = SDL_CreateRGBSurface(0, 1024, 1024, 32, rmask, gmask, bmask, amask);
	SDL_Surface* tmpSurface = 0;
	SDL_Rect dest;
	src.x = dest.x = 0;
	src.y = dest.y = 0;
	src.w = 0;
	int i = 0;
	while(texto[i] != '\0'){
		std::string tmp = "";
		while(texto[i] != '\n' && texto[i] != '\0'){
			if(texto[i] == '\t')
				tmp += "    ";
			else
				tmp.push_back(texto[i]);
			i++;
		}

		tmpSurface = TTF_RenderText_Solid(fonte, tmp.c_str(), cor);
		dest.w = tmpSurface->w;
		dest.h = tmpSurface->h;
		SDL_BlitSurface(tmpSurface, NULL, textSurface, &dest);
		SDL_FreeSurface(tmpSurface);
		dest.y += tmpSurface->h;
		if(dest.w > src.w)
			src.w = dest.w;
		if(texto[i++] == '\0')
			break;
	}
	src.h = dest.y;
	dest.x = 0;
	dest.y = 0;
	dest.w = src.w;
	dest.h = src.h;
	tmpSurface = SDL_CreateRGBSurface(0, src.w, src.h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(textSurface, &dest, tmpSurface, NULL);
	textura = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_FreeSurface(textSurface);

	return (textura != 0);
	*/
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

void Sprite::Renderizar(SDL_Renderer *renderer, double x, double y, unsigned int indicex, unsigned int indicey, double angle, SDL_Point* center, SDL_RendererFlip flip)
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
	SDL_Rect renderQuad = { (int)x, (int)y, src.w, src.h };

	//Set clip rendering dimensions
	if( indicex != 0 || indicey != 0){
		src.x = indicex*src.w;
		src.y = indicey*src.h;
	}
	else{		
		src.x = 0;
		src.y = 0;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, textura, &src, &renderQuad, angle, center, flip );
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