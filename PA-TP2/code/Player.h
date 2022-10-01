#pragma once

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include <string>

#include "GameObject.h"

class Player : public GameObject							//12400 bytes
{
public:
    Player(double x, double y);

    void update(double dt) override;
    void render(SDL_Renderer* renderer) const override;

    void collide(Player& o) override;

    struct Inputs {											//4 bytes
        bool left;
        bool right;
        bool down;
        bool jump;
    } inputs;
private:
    bool isJumping;											//1 byte
};
