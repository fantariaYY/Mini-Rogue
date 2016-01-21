#include "stdafx.h"

#include "Goblins.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "utilities.h"
#include <cmath>
#include <vector>

using namespace std;

const char TMP_WALL = '!';
const char WALL = '#';
const char FINAL_ROOM = ' ';

enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };

using namespace std;

Goblins::Goblins(Coord c, int smell_d) : Actor("Goblin", c, randInt(6) + 15, 1, 3, 1){
	smellDistance = smell_d;
	shortestDistance = INT_MAX;
	bestPossibleDistance = INT_MAX;
	changeWieldingWeapon(new Weapon(c, shortSword));
}

Goblins::~Goblins(){
}

//Actions performed by goblins
void Goblins::action(Coord playerCoord, Dungeon* dungeon, string &outputMessage){
	//If asleep, pass the turn
	if (sleepPass()){
		return;
	}

	//Find the current best possible distance in order to exit recursive
	bestPossibleDistance = abs(getCoord().x - playerCoord.x) + abs(getCoord().y - playerCoord.y);
	//If can smell player, try to find the optimal path
	if (bestPossibleDistance <= smellDistance){
		//If can reach player, attack
		if (bestPossibleDistance == 1){
			attack((Actor*)(dungeon->getPlayer()), outputMessage);
		}
		else{
			vector<Coord> minPath;
			Coord nextMove;
			shortestDistance = INT_MAX;
			if (findShortestPath(getCoord(), playerCoord, Coord(0, 0), minPath, 0, dungeon)){
				setCoord(Coord(getCoord().x + minPath[minPath.size() - 1].x, getCoord().y + minPath[minPath.size() - 1].y));
			}
		}
	}
}

bool Goblins::findShortestPath(Coord startCoord, Coord destCoord, Coord nextMove, vector<Coord>& path, int depth, Dungeon* dungeon){
	//If can't go through, return false
	if (dungeon->getFloor(startCoord) != FINAL_ROOM){
		return false;
	}

	//If reached destination, current distance is shorter, return true, else return false
	if (startCoord == destCoord){
		if (shortestDistance > depth){
			shortestDistance = depth;
			path.push_back(nextMove);
			return true;
		}
		else{
			return false;
		}
	}

	//Make sure no circle exists
	dungeon->setFloor(startCoord, TMP_WALL);

	//Find the current distance
	int dist = abs(destCoord.x - startCoord.x) + abs(destCoord.y - startCoord.y);

	//If player out of reach, can't be smelled, return false
	if (dist + depth > smellDistance){
		dungeon->setFloor(startCoord, FINAL_ROOM);
		return false;
	}

	//Recursively find the best path from east, west, south and north
	bool hasEast = false, hasWest = false, hasSouth = false, hasNorth = false;

	//If the shortest distance is already the best possible, no need to perform recursion, return true
	//Since each recursive performance may find the best result, have to check for each recursion
	if (bestPossibleDistance != shortestDistance){
		hasEast = findShortestPath(Coord(startCoord.x + 1, startCoord.y), destCoord, Coord(1, 0), path, depth + 1, dungeon);
	}
	else{
		if (depth != 0)
			path.push_back(nextMove);
		dungeon->setFloor(startCoord, FINAL_ROOM);
		return true;
	}

	if (bestPossibleDistance != shortestDistance){
		hasWest = findShortestPath(Coord(startCoord.x - 1, startCoord.y), destCoord, Coord(-1, 0), path, depth + 1, dungeon);
	}
	else{
		if (depth != 0)
			path.push_back(nextMove);
		dungeon->setFloor(startCoord, FINAL_ROOM);
		return true;
	}

	if (bestPossibleDistance != shortestDistance){
		hasSouth = findShortestPath(Coord(startCoord.x, startCoord.y + 1), destCoord, Coord(0, 1), path, depth + 1, dungeon);
	}
	else{
		if (depth != 0)
			path.push_back(nextMove);
		dungeon->setFloor(startCoord, FINAL_ROOM);
		return true;
	}

	if (bestPossibleDistance != shortestDistance){
		hasNorth = findShortestPath(Coord(startCoord.x, startCoord.y - 1), destCoord, Coord(0, -1), path, depth + 1, dungeon);
	}
	else{
		if (depth != 0)
			path.push_back(nextMove);
		dungeon->setFloor(startCoord, FINAL_ROOM);
		return true;
	}

	//If found an possible optimal path, push the step into the vector
	//When depth = 0, the step is (0, 0), no need to push it in
	if ((hasEast || hasWest || hasSouth || hasNorth == true) && depth != 0){
		path.push_back(nextMove);
	}

	//Change the floor back so that other paths may pass it
	dungeon->setFloor(startCoord, FINAL_ROOM);

	return hasEast || hasWest || hasSouth || hasNorth;
}