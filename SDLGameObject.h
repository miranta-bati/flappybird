#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "LoaderParams.h"
#include "GameObject.h"
#include "Vector2D.h"
#include <string>

class SDLGameObject : public GameObject
{
	public:
		SDLGameObject(const LoaderParams* pParams);
		~SDLGameObject(){}
		virtual void draw();
		virtual void update();
		virtual void clean();
		Vector2D getPosition(){return m_position;}
		int getWidth(){return m_width;}
		int getHeight(){return m_height;}
		std::string getTextureID(){return m_textureID;}
		void setChecked(bool value){checked = value;}
		bool getChecked(){return checked;}

	protected:
		Vector2D m_position;
		Vector2D m_velocity;
		Vector2D m_acceleration;
		
		int m_width;
		int m_height;
		
		int m_currentRow;
		int m_currentFrame;
		
		std::string m_textureID;

		bool checked;
};

#endif /* defined(__SDLGameObject__) */