#include <cassert>
#include <cmath>
#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "Constants.h"
#include "Player.h"

Player::Player(double x, double y) :
    GameObject{x, y},
    inputs{false},
    isJumping{false}
{
	//std::cout << sizeof(Player) << std::endl;
    w = 70;
    h = 50;

    color_r = 0;
    color_g = 0.63;
    color_b = 0.8;
    color_a = 1;

    ay = +1000;
}

void Player::update(double dt)
{
    // Process input
    ax = inputs.left * -1000 + inputs.right * 1000;

    if(!isJumping && inputs.jump) {
        vy = -600;
        isJumping = true;
    }

    if(inputs.down) {
        if(h == 50)
            y += 25;
        h = 25;
        ay = +1500;
    } else {
        if(h == 25)
            y -= 25;
        h = 50;
        ay = +1000;
    }

    GameObject::update(dt);

    // Damping
    if(!inputs.left && !inputs.right) {
        double sign_vx = copysign(1, vx);

        vx -= dt * sign_vx * 300;

        // Sign change : set to zero
        if(copysign(1, vx) != sign_vx)
            vx = 0;
    }

    if(vx > 350)
        vx = 350;
    if(vx < -350)
        vx = -350;

    if(x < 0) {
        x = 0;
        vx *= -0.5;
    }

    if(x + w > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - w;
        vx *= -0.5;
    }

    if(y + h > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - h;
        vy = 0;
        isJumping = false;
    }
}

void Player::render(SDL_Renderer* renderer) const
{
    GameObject::render(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r;

    int offset = 0;

    if(vx > 0)
        offset = 3;
    else if(vx < 0)
        offset = -3;

    // Eyes
    r.w = 6;
    r.h = 6;

    // Left eye
    r.x = (int) (x + w/4.0 - 3) + offset;
    r.y = (int) (y + h/3.0 - 3);
    SDL_RenderFillRect(renderer, &r);

    // Right eye
    r.x = (int) (x + 3*w/4.0 - 3) + offset;
    SDL_RenderFillRect(renderer, &r);

    // Mouth
    int mouthY = y + 3*h/4.0;
    SDL_RenderDrawLine(renderer, x + w/4.0, mouthY, x + 3*w/4.0, mouthY);
}

void Player::collide(Player& o)
{
    assert(0);
}

