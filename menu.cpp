#include <iostream>
#include <SDL/SDL.h>
#include <SOIL.h>
#include <SDL/SDL_opengl.h>
#include <vector>
#include "draw.h"
#include "util.h"
#ifndef __APPLE__
#undef main
#endif

using namespace std;

//Vars:
int FPS = 60;
//Width and height of the window:
int width = 600, height = 600;

SDL_Surface *screen;

GLuint play;
GLuint space;
GLuint options;
GLuint quitTex;

bool running = true;
Uint32 start;

//Functions:
void render();
void FPSCap();
void init();
void events();
void update();
void button1();
void button2();
void button3();

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

bool collide(float x, float y, button A){
	float leftA = A.x; float rightA = A.x + A.w; float topA = A.y; float bottomA = A.y + A.h;
    if(x > leftA && x < rightA && y > topA && y < bottomA){
		return true;
	}
	return false;
}

void update(){
	start = SDL_GetTicks();
	events();
	render();
	FPSCap();
}

void button1(){
	cout << "You clicked the first button!" << endl;
}

void button2(){
	cout << "You clicked the second button!" << endl;
}

void button3(){
	cout << "You clicked the third button!" << endl;
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
	glBindTexture(GL_TEXTURE_2D, space);
	draw(0, 0, 100, 100);
	for(int i = 0; i < buttons.size(); ++i){
		if(i == 0){
			glBindTexture(GL_TEXTURE_2D, play);
		}

		if(i == 1){
			glBindTexture(GL_TEXTURE_2D, options);
		}
		
		if(i == 2){
			glBindTexture(GL_TEXTURE_2D, quitTex);
		}
		draw(buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h);
	}
	SDL_GL_SwapBuffers();
}

void FPSCap(){
	if(1000 / FPS > SDL_GetTicks() - start){
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}

int main(int argc, char *argv[]){
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Menu", NULL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	play = SOIL_load_OGL_texture("images/menu/play.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	space = SOIL_load_OGL_texture("images/menu/space.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	options = SOIL_load_OGL_texture("images/menu/options.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	quitTex = SOIL_load_OGL_texture("images/menu/quit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	init();
	buttons.push_back(button(0.0, 20, 50, 15, button1));
	buttons.push_back(button(0.0, -5, 50, 15, button2));
	buttons.push_back(button(0.0, -30, 50, 15, button3));

	while(running){
		update();
	}

	return 0;
}
