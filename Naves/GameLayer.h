#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include <list>
#include "Audio.h" 
#include "Tile.h"
#include "Pad.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include "Space.h" // importar
#include "Item.h"
#include "Door.h"
#include "ExtraLife.h"

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	Audio* audioBackground;
	Text* textPoints;
	Text* textItems;
	Text* textLifes;
	int points;


	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	
	Actor* message;
	bool pause;

	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;
	Space* space;
	float scrollX;
	int mapWidth;
	list<Tile*> tiles;




	list<Item*> items;
	int itemsCollected = 0;

	bool hasKey = false;
	Door* door;
	//door = nullptr;
	list<Tile*> floors;
	list<Tile*> walls;
	list<Tile*> decorations;

	bool attackRequested = false;
	int attackCooldown = 0;
	float attackRange = 65.0f;
	list<ExtraLife*> extraLives;
};
