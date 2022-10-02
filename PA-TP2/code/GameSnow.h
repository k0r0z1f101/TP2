#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Snowflake.h"
#include "Game.h"
#include "SnowflakePool.h"

//update, test collision and check if should delete the pool's snowflakes
template<typename T>
void TUpdatePool(T& pool, double& delta, Player& player)
{
	for(size_t i = 0; i < pool->getNbSnowflakes(); ++i)
	{
		pool->get(i).update(delta);
		pool->get(i).testCollision(player);
		if(pool->get(i).shouldDelete())
			pool->destroy(i);
	}
}

//render the pool's snowflakes
template<typename T>
void TRenderPool(T& pool, SDL_Renderer* renderer)
{
	for(size_t i = 0; i < pool->getNbSnowflakes(); ++i)
	{
		pool->get(i).render(renderer);
	}
}

class GameSnow : public Game
{
public:
    GameSnow();

    void handleInput(const SDL_Event& event) override;
    void update(unsigned long dt) override;
    void render(SDL_Renderer* renderer) const override;

    void init(int snowflakes);
    void addSnowflake();
    void addSnowflake(double x, double y);
private:
    bool m_pause;
    unsigned long presets[9] = {0, 1, 35000, 45000, 46000, 47000, 48000, 49000, 55000};

    Player p;

    std::unique_ptr<TSnowflakePool<Snowflake>> snowflakePool;
    std::unique_ptr<TSnowflakePool<SnowflakeNoContact>> snowflakeNoContactPool;
    std::unique_ptr<TSnowflakePool<SnowflakeRebound>> snowflakeReboundPool;
    std::unique_ptr<TSnowflakePool<SnowflakeSine>> snowflakeSinePool;
};
