#pragma once

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "Snowflake.h"

class SnowflakeRebound : public Snowflake	//12400 bytes (7 bytes available for packing)
{
public:
    SnowflakeRebound(double x = RANDOM_START_X, double y = RANDOM_START_Y);

    void update(double dt) override;
    void collide(Player& o) override;
private:
    bool alreadyHit;						//1 byte, 12408 bytes (12400 packed)
    void rebound();
};
