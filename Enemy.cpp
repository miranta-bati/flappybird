#include "Enemy.h"
#include "Game.h"
#include <vector>

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams){
	m_velocity.setX(-1.8);
	setChecked(false);
}

void Enemy::draw(){
	SDLGameObject::draw();
}

void Enemy::update(){


	if(m_textureID=="ground"){
		if(m_position.getX() < -800){
			m_position.setX(-10);
		}
	}
	SDLGameObject::update();
}


void Enemy::clean(){}