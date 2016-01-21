#include "stdafx.h"

#include "Bogeymen.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "utilities.h"
#include <cmath>

using namespace std;

enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };

using namespace std;

Bogeymen::Bogeymen(Coord c) : Actor("Bogeyman", c, randInt(6) + 5, 2, randInt(2) + 2, randInt(2) + 2){
	changeWieldingWeapon(new Weapon(c, shortSword));
}

//Actions performed by bogeymen
void Bogeymen::action(Coord playerCoord, Dungeon* dungeon, string &outputMessage){
	//If asleep, pass the turn
	if (sleepPass()){
		return;
	}

	int dist = abs(getCoord().x - playerCoord.x) + abs(getCoord().y - playerCoord.y);
	//If distance <= 5, try to reach player
	if (dist <= 5){
		//If distance is 1, can reach player, attack
		if (dist == 1){
			attack((Actor*)(dungeon->getPlayer()), outputMessage);
		}
		else{
			//Either close in by row or by column
			if (getCoord().x < playerCoord.x){
				if (dungeon->canWalk(Coord(getCoord().x + 1, getCoord().y))){
					setCoord(Coord(getCoord().x + 1, getCoord().y));
					return;
				}
			}
			else{
				if (getCoord().x > playerCoord.x){
					if (dungeon->canWalk(Coord(getCoord().x - 1, getCoord().y))){
						setCoord(Coord(getCoord().x - 1, getCoord().y));
						return;
					}

				}
			}

			if (getCoord().y < playerCoord.y){
				if (dungeon->canWalk(Coord(getCoord().x, getCoord().y + 1))){
					setCoord(Coord(getCoord().x, getCoord().y + 1));
					return;
				}
			}
			else{
				if (getCoord().y > playerCoord.y){
					if (dungeon->canWalk(Coord(getCoord().x, getCoord().y - 1))){
						setCoord(Coord(getCoord().x, getCoord().y - 1));
						return;
					}
				}
			}
		}
	}
}

Bogeymen::~Bogeymen(){
}