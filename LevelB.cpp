/**
* Author: Jason Lin
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 40
#define LEVEL_HEIGHT 40

constexpr char TILE_FILEPATH[] = "assets/sprites/updated_cake.png";
constexpr char PLAYER_FILEPATH[] = "assets/sprites/char_run.png";
constexpr char PIG_FILEPATH[] = "assets/sprites/angry_pig.png";
constexpr char CHICKEN_FILEPATH[] = "assets/sprites/chicken.png";
constexpr char BAT_FILEPATH[] = "assets/sprites/bat.png";
constexpr char BEE_FILEPATH[] = "assets/sprites/bee.png";
constexpr char FONT_FILEPATH[] = "assets/sprites/modified_atari_font.png";

constexpr char BGM_FILEPATH[] = "assets/audio/Cupids-Revenge.mp3";
constexpr char JUMP_FILEPATH[] = "assets/audio/187024__lloydevans09__jump2.wav";
constexpr char DEATH_FILEPATH[] = "assets/audio/157218__adamweeden__video-game-die-or-lose-life.wav";
constexpr char CHICKEN_SOUND[] = "assets/audio/475733__dogwomble__rubber-chicken-2.wav";
constexpr char PIG_SOUND[] = "assets/audio/449986__reinsamba__pig_grunt.wav";
constexpr char BAT_SOUND[] = "assets/audio/468442__breviceps__video-game-squeak.wav";
constexpr char BEE_SOUND[] = "assets/audio/390733__funwithsound__buzzing-insect-short.wav";

glm::vec3 LEVELB_END_FLAG = glm::vec3(17.0f, -19.0f, 0.0f);


unsigned int LEVELB_DATA[] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,8,3,3,9,0,0,0,0,8,3,3,9,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,5,6,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,8,3,3,9,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,7,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,8,3,3,9,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,2,3,3,4,0,0,0,0,2,3,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,3,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,1,1,1,1,
    1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
    1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

LevelB::~LevelB()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelB::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture(TILE_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 8, 7);

    // -- PLAYER -- //
    std::vector<std::vector<int>> player_walking_animation =
    {
        { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35 }, // LEFT
        { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 }, // RIGHT
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    GLuint player_texture_id = Utility::load_texture(PLAYER_FILEPATH);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        2.0f,                      // speed
        acceleration,              // acceleration
        3.75f,                     // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        18,                        // animation frame amount
        0,                         // current animation index
        2,                         // animation column amount
        18,                        // animation row amount
        1.0f,                      // width
        1.0f,                      // height
        PLAYER
    );

    m_game_state.player->set_position(glm::vec3(4.5f, -32.0f, 0.0f));

    // -- ENEMIES -- //
    GLuint pig_texture_id = Utility::load_texture(PIG_FILEPATH);
    GLuint chicken_texture_id = Utility::load_texture(CHICKEN_FILEPATH);
    GLuint bat_texture_id = Utility::load_texture(BAT_FILEPATH);
    GLuint bee_texture_id = Utility::load_texture(BEE_FILEPATH);


    m_game_state.enemies = new Entity[LEVELB_ENEMY_COUNT];

    // ENEMY 0 PIG
    std::vector<std::vector<int>> pig_walking_animation =
    {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // LEFT
        {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 } // RIGHT
    };

    m_game_state.enemies[0] = Entity(
        pig_texture_id,            // texture id
        3.0f,                      // speed
        acceleration,              // acceleration
        0.0f,                      // jumping power
        pig_walking_animation,     // animation index sets
        0.0f,                      // animation time
        12,                        // animation frame amount
        0,                         // current animation index
        12,                        // animation column amount
        2,                         // animation row amount
        1.0f,                      // width
        1.0f,                      // height
        ENEMY
    );

    m_game_state.enemies[0].set_position(glm::vec3(16.0f, -29.0f, 0.0f));
    m_game_state.enemies[0].set_left_collider(glm::vec3(9.0f, -29.0f, 0.0f));
    m_game_state.enemies[0].set_right_collider(glm::vec3(33.0f, -29.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(1.0f, 0.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(WALKER);
    m_game_state.enemies[0].set_sound(PIG_SOUND);

    // ENEMY 1 & 2 BAT
    std::vector<std::vector<int>> bat_walking_animation =
    {
        {0, 1, 2, 3, 4, 5, 6}, // LEFT
        {7, 8, 9, 10, 11, 12, 13} // RIGHT
    };

    m_game_state.enemies[1] = Entity(
        bat_texture_id,            // texture id
        1.0f,                      // speed
        glm::vec3(0.0f),           // acceleration
        0.0f,                      // jumping power
        bat_walking_animation,     // animation index sets
        0.0f,                      // animation time
        7,                         // animation frame amount
        0,                         // current animation index
        7,                         // animation column amount
        2,                         // animation row amount
        0.25f,                      // width
        0.25f,                      // height
        ENEMY
    );

    m_game_state.enemies[1].set_position(glm::vec3(27.0f, -31.5f, 0.0f));
    m_game_state.enemies[1].set_left_collider(glm::vec3(9.0f, -31.5f, 0.0f));
    m_game_state.enemies[1].set_right_collider(glm::vec3(33.0f, -31.5f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(2.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_velocity(glm::vec3(0.0f, 1.0f, 0.0f));
    m_game_state.enemies[1].set_scale(glm::vec3(0.5f));
    m_game_state.enemies[1].set_ai_type(FLYER);
    m_game_state.enemies[1].set_sound(BAT_SOUND);

    m_game_state.enemies[2] = Entity(
        bat_texture_id,            // texture id
        1.0f,                      // speed
        glm::vec3(0.0f),           // acceleration
        0.0f,                      // jumping power
        bat_walking_animation,     // animation index sets
        0.0f,                      // animation time
        7,                         // animation frame amount
        0,                         // current animation index
        7,                         // animation column amount
        2,                         // animation row amount
        0.25f,                     // width
        0.25f,                     // height
        ENEMY
    );

    m_game_state.enemies[2].set_position(glm::vec3(27.0f, -34.5f, 0.0f));
    m_game_state.enemies[2].set_left_collider(glm::vec3(7.0f, -34.5f, 0.0f));
    m_game_state.enemies[2].set_right_collider(glm::vec3(32.0f, -34.5f, 0.0f));
    m_game_state.enemies[2].set_movement(glm::vec3(2.0f, 0.0f, 0.0f));
    m_game_state.enemies[2].set_velocity(glm::vec3(0.0f, 1.0f, 0.0f));
    m_game_state.enemies[2].set_scale(glm::vec3(0.5f));
    m_game_state.enemies[2].set_ai_type(FLYER);
    m_game_state.enemies[2].set_sound(BAT_SOUND);


    // ENEMY 3 - 10 BEEEEEEEEEEEES
    std::vector<std::vector<int>> bee_walking_animation = {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7}
    };

    for (int i = 0; i < 8; i++) 
    {
        m_game_state.enemies[3 + i] = Entity(
            bee_texture_id,            // texture id
            0.5f,                      // speed
            glm::vec3(0.0f),           // acceleration
            0.0f,                      // jumping power
            bee_walking_animation,     // animation index sets
            0.0f,                      // animation time
            8,                         // animation frame amount
            0,                         // current animation index
            8,                         // animation column amount
            1,                         // animation row amount
            0.25f,                      // width
            0.25f,                      // height
            ENEMY
        );

        m_game_state.enemies[3 + i].set_position(glm::vec3(10.0f + (1.0f * i) + (4.0f * (i/4)), -26.0f, 0.0f));
        m_game_state.enemies[3 + i].set_left_collider(glm::vec3(10.0f + (1.0f * i) + (4.0f * (i / 4)), -25.0f, 0.0f));
        m_game_state.enemies[3 + i].set_right_collider(glm::vec3(10.0f + (1.0f * i) + (4.0f * (i / 4)), -30.0f, 0.0f));
        m_game_state.enemies[3 + i].set_movement(glm::vec3(0.0f, 0.01f, 0.0f));
        m_game_state.enemies[3 + i].set_scale(glm::vec3(0.5f));
        m_game_state.enemies[3 + i].set_ai_state(IDLE);
        m_game_state.enemies[3 + i].set_ai_type(FALLER);
        m_game_state.enemies[3 + i].set_sound(BEE_SOUND);
    }

    m_game_state.enemies[11] = Entity(
        bee_texture_id,            // texture id
        2.5f,                      // speed
        glm::vec3(0.0f),           // acceleration
        0.0f,                      // jumping power
        bee_walking_animation,     // animation index sets
        0.0f,                      // animation time
        8,                         // animation frame amount
        0,                         // current animation index
        8,                         // animation column amount
        1,                         // animation row amount
        0.25f,                      // width
        0.25f,                      // height
        ENEMY
    );

    m_game_state.enemies[11].set_position(glm::vec3(25.0f, -10.0f, 0.0f));
    m_game_state.enemies[11].set_left_collider(glm::vec3(25.0f, -9.0f, 0.0f));
    m_game_state.enemies[11].set_right_collider(glm::vec3(25.0f, -30.0f, 0.0f));
    m_game_state.enemies[11].set_movement(glm::vec3(0.0f, 0.01f, 0.0f));
    m_game_state.enemies[11].set_scale(glm::vec3(0.5f));
    m_game_state.enemies[11].set_ai_state(IDLE);
    m_game_state.enemies[11].set_ai_type(FALLER);
    m_game_state.enemies[11].set_sound(BEE_SOUND);


    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    m_game_state.jump_sfx = Mix_LoadWAV(JUMP_FILEPATH);
    m_game_state.death_sfx = Mix_LoadWAV(DEATH_FILEPATH);
}

bool LevelB::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELB_ENEMY_COUNT, m_game_state.map);
    collide_with_enemy = collide_with_enemy || m_game_state.player->get_position().y < -40.0f;
    if (collide_with_enemy) 
    { 
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);
        initialise(); 
    }

    for (int i = 0; i < LEVELB_ENEMY_COUNT; i++) 
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    if (LEVELB_END_FLAG.x < m_game_state.player->get_position().x && glm::distance(LEVELB_END_FLAG, m_game_state.player->get_position()) < 1.0f) 
    {
        m_game_state.next_scene_id = 3;
    }

    return collide_with_enemy;
}

void LevelB::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < LEVELB_ENEMY_COUNT; i++) 
    {
        m_game_state.enemies[i].render(program);
    }

    GLuint fontsheet_id = Utility::load_texture(FONT_FILEPATH);
    Utility::draw_text(program, fontsheet_id, "<---", 0.2f, 0.0f, glm::vec3(23.0f, -9.0f, 0.0f));

}