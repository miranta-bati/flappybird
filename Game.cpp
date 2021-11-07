#include "Game.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h> 
#include <sstream> 
#include <string>

Game* Game::s_pInstance = 0;
int start_place = 500;	
int random_value;
int pick_random_enemy;

TTF_Font* Sans;
int score = 0;
int high_score = 0;

//Output Messages
std::stringstream strm;
SDL_Surface* surfaceScore_msg;
SDL_Texture* Score_msg;
SDL_Rect Score_msg_rect;

std::stringstream strm2;
SDL_Surface* surfaceHighScore_msg;
SDL_Texture* HighScore_msg;
SDL_Rect HighScore_msg_rect;

SDL_Texture* CheatMessage;
SDL_Rect CheatMessage_rect;
SDL_Surface* surfaceCheatMessage;

SDL_Texture* Message;
SDL_Rect Message_rect;
SDL_Surface* surfaceMessage;

//Font COlors
SDL_Color White = {255, 255, 255};
SDL_Color Black = {10, 10, 10};

bool passed = false;
int w, h;
int enemy_counter = 0;
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

	srand(time(NULL));
	int flags = 0;
	if(fullscreen){
	 	flags = SDL_WINDOW_MAXIMIZED;
	}

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		std::cout << "SDL init success\n";
		// init the window
		my_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(my_Window != 0){ // window init success
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(my_Window, -1, 0);
			if(m_pRenderer != 0){ // renderer init success
				std::cout << "renderer creation success\n";
			}
			else{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
	 	}
		else{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	bRunning = true; // everything inited successfully, start the main loop
	bGameOver = false;

	if(TTF_Init() == -1){
		return false;
	}

	if(!TheTextureManager::Instance()->load("assets/bird.png", "animate", m_pRenderer)){
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/background.png", "bgr", m_pRenderer)){
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/ground.png", "ground", m_pRenderer)){
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/tube1.png", "tube1", m_pRenderer)){
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/tube2.png", "tube2", m_pRenderer)){
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/gameover.png", "gameover", m_pRenderer)){
		return false;
	}
	
	if(!TheSoundManager::Instance()->load("assets/point.wav", "point_sound", SOUND_SFX)){
		return false;
	}
	if(!TheSoundManager::Instance()->load("assets/wing.wav", "wing_sound", SOUND_SFX)){
		return false;
	}
	if(!TheSoundManager::Instance()->load("assets/hit.wav", "hit_sound", SOUND_SFX)){
		return false;
	}

	//get width and height of screen
	SDL_GetRendererOutputSize(m_pRenderer,&w,&h);

	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(0, 0, 800, 384, "bgr")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(0, h-112, 1600, 112, "ground")));
	m_gamePlayers.push_back(new Player(new LoaderParams(250, 250, 36, 26, "animate")));


	Sans = TTF_OpenFont("assets/flappy_font.ttf", 24); //this opens a font style and sets a size
	if(Sans==NULL){
		return false;
	}


	  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	strm << score;
	surfaceScore_msg = TTF_RenderText_Solid(Sans, strm.str().c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Score_msg = SDL_CreateTextureFromSurface(m_pRenderer, surfaceScore_msg); //now you can convert it into a texture

	Score_msg_rect.x = w/2;  //controls the rect's x coordinate 
	Score_msg_rect.y = 0; // controls the rect's y coordinte
	Score_msg_rect.w = 45; // controls the width of the rect
	Score_msg_rect.h = 45; // controls the height of the rect
	
	strm2 << "";
	surfaceHighScore_msg = TTF_RenderText_Solid(Sans, strm2.str().c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	HighScore_msg = SDL_CreateTextureFromSurface(m_pRenderer, surfaceHighScore_msg); //now you can convert it into a texture

	HighScore_msg_rect.x = w/2 + 10;  //controls the rect's x coordinate 
	HighScore_msg_rect.y = 50; // controls the rect's y coordinte
	HighScore_msg_rect.w = 25; // controls the width of the rect
	HighScore_msg_rect.h = 25; // controls the height of the rect
	
	surfaceMessage = TTF_RenderText_Solid(Sans, "Press P to play", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Message = SDL_CreateTextureFromSurface(m_pRenderer, surfaceMessage); //now you can convert it into a texture

	Message_rect.x = (w/2)-125;  //controls the rect's x coordinate 
	Message_rect.y = (h/2)-120; // controls the rect's y coordinte
	Message_rect.w = 250; // controls the width of the rect
	Message_rect.h = 40; // controls the height of the rect

	surfaceCheatMessage = TTF_RenderText_Solid(Sans, "Cheat Mode : ON", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	CheatMessage = SDL_CreateTextureFromSurface(m_pRenderer, surfaceCheatMessage); //now you can convert it into a texture

	CheatMessage_rect.x = (w-200);  //controls the rect's x coordinate 
	CheatMessage_rect.y = (h-40); // controls the rect's y coordinte
	CheatMessage_rect.w = 180; // controls the width of the rect
	CheatMessage_rect.h = 20; // controls the height of the rect
	
	paused = true;
	cheatmode = false;
	restart();
	return true;
}


void Game::render(){
 	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

 	m_gameObjects[0]->draw();

 	for(std::vector<Enemy*>::size_type i = 0; i != m_gameEnemies.size(); i++){
		m_gameEnemies[i]->draw();
	}
 	for(std::vector<GameObject*>::size_type i = 1; i != m_gameObjects.size(); i++){
		m_gameObjects[i]->draw();
	}

 	for(std::vector<Player*>::size_type i = 0; i != m_gamePlayers.size(); i++){
		m_gamePlayers[i]->draw();
	}
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameOver.size(); i++){
		m_gameOver[i]->draw();
	}

 	SDL_RenderCopy(m_pRenderer, Score_msg, NULL, &Score_msg_rect); 

 	if(paused==true){
 		SDL_RenderCopy(m_pRenderer, HighScore_msg, NULL, &HighScore_msg_rect);
 		SDL_RenderCopy(m_pRenderer, Message, NULL, &Message_rect);
 	}
 	if(cheatmode==true){
 		SDL_RenderCopy(m_pRenderer, CheatMessage, NULL, &CheatMessage_rect); 
 	}

 	SDL_RenderPresent(m_pRenderer); // draw to the screen
}


void Game::handleEvents(){
	TheInputHandler::Instance()->update();


	if(paused==false){
		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
			paused = true;
		}
	}else{
		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_P) ){
			paused = false;
			if(!m_gameOver.empty()){
		 		m_gameOver.pop_back();
		 		restart();
		 	}
		}
	} 

	if(cheatmode==false){
		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_C)){
			cheatmode = true;
		}
	}else{
		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_X)){
			cheatmode = false;
		}
	} 
}

