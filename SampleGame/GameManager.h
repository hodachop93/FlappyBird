#pragma once
#include "Bird.h"
#include "GameObject.h"
#include "ImageGame.h"
#include "Scence.h"

#define MAX	100

class GameManager
{
private:
	ImageGame *list[MAX];
	int numOfGameObject;
public:
	GameManager(void);
	~GameManager(void);
	void Load();
	ImageGame *getObjects(string id);
	void displayList();
	void randomPipe(ImageGame *image1, ImageGame *image2);
	void Run(int SCREEN_WIDTH,int SCREEN_HEIGHT,Scence& scence,Bird& bird);
	bool Exit(Bird& bird);
	bool isHit(Vector2& Point_Bird, Vector2& Point_Pipe);
};

