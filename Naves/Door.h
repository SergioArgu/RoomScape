#pragma once

#include "Actor.h"

class Door : public Actor
{
public:
    bool open;

    Door(float x, float y, Game* game);

    void unlock();
};