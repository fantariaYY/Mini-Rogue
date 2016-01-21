// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Dungeon;
class Player;
// You may add data members and other member functions to this class.

class Game
{
public:
	Game(int goblinSmellDistance);
	void play();
private:
	Dungeon* g_dungeon;
};

#endif // GAME_INCLUDED
