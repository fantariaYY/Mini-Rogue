#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Coord.h"
#include "actor.h"
#include <vector>
#include <string>

class GameObject;

class Player :public Actor{
public:
	Player(Coord c);
	Player(Coord c, const Player &p);
	virtual ~Player();

	bool action(char input, std::string &outputMessage);
	void insertItem(GameObject* item);
	bool checkTeleport();	

	void outputPlayerData() const;
	bool isDead();

private:
	bool isTeleported = false;
	std::vector<GameObject*> itemList;

	char openInventory() const;
	std::string useItem(int type);
};

inline
bool Player::isDead(){
	return Player::curHitPoints <= 0;
}

#endif