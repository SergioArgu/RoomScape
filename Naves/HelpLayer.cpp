#include "HelpLayer.h"

HelpLayer::HelpLayer(Game* game) : Layer(game)
{
    gamePad = SDL_GameControllerOpen(0);
    init();
}

void HelpLayer::init()
{
    background = new Background(
        "res/recursos/mazmorra.png",
        WIDTH * 0.5, HEIGHT * 0.5, game
    );

    title = new Text("AYUDA", WIDTH * 0.5, 35, game);

    explanation = new Text(
        "Recoge llaves y encuentra la puerta.",
        WIDTH * 0.5, 100, game);

    controls = new Text(
        "WASD: Moverse ESPACIO: Disparar E: Atacar",
        WIDTH * 0.5, 190, game);

    buttonBack = new Actor(
        "res/recursos/botonAtras.jpg",
        WIDTH * 0.5, 290, 120, 40, game
    );
}

void HelpLayer::draw()
{
    background->draw();
    title->draw();
    explanation->draw();
    controls->draw();
    buttonBack->draw();

    SDL_RenderPresent(game->renderer);
}

void HelpLayer::processControls()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_CONTROLLERBUTTONDOWN ||
            event.type == SDL_CONTROLLERAXISMOTION)
            game->input = game->inputGamePad;

        if (event.type == SDL_KEYDOWN)
            game->input = game->inputKeyboard;

        if (event.type == SDL_MOUSEBUTTONDOWN)
            game->input = game->inputMouse;

        if (game->input == game->inputKeyboard)
            keysToControls(event);

        if (game->input == game->inputMouse)
            mouseToControls(event);

        if (game->input == game->inputGamePad)
            gamePadToControls(event);
    }

    if (controlBack)
    {
        game->layer = game->menuLayer;
        controlBack = false;
    }
}

void HelpLayer::keysToControls(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN &&
        event.key.keysym.sym == SDLK_ESCAPE)
    {
        controlBack = true;
    }
}

void HelpLayer::mouseToControls(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        float x = event.button.x / game->scaleLower;
        float y = event.button.y / game->scaleLower;

        if (buttonBack->containsPoint(x, y))
            controlBack = true;
    }
}

void HelpLayer::gamePadToControls(SDL_Event event)
{
    if (event.type == SDL_CONTROLLERBUTTONDOWN &&
        event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
    {
        controlBack = true;
    }
}