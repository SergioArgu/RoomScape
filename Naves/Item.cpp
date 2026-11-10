#include "Item.h"

Item::Item(float x, float y, Game* game)
    : Actor("res/llave.png", x, y, 36, 40, game)
{
    collected = false;

    animation = new Animation(
        "res/recursos/llave.png",
        width, height,
        256, 32,
        5, 8,
        true,
        game
    );
}

void Item::update()
{
    if (collected)
        return;

    if (animation != nullptr)
        animation->update();
}

void Item::draw(float scrollX)
{
    if (collected)
        return;

    if (animation != nullptr)
        animation->draw(x - scrollX, y);
    else
        Actor::draw(scrollX);
}