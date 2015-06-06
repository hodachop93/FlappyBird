#pragma once
#include "ImageGame.h"
#include "GameObject.h"

#define MAX 10

class Scence
{
public:
	Scence(void);
	~Scence(void);
	void Load();
	void drawScence();
private:
	int numOfScence;
	ImageGame *scence[MAX];
};

