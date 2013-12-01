#include <SDL/SDL_opengl.h>
#include "draw.h"
#include "button.h"

button::button(float x, float y, float w, float h, GLuint tex, void (*clickFunction) (void)) : x(x), y(y), w(w), h(h), tex(tex), onClick(clickFunction) { }

void button::wasClicked(float xClick, float yClick){
	float left = x - (w / 2); float right = x + (w / 2); float top = y - (h / 2); float bottom = y + (h / 2);
		//Check for collision with the click and all of the buttons values:
		if(xClick > left && xClick < right && yClick > top && yClick < bottom){
			this->onClick();
		}
}

void button::drawButton() {
	glBindTexture(GL_TEXTURE_2D, tex);
	draw(x, y, w, h);
}
