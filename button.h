#ifndef MENU_BUTTON_INC
#define MENU_BUTTON_INC

#include <SDL/SDL_opengl.h>

struct button{
	float x, y, w, h;
	int tex;
	void (*onClick) (void);
	button(float, float, float, float, GLuint, void (*) (void));
	void wasClicked(float, float);
	void drawButton();
};

#endif
