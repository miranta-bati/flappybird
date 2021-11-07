#ifndef __Enemy__
#define __Enemy__

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"

class Enemy : public SDLGameObject
{
	public:
		Enemy(const LoaderParams* pParams);
		~Enemy(){}
		
		void draw();
		void update();
		void clean();

		Vector2D getPosition(){return m_position;}
		void setChecked(bool value){checked = value;}
		bool getChecked(){return checked;}

};

#endif /* defined(__Enemy__) */