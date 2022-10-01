#pragma once

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "Snowflake.h"

class SnowflakeNoContact : public Snowflake		//12400 bytes
{
public:
    SnowflakeNoContact(double x = RANDOM_START_X, double y = RANDOM_START_Y);

    void collide(Player& o) override;
};
