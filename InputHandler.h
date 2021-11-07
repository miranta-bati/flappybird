#ifndef __InputHandler__
#define __InputHandler__

#include "SDL2/SDL.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
	public:
		static InputHandler* Instance();
		void update();
		void clean();
		bool getMouseButtonState(int buttonNumber);
		bool isKeyDown(SDL_Scancode key);

	private:
		InputHandler();
		~InputHandler() {}
		static InputHandler* s_pInstance;
		std::vector<bool> m_mouseButtonStates;
		const Uint8* m_keystates;
		
		// handle keyboard events
		void onKeyDown();
		void onKeyUp();

		// handle mouse events
		void onMouseButtonDown(SDL_Event& event);
		void onMouseButtonUp(SDL_Event& event);

};
typedef InputHandler TheInputHandler;
#endif /* defined(__Game__) */