#include <SDL\SDL.h>
#include <GL/glew.h>

#include "Engine.h"

namespace Engine {
	int init() {
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//tell SDL to use double buffer to avoid flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}