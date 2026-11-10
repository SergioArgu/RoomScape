#pragma once

#include "Actor.h"
#include "Animation.h"

class Item : public Actor
{
public:
    bool collected;
    Animation* animation;

    Item(float x, float y, Game* game);

    void update();
    void draw(float scrollX) override;
};