#include <iostream>
#include <SDL/SDL.h>
#include <SOIL.h>
#include <SDL/SDL_opengl.h>
#include <vector>
#include "draw.h"
#include "util.h"
#include "button.h"

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
GLuint credits;
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

vector<button> buttons;

void update(){
	start = SDL_GetTicks();
	events();
	render();
	FPSCap();
}

//Buttons functions:
void playButton(){
	cout << "You clicked play!" << endl;
}

void optionsButton(){
	cout << "You clicked options!" << endl;
}

void creditsButton(){
	cout << "I made this game." << endl;
}

void quitButton(){
	running = false;
}

//Check for input from the player:
void events(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
				
			//If the player clicks the mouse:
			case SDL_MOUSEBUTTONDOWN:
				//Set the x and y of the click to some vars:
				mouseX = event.button.x;
				mouseY = event.button.y;
				//Run a function in util which converts those ints to workable ones:
				mouse(&mouseX, &mouseY);
				//Check for collision on the buttons:
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

//Set up OpenGL:
void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Bind space to the background:
	glBindTexture(GL_TEXTURE_2D, space);
	//Draw the background:
	draw(0, 0, 100, 100);
	//Draw the buttons:
	for(int i = 0; i < buttons.size(); ++i){
		buttons[i].drawButton();
	}
	SDL_GL_SwapBuffers();
}

//Keep the FPS stable:
void FPSCap(){
	if(1000 / FPS > SDL_GetTicks() - start){
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}

int main(int argc, char *argv[]){
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Menu", NULL);
	//Start setting up textures:
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//Enable transparency:
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Load in some textures:
	play = SOIL_load_OGL_texture("images/menu/play.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	space = SOIL_load_OGL_texture("images/menu/space.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	options = SOIL_load_OGL_texture("images/menu/options.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	quitTex = SOIL_load_OGL_texture("images/menu/quit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	credits = SOIL_load_OGL_texture("images/menu/credits.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
	init();
	buttons.push_back(button(0.0, 30, 45, 11, play, playButton));
	buttons.push_back(button(0.0, 10, 45, 11, options, optionsButton));
	buttons.push_back(button(0.0, -10, 45, 11, credits, creditsButton));
	//Quits the game:
	buttons.push_back(button(0.0, -30, 45, 11, quitTex, quitButton));

	while(running){
		update();
	}

	return 0;
}
