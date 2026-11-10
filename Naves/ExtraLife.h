#pragma once

#include "Actor.h"
#include "Animation.h"

class ExtraLife : public Actor
{
public:
    bool collected;
    Animation* animation;

    ExtraLife(float x, float y, Game* game);

    void update();
    void draw(float scrollX = 0) override;
};