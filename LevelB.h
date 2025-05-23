#pragma once
#include "Scene.h"

class LevelB : public Scene
{
public:
    int LEVELB_ENEMY_COUNT = 12;

    ~LevelB();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};