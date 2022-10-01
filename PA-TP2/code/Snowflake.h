#pragma once

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "GameObject.h"
#include "Player.h"

class Snowflake : public GameObject				//12400 bytes
{
public:
    Snowflake(double x = RANDOM_START_X, double y = RANDOM_START_Y);
    void init(double x, double y = -10);

    void update(double dt) override;
    virtual void collide(Player& o) override;
};
