#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "draw.h"
#undef main

using namespace std;

int FPS = 60;
int width = 600, height = 480;

SDL_Surface *screen;

bool running = true;
Uint32 start;

void render();
void FPSCap();
void init();
void events();
void update();

void update(){
	events();
	render();
}

void events(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 0);
	draw(25.0, 25.0, 5.0, 5.0);
	SDL_GL_SwapBuffers();
}

void FPSCap(){

}

int main(){
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Menu", NULL);
	init();
	while(running){
		update();
	}

	return 0;
}