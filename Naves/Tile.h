#pragma once

#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);

	bool destructible = false;
	bool countdownStarted = false;
	bool destroyed = false;
	int countdown = 0;

	void update();

	bool jumpPlatform = false;

};
