#include <SDL/SDL.h>
#include "Util.h"

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
bool mouse(float *x, float *y) {
	int px, py;
	bool clicked = SDL_GetMouseState(&px, &py);
	*x = ((px / (float)width) * (worldsize*2) - worldsize) * aspect;
	*y = (1 - (py / (float)height)) * (worldsize*2) - worldsize;
	return clicked;
}