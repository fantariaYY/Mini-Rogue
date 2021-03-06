#include "stdafx.h"

#include "utilities.h"
#include "Player.h"
#include "Weapon.h"
#include "Scroll.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum ItemType :int{weapon, scroll};
enum WeaponType : int{ mace, shortSword, longSword, magicAxe, magicFangsOfSleep };
enum ScrollType : int { teleporation, improveArmor, raiseStrength, enhanceHealth, enhanceDexterity };

//Constructor
Player::Player(Coord c) :Actor("Player", c, 20, 2, 2, 2){
	GameObject* initialWeapon = new Weapon(c, shortSword);
	itemList.push_back(initialWeapon);
	changeWieldingWeapon((Weapon*)itemList[0]);
}

//Copy constructor
Player::Player(Coord c, const Player &p) :Actor(p){
	setCoord(c);
	for (unsigned int i = 0; i < p.itemList.size(); i++){
		itemList.push_back(p.itemList[i]);
	}

	changeWieldingWeapon(p.getWieldingWeapon());
}

Player::~Player(){
	while (!itemList.empty()){
		delete itemList[itemList.size() - 1];
		itemList.pop_back();
	}
}

//Perform action according to the command given
bool Player::action(char input, string &outputMessage){

	switch (input){
	case ARROW_UP:
		setCoord(Coord(getCoord().x, getCoord().y - 1));
		break;
	case ARROW_DOWN:
		setCoord(Coord(getCoord().x, getCoord().y + 1));
		break;
	case ARROW_LEFT:
		setCoord(Coord(getCoord().x - 1, getCoord().y));
		break;
	case ARROW_RIGHT:
		setCoord(Coord(getCoord().x + 1, getCoord().y));
		break;
	case 'g':
		if (itemList.size() > 25){
			outputMessage = "Your knapsack is full; you can't pick that up.";
			return false;
		}
		else{
			return true;	//return true indicates trying to pick up an item
		}
	case 'i':
		openInventory();
		break;
	case 'c':			//Cheats :P
		maxHitPoints = 50;
		curHitPoints = 50;
		strengthPoints = 9;
		break;
	case 'w':
		outputMessage = useItem(weapon);
		break;
	case 'r':
		outputMessage = useItem(scroll);
		break;
	default:
		break;
	}

	return false;
}

//Insert an item into the inventory
void Player::insertItem(GameObject* item){
	itemList.push_back(item);
}

//Check if the player used a teleport scroll
bool Player::checkTeleport(){
	if (isTeleported){
		isTeleported = false;
		return true;
	}

	return false;
}

//Output the player information
void Player::outputPlayerData() const{
	cout << ", Hit points: " << curHitPoints;
	cout << ", Armor: " << armorPoints;
	cout << ", Strength: " << strengthPoints;
	cout << ", Dexterity: " << dexterityPoints << endl << endl;
}

//Open the inventory
char Player::openInventory() const{
	clearScreen();
	cout << "Inventory:" << endl;
	for (unsigned int i = 0; i < itemList.size(); i++){
		cout << " " << (char)('a' + i) << ". ";
		cout << itemList[i]->getName() << endl;
	}

	return getCharacter();
}

//Use one of the item and return the correct string message
string Player::useItem(int type){
	unsigned int itemNumber = openInventory() - 'a';
	if (itemNumber < 0 || itemNumber >= itemList.size()){
		return "";
	}

	//If try to wield a weapon, check if it's a weapon
	if (type == weapon){
		Weapon* wptr = dynamic_cast<Weapon*>(itemList[itemNumber]);
		if (wptr == nullptr){
			return "You can't wield a " + itemList[itemNumber]->getName();
		}
		else{
			changeWieldingWeapon((Weapon*)(itemList[itemNumber]));
			return "";
		}
	}
	else{
		//If try to read a scroll, check if it's a scroll
		Scroll* sptr = dynamic_cast<Scroll*>(itemList[itemNumber]);
		if (sptr == nullptr){
			return  "You can't read a " + itemList[itemNumber]->getName();
		}
		else{
			Scroll* usedScroll = (Scroll*)(itemList[itemNumber]);
			switch (usedScroll->getScrollType()){
			case teleporation:
				isTeleported = true;
				break;
			case improveArmor:
				armorPoints = min(99, armorPoints + randInt(3) + 1);
				break;
			case raiseStrength:
				strengthPoints = min(99, strengthPoints + randInt(3) + 1);
				break;
			case enhanceHealth:
				maxHitPoints = min(99, maxHitPoints + randInt(6) + 3);
				break;
			case enhanceDexterity:
				dexterityPoints = min(99, dexterityPoints + 1);
				break;
			}
			//Delete the scroll after reading it
			itemList.erase(itemList.begin() + itemNumber);

			return "You used a " + usedScroll->getName() + ".\n" + usedScroll->action();
		}
	}
}
