#include "stdafx.h"

#include "Weapon.h"
#include <iostream>

using namespace std;

enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };
string weaponName[5] = { "mace", "short sword", "long sword", "magic axe", "magic fangs of sleep" };

//Initialization for the weapon attributes
Weapon::Weapon(Coord c, int wType) : GameObject(c, weaponName[wType]){
	type = wType;

	switch (type){
	case mace:
		dexterityBonus = 0;
		damageAmount = 2;
		break;
	case shortSword:
		dexterityBonus = 0;
		damageAmount = 2;
		break;
	case longSword:
		dexterityBonus = 2;
		damageAmount = 4;
		break;
	case magicAxe:
		dexterityBonus = 5;
		damageAmount = 5;
		break;
	case magicFangsOfSleep:
		dexterityBonus = 3;
		damageAmount = 2;
		break;
	}
}

//Corresponding action when used by actors
std::string Weapon::action(){
	switch (type){
	case mace:
		return "swings mace at";
	case shortSword:
		return " slashes short sword at ";
	case longSword:
		return " swings long sword at ";
	case magicAxe:
		return " chops magic axe at ";
	case magicFangsOfSleep:
		return " strikes magic fangs at ";
	default:
		return "";
	}
}

Weapon::~Weapon(){
}