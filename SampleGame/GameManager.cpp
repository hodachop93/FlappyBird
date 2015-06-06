#include "GameManager.h"
#include "GameObject.h"
#include <iostream>
using namespace std;

const int PIPE_WIDTH = 60;
const int PIPE_HEIGHT = 400;
const int NUM_OF_PIPE = 2;
const int PIPE_FROM = -300;
const int PIPE_TO = 0;
const int BLANK = 100;
const int RESET = 500;
const int BIRD_WIDTH = 40;
const int BIRD_HEIGHT = 30;
const int SENCE_WIDTH = 450;
const int SENCE_HEIGHT = 600;

GameManager::GameManager(void)
{
	numOfGameObject=0;
	int i=0;
	while (i<MAX)
	{
		list[i]=NULL;
		i++;
	}
}


GameManager::~GameManager(void)
{
	int i=0;
	while (i<100)
	{
		delete list[i];
		i++;
	}
}

void GameManager::Load()
{
	FILE *f = fopen("resource.txt","r");
	if (f==NULL)
	{
		cout<<"Doc file loi"<<endl;
		return;
	}
	else
	{
		cout<<"Doc file resource.txt"<<endl;
		int n=0,i;
		char id[256];
		char fn[256];
		float a,b;
		fscanf(f,"Images:%d\n",&n);
		numOfGameObject=n;
		for(int i=0;i<n;i++)
		{
			fscanf(f,"Id: %s\n",&id);
			fscanf(f,"File: %s\n",&fn);
			fscanf(f,"Position: %f %f\n",&a,&b);
			list[i]= new ImageGame(id ,fn,a,b);
		}
		fclose(f);
		for (i=0;i<NUM_OF_PIPE;i++)
		{
		randomPipe(list[i],list[i+2]);
		}
		return;
	}

}

ImageGame *GameManager::getObjects(string id)
{
	for (int i=0;i<numOfGameObject;i++)
	{
		if (list[i]->getID()==id)
		{
			return list[i];
		}
	}
	return NULL;
}

void GameManager::displayList()
{
	for (int i=0;i<numOfGameObject;i++)
		cout<<list[i]->getID()<<endl;
}

void GameManager::randomPipe(ImageGame *image1,ImageGame *image2)
{
	
	int random;	
	random=rand()%(PIPE_TO - PIPE_FROM)+PIPE_FROM;
	image1->locatePipe(random);
	image2->locatePipe(random+PIPE_HEIGHT+BLANK);
}

void GameManager::Run(int SCREEN_WIDTH, int SCREEN_HEIGHT, Scence& x, Bird& bird)
{
	Vector2 speed(-20.0f,0.0f);
	Device *device = Device::GetInstance();
	Graphics *graphics = device->GetGraphics();
	int i;
	Vector2 speed_pipe(-100.0f,0);
	Vector2 speed_ground(-200.0f,0);
		//draw Render
	x.drawScence();
	for (i=0;i<numOfGameObject;i++)
	{
		list[i]->drawImage();
	}
	bird.drawBird();
		//update status
	
	for (i=0;i<numOfGameObject-1;i++)
	{
		list[i]->moveImage(speed_pipe,(-PIPE_WIDTH),RESET);
	}
	list[i]->moveImage(speed_ground,(-SCREEN_WIDTH/10),0);

	for (int i=0; i < NUM_OF_PIPE; i++)
		if (list[i]->getPositionX()<=(-PIPE_WIDTH+1))
			randomPipe(list[i],list[i+2]);

}

bool GameManager::Exit(Bird& bird)
{
	Vector2 Point;
	Point=bird.getBirdPosition();
	if (isHit(Point, list[0]->getPosition()))
		return true;
	if (isHit(Point, list[1]->getPosition()))
		return true;
	if ((Point.y+BIRD_HEIGHT)>SENCE_HEIGHT)
		return true;
	return false;

}


bool GameManager::isHit(Vector2& Point_Bird, Vector2& Point_Pipe)
{
	if (((Point_Bird.x+BIRD_WIDTH)>Point_Pipe.x)&&((Point_Bird.x+BIRD_WIDTH)<(Point_Pipe.x+PIPE_WIDTH)))
		if (((Point_Bird.y)<(Point_Pipe.y+PIPE_HEIGHT))||((Point_Bird.y+BIRD_HEIGHT)>(Point_Pipe.y+PIPE_HEIGHT+BLANK)))
				return true;
	if (((Point_Bird.x)>Point_Pipe.x)&&((Point_Bird.x)<(Point_Pipe.x+PIPE_WIDTH)))
		if (((Point_Bird.y)<(Point_Pipe.y+PIPE_HEIGHT))||((Point_Bird.y+BIRD_HEIGHT)>(Point_Pipe.y+PIPE_HEIGHT+BLANK)))
				return true;
	return false;
}