#ifndef __MovingEnemy__
#define __MovingEnemy__

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"

class MovingEnemy : public SDLGameObject
{
	public:
		MovingEnemy(const LoaderParams* pParams);
		~MovingEnemy(){}
		
		void draw();
		void update();
		void clean();
		
		Vector2D getPosition(){return m_position;}
		void setChecked(bool value){checked = value;}
		bool getChecked(){return checked;}

};

#endif /* defined(__MovingEnemy__) */
