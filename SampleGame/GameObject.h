#pragma once
#include <string>
using namespace std;

class GameObject
{
public:
	GameObject(string id);
	~GameObject(void);
	virtual void Load(string fileName) = 0;
	virtual string getType() = 0;
	string getID();
	virtual void *getFilePointer() = 0;

protected:
	string id;
};

