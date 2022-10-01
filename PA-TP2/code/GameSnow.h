#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Snowflake.h"
#include "Game.h"
#include "SnowflakePool.h"

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

    std::unique_ptr<SnowflakePool<Snowflake>> snowflakePool;
    std::unique_ptr<SnowflakePool<SnowflakeNoContact>> snowflakeNoContactPool;
    std::unique_ptr<SnowflakePool<SnowflakeRebound>> snowflakeReboundPool;
    std::unique_ptr<SnowflakePool<SnowflakeSine>> snowflakeSinePool;
};
