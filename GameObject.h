#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "LoaderParams.h"

class GameObject
{
	public:
		GameObject(){}
		~GameObject(){}
		
		virtual void draw() = 0;
		virtual void update() = 0;
		virtual void clean() = 0;
			
	protected:
		GameObject(const LoaderParams* pParams) {}
};
#endif /* defined(__GameObject__) */