#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
	gamePad = SDL_GameControllerOpen(0);
}

void MenuLayer::init() {
	background = new Background(
		"res/recursos/menu.jpg",
		WIDTH * 0.5, HEIGHT * 0.5, game
	);

	buttonPlay = new Actor(
		"res/recursos/BotonJugar.jpg",
		WIDTH * 0.5, HEIGHT * 0.60,
		160, 50, game
	);

	buttonHelp = new Actor(
		"res/recursos/botonAyuda.jpg",
		WIDTH * 0.5, HEIGHT * 0.75,
		160, 50, game
	);
}

void MenuLayer::draw() {
	background->draw();
	buttonPlay->draw();
	buttonHelp->draw();

	SDL_RenderPresent(game->renderer);
}

void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		if (controlHelp) {
			game->layer = game->helpLayer;
			controlHelp = false;
		}
	}

	//procesar controles, solo tiene uno
	if (controlContinue) {
		// Cambia la capa
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // derecha
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE: // dispara
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {

	if (event.type == SDL_MOUSEBUTTONDOWN) {

		float motionX = event.button.x / game->scaleLower;
		float motionY = event.button.y / game->scaleLower;

		if (buttonPlay->containsPoint(motionX, motionY)) {
			controlContinue = true;
		}

		if (buttonHelp->containsPoint(motionX, motionY)) {
			controlHelp = true;
		}
	}
}

void MenuLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);

	if (buttonA) {
		controlContinue = true;
	}
}
