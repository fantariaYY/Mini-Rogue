#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "GameObject.h"

class Weapon : public GameObject{
public:
	Weapon(Coord c, int wType);
	virtual ~Weapon();
	std::string action();
	int getWeaponType() const;
	int getWeaponDexterity() const;
	int getWeaponDamage() const;

private:
	int type;
	int dexterityBonus;
	int damageAmount;
};

inline
int Weapon::getWeaponType() const{
	return type;
}

inline
int Weapon::getWeaponDexterity() const{
	return dexterityBonus;
}

inline
int Weapon::getWeaponDamage() const{
	return damageAmount;
}
#endif