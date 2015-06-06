#ifdef WIN32
#include <GameEngine.h>
#include <stdlib.h>
#include "SampleGame.h"
#include <vld.h>
#include <conio.h>
using namespace gamerize;


const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 800;


/**
* The main Program
**/
int main()
{
	// Init Graphics 
	Device *device = Device::GetInstance();
	device->InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	Graphics *graphics = device->GetGraphics();
	InputManager *inputManager = InputManager::GetInstance();

	GameManager Game;
	Game.Load();

	Scence scence;
	scence.Load();

	Bird bird;
	bird.Load();

	while (device->IsRunning())
	{
		
		Game.Run(SCREEN_WIDTH,SCREEN_HEIGHT,scence, bird);
		if (Game.Exit(bird))
			break;

	}

	InputManager::DestroyInstance();
	Device::DestroyInstance();
	return 0;
}

#endif