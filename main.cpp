#include "Game.h"
// our Game object
Game* my_game = 0;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Uint32 frameStart, frameTime;

int main(int argc, char* argv[]){
	std::cout << "game init attempt...\n";
	if(TheGame::Instance()->init("Flappy Bird", 100, 100, 800, 496, false))
	{
		std::cout << "game init success!\n";
		while(TheGame::Instance()->running())
		{
			TheGame::Instance()->set_gameover(false);
			while(!TheGame::Instance()->gameover()){
				frameStart = SDL_GetTicks();

				TheGame::Instance()->handleEvents();
				TheGame::Instance()->update();
				TheGame::Instance()->render();

				frameTime = SDL_GetTicks() - frameStart;
				
				if(frameTime< DELAY_TIME){
					SDL_Delay((int)(DELAY_TIME - frameTime));
				}
			}

		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}
	std::cout << "game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}