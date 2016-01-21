#ifndef _GOBLINS_H_
#define _GOBLINS_H_

#include "Actor.h"
#include "Coord.h"
#include <vector>

class Dungeon;

class Goblins :public Actor{
public:
	Goblins(Coord c, int smell_d);
	virtual ~Goblins();

	void action(Coord playerCoord, Dungeon* dungeon, std::string &outputMessage);

private:
	int smellDistance;	//Furtherest distance that a goblin can smell the player
	int shortestDistance;	//Record the shortest distance to the player
	int bestPossibleDistance;	//The best possible distance is the Norm-1 distance of two actors
	bool findShortestPath(Coord startCoord, Coord destCoord, Coord nextMove, std::vector<Coord>& path, int depth, Dungeon* dungeon);
};

#endif