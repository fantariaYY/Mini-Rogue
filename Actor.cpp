#include "stdafx.h"

#include "Actor.h"
#include "Weapon.h"
#include "utilities.h"

#include <iostream>
#include <algorithm>

using namespace std;

enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };

Actor::Actor(std::string name, Coord c, int hp, int ap, int sp, int dp) :actorName(name), curCoord(c), curHitPoints(hp),
maxHitPoints(hp), armorPoints(ap), strengthPoints(sp), dexterityPoints(dp), sleepTime(0){
}

Actor::Actor(const Actor &a) : actorName(a.actorName), curCoord(a.curCoord), curHitPoints(a.curHitPoints),
maxHitPoints(a.maxHitPoints), armorPoints(a.armorPoints), strengthPoints(a.strengthPoints), dexterityPoints(a.dexterityPoints), sleepTime(a.sleepTime){
}

Actor::~Actor(){
	if (wieldingWeapon != NULL){
		delete wieldingWeapon;
	}
}

//Set the coordinate to c
void Actor::setCoord(Coord c){
	curCoord.x = c.x;
	curCoord.y = c.y;
}

//Get the coordinate of the actor
Coord Actor::getCoord() const{
	return curCoord;
}

//Get the wielding weapon of this actor
Weapon* Actor::getWieldingWeapon() const{
	return wieldingWeapon;
}

//get the name of this actor
string Actor::getName() const{
	return actorName;
}

//If actor is asleep, pass the turn and reduce the sleep time by 1
bool Actor::sleepPass(){
	if (sleepTime > 0){
		sleepTime--;
		return true;
	}
	else{
		return false;
	}
}

void Actor::regenerateHealth(){
	if (trueWithProbability(0.1)){
		if (curHitPoints < maxHitPoints){
			curHitPoints++;
		}
	}
}

//Change the wielding weapon of the actor
void Actor::changeWieldingWeapon(Weapon* weapon){
	wieldingWeapon = weapon;
}

//Let the current actor attack an opponent
bool Actor::attack(Actor* opponent, string &message){
	//Calculate the attacker points and defender points
	int attackerPoints = dexterityPoints + wieldingWeapon->getWeaponDexterity();
	int defenderPoints = opponent->dexterityPoints + opponent->armorPoints;

	//If hit, calculate the damage amount
	if (randInt(attackerPoints) >= randInt(defenderPoints)){
		int damageAmount = randInt(strengthPoints + wieldingWeapon->getWeaponDamage());
		opponent->curHitPoints -= damageAmount;

		//If opponent's hit point is reduced below zero, generate the corresponding message
		if (opponent->curHitPoints <= 0){
			message = getName() + wieldingWeapon->action() + opponent->getName() + " dealing a final blow.";
			//return true indicates killed you opponent
			return true;
		}

		//If wielding magic fangs of sleep, can make opponent sleep
		if (wieldingWeapon->getWeaponType() == magicFangsOfSleep){
			if (trueWithProbability(0.2)){
				opponent->sleepTime = max(opponent->sleepTime, randInt(5) + 2);
				message = getName() + wieldingWeapon->action() + opponent->getName() + " and hits, putting " + opponent->getName() + " to sleep.";
				return false;
			}
		}

		message = getName() + wieldingWeapon->action() + opponent->getName() + " and hits.";
	}
	else{
		message = getName() + wieldingWeapon->action() + opponent->getName() + " and misses.";
	}

	return false;
}