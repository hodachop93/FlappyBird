#include "Scence.h"
#include <GameEngine.h>
#include "ImageGame.h"
#include <iostream>
using namespace std;
using namespace gamerize;



Scence::Scence(void)
{
	numOfScence=0;
	int i=0;
	while (i<MAX)
	{
		scence[i]=NULL;
		i++;
	}
}


Scence::~Scence(void)
{
	int i=0;
	while (i<MAX)
	{
		delete scence[i];
		scence[i]=NULL;
		i++;
	}
}


void Scence::Load()
{
	FILE *f=fopen("Scence.txt","r");
	if (f==NULL)
	{
		cout<<"Doc file loi!!!";
		return;
	}
	else
	{
		cout<<"Doc file scence.txt"<<endl;
		int n=0;
		char id[256];
		char fn[256];
		float a,b;
		fscanf(f,"Scence: %d\n",&n);
		numOfScence=n;
		for(int i=0;i<n;i++)
		{
			fscanf(f,"Id: %s\n",&id);
			fscanf(f,"File: %s\n",&fn);
			fscanf(f,"Position: %f %f\n",&a,&b);
			scence[i]= new ImageGame(id,fn,a,b);
		}
		fclose(f);
		return;
	}
}

void Scence::drawScence()
{
	Device *device = Device::GetInstance();
	Graphics *graphics = device->GetGraphics();
	graphics->ClearScreen();
	int i;
	
	for(i=0;i<numOfScence;i++)
	{
		scence[i]->drawImage();
	}
}
