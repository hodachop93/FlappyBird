#pragma once
#include "GameObject.h"
#include <GameEngine.h>
using namespace gamerize;

class ImageGame : public GameObject
{
protected:
	Image *image;
	Vector2 position;
public:
	ImageGame(string id, string fileName, float positionX, float positionY);
	ImageGame(string id, string fileName);
	~ImageGame(void);
	void Load(string fileName);
	string getType();
	void *getFilePointer();
	void drawImage();
	void moveImage(Vector2& speed);
	void moveImage(Vector2& speed,int to,int reset);
	void locatePipe(float _y);
	float getPositionX();
	Vector2 getPosition();
};

