#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include "SDL2/SDL.h"
#include "SoundManager.h"
bool first_time = 1;
bool one_click = 0;
bool isAlive = true;
double yvel=-4.0;
double gravity=0.5;
void Player::draw(){
	TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void Player::update(){
if(isAlive){	
	m_currentFrame = int(((SDL_GetTicks() / 100) % 3));
	if((TheInputHandler::Instance()->getMouseButtonState(LEFT) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_P))){	
		yvel=-4.0;
		m_velocity.setY((float)yvel);
		first_time = 0;
		one_click++;
	}
	else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && !TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
		if(first_time){
			yvel=0.0;
			m_velocity.setY((float)yvel);
			yvel=2.0;
			gravity=0.5;
		}
		else{
			yvel=yvel+gravity;
			m_velocity.setY((float)yvel);	
		}
	}
}else{
	first_time=0;
	one_click=0;
	yvel=-4.0;
	m_velocity.setY((float)yvel);
	m_position.setX(250);
	m_position.setY(250);
	isAlive = true;
}
	

	SDLGameObject::update();
}

void Player::clean(){}