void Game::clean(){
 	std::cout << "cleaning game\n";
 	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(my_Window);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::update(){
	
	strm.str("");
	strm << score;
	surfaceScore_msg = TTF_RenderText_Solid(Sans, strm.str().c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Score_msg = SDL_CreateTextureFromSurface(m_pRenderer, surfaceScore_msg); //now you can convert it into a texture
	if( score>high_score ){
		high_score = score;
		strm2 << score;
		surfaceHighScore_msg = TTF_RenderText_Solid(Sans, strm2.str().c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
		HighScore_msg = SDL_CreateTextureFromSurface(m_pRenderer, surfaceScore_msg); //now you can convert it into a texture
	}
	

	 if(enemy_counter<6 ){
	 	
	 	pick_random_enemy = rand() % 2 +1;

	 	if(pick_random_enemy==1){
	 		if(passed==false){
		 		start_place+=200;
			}else{
				start_place=1140;
			}
	 		random_value = rand() % (250) + (55);
			random_value = - random_value;	
			m_gameEnemies.push_back(new Enemy(new LoaderParams(start_place, random_value, 52, 320, "tube1")));//x=startplace , y = -250..-70
			m_gameEnemies.push_back(new Enemy(new LoaderParams(start_place, random_value+420, 52, 320, "tube2")));//x=startplc, y = h/2-90..h/2+90
			

	 	}else if(pick_random_enemy==2){
	 		if(passed==false){
				start_place+=200;
			}else{
				start_place = 1140;		
			}
	 		random_value = rand() % (250) + (55);
			random_value = - random_value;
	 		m_gameEnemies.push_back(new MovingEnemy(new LoaderParams(start_place, random_value, 52, 320, "tube1")));
	 		
	 		m_gameEnemies.push_back(new Enemy(new LoaderParams(start_place, random_value+420+157, 52, 320, "tube2")));//easy_fix
	 			
	 	}
	 	enemy_counter++;
		
	}else{
		if(m_gameEnemies.front()->getPosition().getX()<=-60){
			passed=true;
			m_gameEnemies.erase(m_gameEnemies.begin());
			m_gameEnemies.erase(m_gameEnemies.begin());
			enemy_counter--;
		}
	}

	//check if paused
	if(!paused){
		
		//not paused so update
		for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++){
			m_gameObjects[i]->update();
		}
		for(std::vector<Enemy*>::size_type i = 0; i != m_gameEnemies.size(); i++){
				m_gameEnemies[i]->update();
		}
		for(std::vector<Player*>::size_type i = 0; i != m_gamePlayers.size(); i++){
			m_gamePlayers[i]->update();
		}

		//check for collision
		for(std::vector<Enemy*>::size_type i = 0; i != m_gameEnemies.size(); i++){
				updateScore(dynamic_cast<SDLGameObject*>(m_gamePlayers[0]), dynamic_cast<SDLGameObject*>(m_gameEnemies[i]));
				

			}

		//if not paused and cheat mode disabled
		if(!cheatmode){
			if (checkCollision(dynamic_cast<SDLGameObject*>(m_gamePlayers[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
				m_gameOver.push_back(new SDLGameObject(new LoaderParams((w/2)-200, (h/2)-68, 400, 68, "gameover")));
					m_gameOver[0]->update();
					paused=true;
					bGameOver=true;
					m_gamePlayers[0]->isAlive = false;

			}			

			for(std::vector<Enemy*>::size_type i = 0; i != m_gameEnemies.size(); i++){
				if(checkCollision(dynamic_cast<SDLGameObject*>(m_gamePlayers[0]), dynamic_cast<SDLGameObject*>(m_gameEnemies[i]))){
					m_gameOver.push_back(new SDLGameObject(new LoaderParams((w/2)-200, (h/2)-68, 400, 68, "gameover")));
					m_gameOver[0]->update();
					paused=true;
					bGameOver=true;
					m_gamePlayers[0]->isAlive = false;
				}
			}
		}
		
	}
}

void Game::quit(){
	bRunning = false;
	bGameOver = true;
}

//resets all values to restart the game
void Game::restart(){
	m_gameEnemies.clear();
	enemy_counter=0;
	passed = false;
	start_place=500;
	score = 0;
}

bool Game::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();
	
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if(bottomA <= topB ){return false;}
	if(topA >= bottomB){return false;}
	if(rightA <= leftB){return false;}
	if(leftA >= rightB){return false;}
	TheSoundManager::Instance()->playSound("hit_sound", 0);
	return true;
}

void Game::updateScore(SDLGameObject* player, SDLGameObject* enemy)
{
	int middleE;
	int rightP;
	
	middleE = enemy->getPosition().getX() + (enemy->getWidth() / 2 );
	
	rightP = player->getPosition().getX() + player->getWidth();
	
	if(rightP > middleE && enemy->getChecked() ==false && enemy->getTextureID() == "tube1"){score++; enemy->setChecked(true);TheSoundManager::Instance()->playSound("point_sound", 0);}
	
	return;
}