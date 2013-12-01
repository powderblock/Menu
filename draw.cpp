#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "draw.h"

using namespace std;

void draw(float x, float y, float w, float h){
	glBegin(GL_TRIANGLES);
	glVertex2f(x - (w / 2), y - (h / 2));
	glVertex2f(x - (w / 2), y + (h / 2));
	glVertex2f(x + (w / 2), y + (h / 2));
	glVertex2f(x + (w / 2), y + (h / 2));
	glVertex2f(x + (w / 2), y - (h / 2));
	glVertex2f(x - (w / 2), y - (h / 2));
	glEnd();
}