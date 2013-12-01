#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "draw.h"

using namespace std;

void draw(float x, float y, float w, float h){
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex2f(x - (w / 2), y - (h / 2));
	glTexCoord2f(0, 1);
	glVertex2f(x - (w / 2), y + (h / 2));
	glTexCoord2f(1, 1);
	glVertex2f(x + (w / 2), y + (h / 2));
	glTexCoord2f(1, 1);
	glVertex2f(x + (w / 2), y + (h / 2));
	glTexCoord2f(1, 0);
	glVertex2f(x + (w / 2), y - (h / 2));
	glTexCoord2f(0, 0);
	glVertex2f(x - (w / 2), y - (h / 2));
	glEnd();
}