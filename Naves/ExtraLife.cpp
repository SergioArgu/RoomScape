#include "ExtraLife.h"

ExtraLife::ExtraLife(float x, float y, Game* game)
    : Actor("res/recursos/pocion.png", x, y, 36, 40, game)
{
    collected = false;
    animation = nullptr;
}

void ExtraLife::update()
{
    if (collected)
        return;
}

void ExtraLife::draw(float scrollX)
{
    if (collected)
        return;

    Actor::draw(scrollX);
}