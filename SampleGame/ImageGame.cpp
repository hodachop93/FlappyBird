#include "ImageGame.h"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 450;
const int SCREEN_HEIGHT = 800;

ImageGame::ImageGame(string id, string fileName,float positionX,float positionY) : GameObject(id)
{
	position.x=positionX;
	position.y=positionY;
	Load(fileName);
}

ImageGame::ImageGame(string id, string fileName) : GameObject(id)
{
	Load(fileName);
	position.x=0;
	position.y=0;
}

ImageGame::~ImageGame(void)
{
	delete  image;
}

void ImageGame::Load(string fileName)
{
	const char *s= fileName.data();
	image = new Image(s);
}

string ImageGame::getType()
{
	return "ImageGame";
}

void *ImageGame::getFilePointer()
{
	return image;
}

void ImageGame::drawImage()
{
	Device *device = Device::GetInstance();
	Graphics *graphics = device->GetGraphics();
	graphics->DrawImage(image,position.x,position.y);

}

void ImageGame::moveImage(Vector2& speed)
{
	position += speed * GameTime::GetFrameTime();
}

void ImageGame::moveImage(Vector2 &speed,int to,int reset)
{
	position += speed * GameTime::GetFrameTime();
	if(position.x<(to))
	{
		position.x=reset;
	}
}

void ImageGame::locatePipe(float _y)
{
	this->position.y = _y;
}

float ImageGame::getPositionX()
{
	return position.x;
}

Vector2 ImageGame::getPosition()
{
	return position;
}