#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <vector>
#include "draw.h"
#ifndef __APPLE__
#undef main
#endif

using namespace std;

int FPS = 60;
int width = 600, height = 500;

SDL_Surface *screen;

bool running = true;
Uint32 start;

void render();
void FPSCap();
void init();
void events();
void update();
void button1();
void button2();

struct button{
	float x, y, w, h;
	void (*onClick) (void);
	button(float, float, float, float, void (*) (void));
	void wasClicked(float x, float y){
		//Check for collision
	}
};

button::button(float x, float y, float w, float h, void (*clickFunction) (void)): x(x), y(y), w(w), h(h), onClick(clickFunction){};

vector<button> buttons;

void update(){
	events();
	render();
}

void button1(){
	cout << "You clicked the first button!" << endl;
}

void button2(){
	cout << "You clicked the second button!" << endl;
}

void events(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				case SDLK_ESCAPE:
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
	for(int i = 0; i < buttons.size(); ++i){
		draw(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h);
	}
	SDL_GL_SwapBuffers();
}

void FPSCap(){

}

int main(int argc, char *argv[]){
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Menu", NULL);
	init();
	buttons.push_back(button(0.0, 15, 50, 15, button1));
	buttons.push_back(button(0.0, -12, 50, 15, button2));
	
	while(running){
		update();
	}

	return 0;
}
