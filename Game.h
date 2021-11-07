#ifndef __Game__
#define __Game__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "SDLGameObject.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "MovingEnemy.h"

class Game{
	public:
		
		//~Game() {}
		// simply set the running variable to true
		bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
		void render();
		void update();
		void handleEvents();
		void clean();
		void quit();
		SDL_Renderer* getRenderer() const { return m_pRenderer; }
		// a function to access the private running variable
		bool running() { return bRunning; }
		bool gameover() { return bGameOver; }
		void set_gameover(bool value) { bGameOver=value; }
		void restart();

		static Game* Instance()
		{
			if(s_pInstance == 0)
			{
				s_pInstance = new Game();
				return s_pInstance;
			}
			return s_pInstance;
		}

		bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
		void updateScore(SDLGameObject* player, SDLGameObject* enemy);
		
	private:
		Game(){}
		~Game(){}
		SDL_Window* my_Window;
	 	SDL_Renderer* m_pRenderer;
		bool bRunning;
		bool bGameOver;
		static Game* s_pInstance;

		std::vector<GameObject*> m_gameObjects;
		std::vector<Player*> m_gamePlayers;
		std::vector<SDLGameObject*> m_gameEnemies;
		std::vector<GameObject*> m_gameOver;
		
		bool paused;
		bool cheatmode;

		int score;
		int highscore;
};
typedef Game TheGame;
#endif /* defined(__Game__) */