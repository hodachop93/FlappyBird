#pragma once

#include "ImageGame.h"
#include <iostream>
using namespace std;

#define MAX 2

class Bird
{
public:
	Bird();
	~Bird();
	void Load();
	void drawBird();
	Vector2 getBirdPosition();
private:
	ImageGame *image[MAX];
	Vector2 speed_down;
	Vector2 speed_up;

};

