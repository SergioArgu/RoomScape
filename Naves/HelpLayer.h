#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "Text.h"

class HelpLayer : public Layer
{
public:
    HelpLayer(Game* game);

    void init() override;
    void draw() override;
    void processControls() override;

    void keysToControls(SDL_Event event);
    void mouseToControls(SDL_Event event);
    void gamePadToControls(SDL_Event event);

    Background* background;
    Text* title;
    Text* explanation;
    Text* controls;
    Actor* buttonBack;

    bool controlBack = false;
    SDL_GameController* gamePad;
};