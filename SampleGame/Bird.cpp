#include "Bird.h"

Bird::Bird()
{
	for (int i=0;i<MAX;i++)
		image[i]=NULL;
	speed_down.x = 0;
	speed_down.y = 0;
	speed_up.x = 0;
	speed_up.y = 0;
}

Bird::~Bird(void)
{
	for (int i=0;i<MAX;i++)
		delete image[i];
}

void Bird::Load()
{
	FILE *f=fopen("bird.txt","r");
	if (f==NULL)
	{
		cout<<"Doc file loi!!!";
		return;
	}
	else
	{
		cout<<"Doc file bird.txt"<<endl;
		char id[256];
		char fn[256];
		int i=0;
		float positionX, positionY;
		float speed_downY, speed_upY;

		fscanf(f,"Id: %s\n",&id);
		fscanf(f,"File: %s\n",&fn);
		fscanf(f,"Position: %f %f\n",&positionX,&positionY);
		fscanf(f,"Speed_downY: %f\n",&speed_downY);
		fscanf(f,"Speed_upY: %f\n",&speed_upY);
		image[i++] = new ImageGame(id,fn,positionX,positionY);

		fscanf(f,"File: %s\n",&fn);
		image[i++] = new ImageGame(id,fn,positionX,positionY);

		speed_down.x = 0;
		speed_down.y = speed_downY;
		speed_up.x = 0;
		speed_up.y = speed_upY;

		fclose(f);
		return;
	}
}

void Bird::drawBird()
{
	InputManager *inputManager = InputManager::GetInstance();
	if (inputManager->IsKeyDown(InputManager::KEY_UP_ARROW))
	{
			// Handle event 
		image[1]->drawImage();
			//Update status
		for (int i=0; i<2; i++)
		{
			image[i]->moveImage(speed_up);
		}
		
	}
	else
	{
			//Handle event
		image[0]->drawImage();
			//Update status
		for (int i=0; i<2; i++)
		{
			image[i]->moveImage(speed_down);
		}	
	}
		

}

Vector2 Bird::getBirdPosition()
{
	return image[0]->getPosition();
}