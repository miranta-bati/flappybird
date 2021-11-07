#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler(){
	for(int i = 0; i < 3; i++){
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler* InputHandler::Instance(){
	if(s_pInstance == 0){
		s_pInstance = new InputHandler();
	}
	return s_pInstance;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
	if(m_keystates != 0){
		if(m_keystates[key] == 1){
			return true;
		}
		else{
			return false;
		}
	}
	return false;
}

void InputHandler::onKeyDown(){}

void InputHandler::onKeyUp(){}

void InputHandler::onMouseButtonDown(SDL_Event& event){
	if(event.button.button == SDL_BUTTON_LEFT){
		m_mouseButtonStates[LEFT] = true;
	}
	if(event.button.button == SDL_BUTTON_MIDDLE){
		m_mouseButtonStates[MIDDLE] = true;
	}
	if(event.button.button == SDL_BUTTON_RIGHT){
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event){
	if(event.button.button == SDL_BUTTON_LEFT){
		m_mouseButtonStates[LEFT] = false;
	}
	if(event.button.button == SDL_BUTTON_MIDDLE){
		m_mouseButtonStates[MIDDLE] = false;
	}
	if(event.button.button == SDL_BUTTON_RIGHT){
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::update(){
	SDL_Event event;
	m_keystates = SDL_GetKeyboardState(0);

	while(SDL_PollEvent(&event)){	
		switch (event.type)
		{
			case SDL_QUIT:
				TheGame::Instance()->quit();
				break;
			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;
			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;
			case SDL_KEYDOWN:
				onKeyDown();
				break;
			case SDL_KEYUP:
				onKeyUp();
				break;
			default:
				break;
		}	
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber){
	if(buttonNumber<0 || buttonNumber>2){ return false; }
	return m_mouseButtonStates[buttonNumber];
}

void InputHandler::clean(){}
