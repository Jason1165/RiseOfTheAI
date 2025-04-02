#pragma once
#include "Scene.h"

class LevelC : public Scene
{
public:
    int LEVELC_ENEMY_COUNT = 36;

    ~LevelC();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};