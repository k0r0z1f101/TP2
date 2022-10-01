#pragma once

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "Snowflake.h"

class SnowflakeSine : public Snowflake	//12400 bytes (7 bytes available for packing)
{
public:
    SnowflakeSine(double x = RANDOM_START_X, double y = RANDOM_START_Y);

    void update(double dt) override;
private:
    double timeSinceStart;				//8 bytes, 12408 bytes (no packing possible)
};
