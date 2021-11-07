#ifndef __Player__
#define __Player__

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"

class Player : public SDLGameObject 
{
	public:
		Player(const LoaderParams* pParams) : SDLGameObject(pParams){}
		~Player(){}
		
		virtual void draw();
		virtual void update();
		virtual void clean();

		bool isAlive;
};

#endif /* defined(__Player__) */