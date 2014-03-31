#include "SDLApp.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	srand((unsigned int)time(0));
	SDLApp EditorsQuest;
	return EditorsQuest.Executar();
}