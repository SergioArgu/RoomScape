#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
    : Actor(filename, x, y, WIDTH, HEIGHT, game)
{
    vx = 0;
    backgroundAux = nullptr;
}

void Background::update()
{
    // El fondo permanece quieto
}

void Background::draw(float scrollX)
{
    Actor::draw();
}