#include "Door.h"

Door::Door(float x, float y, Game* game)
    : Actor("res/nivel1/puerta_madera.png", x, y, 40, 40, game)
{
    open = false;
}

void Door::unlock()
{
    if (!open)
    {
        open = true;
        texture = game->getTexture("res/nivel1/entrada_ruinas.png");
    }
}