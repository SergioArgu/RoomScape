#pragma once

#include "Actor.h"
#include "Animation.h"

enum EnemyType
{
    BASIC,
    SPAWNER
};

class Enemy : public Actor
{
public:
    Enemy(float x, float y, Game* game);
    Enemy(string filename, float x, float y, Game* game);
    Enemy(float x, float y, EnemyType type, Game* game);

    void draw(float scrollX = 0) override;
    void update();

    void impacted();
    void die();

    void setTarget(Actor* target);

    bool consumeSpawnRequest();

    float vxIntelligence;
    int state;

    Animation* aDying;
    Animation* aMoving;
    Animation* animation;

    bool diesWhenJumpedOn = false;

    bool frozen = false;
    int freezeTimer = 0;
    int freezeDuration = 90; // 3 segundos a 30 FPS
    void freeze();

private:
    EnemyType type;
    Actor* target;

    int spawnTimer;
    int spawnInterval;
    bool spawnRequested;

    float speed;
};