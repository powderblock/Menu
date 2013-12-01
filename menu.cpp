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

float mouseX, mouseY;

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
	void wasClicked(float, float);
};

void button::wasClicked(float xClick, float yClick){
	float left = x - (w / 2); float right = x + (w / 2); float top = y - (h / 2); float bottom = y + (h / 2);
	if(xClick > left && xClick < right && yClick > top && yClick < bottom){
		this->onClick();
	}
}

button::button(float x, float y, float w, float h, void (*clickFunction) (void)): x(x), y(y), w(w), h(h), onClick(clickFunction){};

vector<button> buttons;

void update(){
	start = SDL_GetTicks();
	events();
	render();
	FPSCap();
}

void playButton(){
	cout << "You clicked play!" << endl;
}

void optionsButton(){
	cout << "You clicked options!" << endl;
}

void quitButton(){
	running = false;
}

void events(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				mouseX = event.button.x;
				mouseY = event.button.y;
				mouse(&mouseX, &mouseY);
				for(int i = 0; i < buttons.size(); ++i){
					buttons[i].wasClicked(mouseX, mouseY);
				}
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
	buttons.push_back(button(0.0, 20, 50, 15, playButton));
	buttons.push_back(button(0.0, -5, 50, 15, optionsButton));
	buttons.push_back(button(0.0, -30, 50, 15, quitButton));

	while(running){
		update();
	}

	return 0;
}
