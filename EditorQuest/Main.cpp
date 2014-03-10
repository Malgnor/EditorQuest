#include "SDLApp.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	srand((unsigned int)time(NULL));
	SDLApp EditorsQuest;
	return EditorsQuest.Executar();
}