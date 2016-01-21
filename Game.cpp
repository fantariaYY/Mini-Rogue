// Game.cpp
#include "stdafx.h"

#include "Game.h"
#include "Player.h"
#include "utilities.h"
#include "Dungeon.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance){
	g_dungeon = new Dungeon(0, goblinSmellDistance, NULL);
}

void Game::play()
{
	int playerResult = 0;
	char command = NULL;
	while (command != 'q'){
		//Output the dungeon
		clearScreen();
		g_dungeon->printDungeon();

		//If player is dead, end the game
		if (g_dungeon->getPlayer()->isDead()){
			break;
		}

		//Take in command and perform it
		command = getCharacter();
		playerResult = g_dungeon->performCommand(command);
		//If go down to the next level, generate a new dungeon
		if (playerResult == 1){
			Dungeon *tmp = g_dungeon;
			g_dungeon = new Dungeon(g_dungeon->getLevel() + 1, g_dungeon->getGoblinSmellDistance(), g_dungeon->getPlayer());
			delete tmp;
		}
		else{
			//If found the golden idol, won the game and break
			if (playerResult == 2){
				cout << "You picked up the golden idol" << endl;
				cout << "Congratulations, you won!" << endl;
				break;
			}
		}
		//Monster moves after player
		g_dungeon->monsterAction();
	}

	if (command == 'q'){
		return;
	}

	cout << "Press q to exit game." << endl;
	while (getCharacter() != 'q');
	
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
