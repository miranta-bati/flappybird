#include "Game.h"
#include <vector>

MovingEnemy::MovingEnemy(const LoaderParams* pParams) : SDLGameObject(pParams){
	m_velocity.setX(-1.8);
	m_velocity.setY(1.5);
	setChecked(false);
}

void MovingEnemy::draw(){
	SDLGameObject::draw();
}

void MovingEnemy::update(){
	
	if(m_textureID=="tube1"){
		if(m_position.getY() < -250){
			m_velocity.setY(1.5);
		}else if(m_position.getY() > -110){
			m_velocity.setY(-1.5);
		}
	}else if(m_textureID=="tube2"){
		if(m_position.getY() < 100){
			m_velocity.setY(1.5);
		}else if(m_position.getY() > 340){
			m_velocity.setY(-1.5);
		}
	}
	SDLGameObject::update();
}


void MovingEnemy::clean(){}