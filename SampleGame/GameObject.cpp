#include "GameObject.h"


GameObject::GameObject(string id)
{
	this->id=id;
}


GameObject::~GameObject(void)
{
}

string GameObject::getID()
{

	return id;
}
