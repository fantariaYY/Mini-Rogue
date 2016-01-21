#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Coord.h"
#include <string>

class Weapon;
class Coord;
class Dungeon;

class Actor{
public:
	Actor(std::string name, Coord c, int hp, int ap, int sp, int dp);
	Actor(const Actor &a);
	virtual ~Actor();

	void setCoord(Coord c);
	void changeWieldingWeapon(Weapon* weapon);
	bool attack(Actor* opponent, std::string &message);
	Coord getCoord() const;
	Weapon* getWieldingWeapon() const;
	std::string getName() const;
	bool sleepPass();
	void regenerateHealth();

protected:
	int curHitPoints;
	int maxHitPoints;
	int armorPoints;
	int strengthPoints;
	int dexterityPoints;
	int sleepTime;

private:
	Coord curCoord;
	Weapon* wieldingWeapon;
	std::string actorName;
};

#endif