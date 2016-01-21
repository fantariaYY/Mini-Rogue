#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Coord.h"
#include <string>

class GameObject{
public:

	GameObject(Coord c, std::string name) : curCoord(c), gameObjectName(name){}
	virtual ~GameObject(){}
	std::string getName();
	Coord getCoord();

private:
	Coord curCoord;
	std::string gameObjectName;
};

inline
std::string GameObject::getName(){
	return gameObjectName;
}

inline
Coord GameObject::getCoord(){
	return curCoord;
}

#endif