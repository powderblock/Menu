#include <SDL/SDL.h>
#include "util.h"

//variables
float worldsize = 10;
float aspect = width/(float)height;

//Quits and handles cleanup
//Because apparently atexit() is evil
void quit(int rc) {
	SDL_Quit();
	exit(rc);
}

//Get the mouse in worldspace
void mouse(float *x, float *y) {
	*x = ((*x / (float)width) * (worldsize*2) - worldsize) * aspect;
	*y = (1 - (*y / (float)height)) * (worldsize*2) - worldsize;
}
