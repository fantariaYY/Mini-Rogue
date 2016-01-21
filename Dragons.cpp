#include "stdafx.h"

#include "Dragons.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "utilities.h"
#include <cmath>

using namespace std;

enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };


using namespace std;

Dragons::Dragons(Coord c) : Actor("Dragon", c, randInt(6) + 20, 4, 4, 4){
	changeWieldingWeapon(new Weapon(c, longSword));
}

//Actions performed by dragons
void Dragons::action(Coord playerCoord, Dungeon* dungeon, string &outputMessage){
	//Possible to regenerate health
	regenerateHealth();

	//If asleep, pass the turn
	if (sleepPass()){
		return;
	}

	//Never moves, attacks when can reach player
	int dist = abs(getCoord().x - playerCoord.x) + abs(getCoord().y - playerCoord.y);
	if (dist == 1){
		attack((Actor*)(dungeon->getPlayer()), outputMessage);
	}
}

Dragons::~Dragons(){
}