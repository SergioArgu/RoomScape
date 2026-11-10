#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float x, float y, Game* game)
    : Enemy(x, y, BASIC, game)
{
}

Enemy::Enemy(string filename, float x, float y, Game* game)
    : Actor(filename, x, y, 36, 40, game)
{
    type = BASIC;
    target = nullptr;
    spawnTimer = 0;
    spawnInterval = 180;
    spawnRequested = false;
    speed = 0.7f;

    vx = 0;
    vy = 0;
    vxIntelligence = 0;

    state = game->stateMoving;

    aDying = new Animation("res/enemigo_morir.png",
        width, height, 280, 40, 6, 8, false, game);

    aMoving = new Animation("res/enemigo_movimiento2.png",
        width, height, 108, 40, 6, 3, true, game);

    animation = aMoving;
}

Enemy::Enemy(float x, float y, EnemyType type, Game* game)
    : Actor("res/enemigo.png", x, y, 36, 40, game)
{
    this->type = type;

    target = nullptr;
    spawnTimer = 0;
    spawnInterval = 180; // 6 segundos a 30 FPS
    spawnRequested = false;

    speed = (type == BASIC) ? 0.7f : 1.0f;

    vx = 0;
    vy = 0;
    vxIntelligence = 0;

    state = game->stateMoving;

    aDying = new Animation("res/enemigo_morir.png",
        width, height, 280, 40, 6, 8, false, game);

    aMoving = new Animation("res/enemigo_movimiento.png",
        width, height, 108, 40, 6, 3, true, game);

    animation = aMoving;
}

void Enemy::setTarget(Actor* target)
{
    this->target = target;
}

bool Enemy::consumeSpawnRequest()
{
    if (spawnRequested)
    {
        spawnRequested = false;
        return true;
    }

    return false;
}

void Enemy::update()
{
    if (state == game->stateDead)
        return;

    // Comprobar si está congelado
    if (frozen)
    {
        vx = 0;
        vy = 0;

        freezeTimer--;

        if (freezeTimer <= 0)
        {
            frozen = false;
        }

        animation->update();
        return;
    }

    bool endAnimation = animation->update();

    if (endAnimation && state == game->stateDying)
    {
        state = game->stateDead;
        vx = 0;
        vy = 0;
        return;
    }

    if (state == game->stateDying)
    {
        animation = aDying;
        vx = 0;
        vy = 0;
        return;
    }

    animation = aMoving;

    if (target == nullptr)
    {
        vx = 0;
        vy = 0;
        return;
    }

    float dx = target->x - x;
    float dy = target->y - y;

    float distance = sqrt(dx * dx + dy * dy);

    if (distance == 0)
    {
        vx = 0;
        vy = 0;
        return;
    }

    float direction = 1.0f;

    if (type == SPAWNER)
    {
        direction = -1.0f;

        spawnTimer++;

        if (spawnTimer >= spawnInterval)
        {
            spawnTimer = 0;
            spawnRequested = true;
        }
    }

    vx = (dx / distance) * speed * direction;
    vy = (dy / distance) * speed * direction;
    cout << "dy: " << dy << " | vy: " << vy << endl;
}

void Enemy::draw(float scrollX) {
    animation->draw(x - scrollX, y);
}

void Enemy::die()
{
    if (state == game->stateDying || state == game->stateDead)
        return;

    state = game->stateDying;
    animation = aDying;
    animation->currentFrame = 0;
}

void Enemy::impacted()
{
    if (state != game->stateDying &&
        state != game->stateDead)
    {
        die();
    }
}

void Enemy::freeze()
{
    if (state == game->stateDying ||
        state == game->stateDead)
        return;

    frozen = true;
    freezeTimer = freezeDuration;

    vx = 0;
    vy = 0;
}