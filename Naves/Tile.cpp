#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {

}

void Tile::update()
{
    if (!destructible || !countdownStarted || destroyed)
        return;

    countdown++;

    if (countdown >= 120)
    {
        destroyed = true;
    }
}