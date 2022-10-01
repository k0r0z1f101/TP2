#include <iostream>
#include <memory>
#include <algorithm>

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__
#include <SDL2/SDL.h>
#endif

#include "Constants.h"
#include "GameSnow.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"

using namespace std;

GameSnow::GameSnow() :
    m_pause(false),
    p(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
{
    init(presets[0]);
}

void GameSnow::init(int n)
{
    cout << "Init with " << n << " particles" << endl;

    snowflakePool = make_unique<SnowflakePool<Snowflake>>();
    snowflakeNoContactPool = make_unique<SnowflakePool<SnowflakeNoContact>>();
    snowflakeReboundPool = make_unique<SnowflakePool<SnowflakeRebound>>();
    snowflakeSinePool = make_unique<SnowflakePool<SnowflakeSine>>();

    for(int i=0; i<n; i++) {
        double x = rand()/(double)RAND_MAX * SCREEN_WIDTH;
        double y = rand()/(double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;

        addSnowflake(x, y);
    }
}

void GameSnow::addSnowflake()
{
    // Default : top of the screen
    addSnowflake(rand()/(double)RAND_MAX * SCREEN_WIDTH, -10);
}

void GameSnow::addSnowflake(double x, double y)
{
    int rnd = rand();
    if(rnd < RAND_MAX / 10)
    {
        snowflakeReboundPool->spawn();
    }
    else if(rnd < RAND_MAX / 5 * 2)
    {
        snowflakeNoContactPool->spawn();
    }
    else if(rnd < RAND_MAX / 2)
    {
        snowflakeSinePool->spawn();
    }
    else
    {
        snowflakePool->spawn();
    }
}

void GameSnow::handleInput(const SDL_Event& event)
{
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                p.x = x;
                p.y = y;
            }
            break;
    case SDL_KEYUP:
        switch(event.key.keysym.sym) {
        case SDLK_LEFT:
            p.inputs.left = false;
            break;
        case SDLK_RIGHT:
            p.inputs.right = false;
            break;
        case SDLK_DOWN:
            p.inputs.down = false;
            break;
        case SDLK_UP:
        case SDLK_SPACE:
            p.inputs.jump = false;
            break;
        }
        break;

    case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
        case SDLK_LEFT:
            p.inputs.left = true;
            break;
        case SDLK_RIGHT:
            p.inputs.right = true;
            break;
        case SDLK_DOWN:
            p.inputs.down = true;
            break;
        case SDLK_UP:
        case SDLK_SPACE:
            p.inputs.jump = true;
            break;

            // Pause
        case SDLK_p:
            m_pause = !m_pause;
            break;

        case SDLK_1:
        case SDLK_2:
        case SDLK_3:
        case SDLK_4:
        case SDLK_5:
        case SDLK_6:
        case SDLK_7:
        case SDLK_8:
        case SDLK_9:
            init(presets[event.key.keysym.sym - SDLK_1]);
            break;

        case SDLK_ESCAPE:
            keepPlaying = false;
            break;
        }
    }
}

void GameSnow::update(unsigned long dt)
{

    if(m_pause) return;

    double delta_t = dt / 1000.0;

    // Physics
    p.update(delta_t);

    for(size_t i = 0; i < snowflakePool->getNbSnowflakes(); ++i)
    {
    	snowflakePool->get(i).update(delta_t);
    	snowflakePool->get(i).testCollision(p);
    	if(snowflakePool->get(i).shouldDelete())
    		snowflakePool->destroy(i);
    }
    for(size_t i = 0; i < snowflakeNoContactPool->getNbSnowflakes(); ++i)
    {
    	snowflakeNoContactPool->get(i).update(delta_t);
    	snowflakeNoContactPool->get(i).testCollision(p);
    	if(snowflakeNoContactPool->get(i).shouldDelete())
    		snowflakeNoContactPool->destroy(i);
    }
    for(size_t i = 0; i < snowflakeReboundPool->getNbSnowflakes(); ++i)
    {
    	snowflakeReboundPool->get(i).update(delta_t);
    	snowflakeReboundPool->get(i).testCollision(p);
    	if(snowflakeReboundPool->get(i).shouldDelete())
    		snowflakeReboundPool->destroy(i);
    }
    for(size_t i = 0; i < snowflakeSinePool->getNbSnowflakes(); ++i)
    {
    	snowflakeSinePool->get(i).update(delta_t);
    	snowflakeSinePool->get(i).testCollision(p);
    	if(snowflakeSinePool->get(i).shouldDelete())
    		snowflakeSinePool->destroy(i);
    }
}

void GameSnow::render(SDL_Renderer* renderer) const
{
    // -- Clear screen --
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    // Draw particles
    p.render(renderer);

    for(size_t i = 0; i < snowflakePool->getNbSnowflakes(); ++i)
    {
    	snowflakePool->get(i).render(renderer);
    }
    for(size_t i = 0; i < snowflakeNoContactPool->getNbSnowflakes(); ++i)
    {
    	snowflakeNoContactPool->get(i).render(renderer);
    }
    for(size_t i = 0; i < snowflakeReboundPool->getNbSnowflakes(); ++i)
    {
    	snowflakeReboundPool->get(i).render(renderer);
    }
    for(size_t i = 0; i < snowflakeSinePool->getNbSnowflakes(); ++i)
    {
    	snowflakeSinePool->get(i).render(renderer);
    }

    SDL_RenderPresent(renderer);
}
