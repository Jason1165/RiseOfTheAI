/**
* Author: Jason Lin
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 40
#define LEVEL_HEIGHT 20

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

glm::vec3 LEVELA_END_FLAG = glm::vec3(32.0f, -1.0f, 0.0f);


unsigned int LEVELA_DATA[] =
{
        3,3,3,3,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,3,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,5,6,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,54,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,52,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,52,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,10,11,11,11,11,11,11,11,11,12,0,0,0,0,0,0,52,0,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,11,11,12,0,0,0,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,0,28,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,29,0,3,3,1,1,1,1,1,1,
        1,1,1,1,1,1,40,42,42,41,0,0,2,4,48,49,50,51,1,1,0,0,0,0,0,0,0,0,0,0,3,3,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,3,3,3,3,3,3,1,1,3,3,3,3,1,1,3,4,0,0,2,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture(TILE_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 8, 7);

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

    m_game_state.player->set_position(glm::vec3(6.5f, -12.0f, 0.0f));

    // -- ENEMIES -- //
    GLuint pig_texture_id = Utility::load_texture(PIG_FILEPATH);
    GLuint chicken_texture_id = Utility::load_texture(CHICKEN_FILEPATH);

    m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];

    // ENEMY_ZERO
    std::vector<std::vector<int>> pig_walking_animation =
    {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // LEFT
        {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 } // RIGHT
    };

    m_game_state.enemies[0] = Entity(
        pig_texture_id,            // texture id
        1.0f,                      // speed
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

    m_game_state.enemies[0].set_position(glm::vec3(26.0f, -10.0f, 0.0f));
    m_game_state.enemies[0].set_left_collider(glm::vec3(24.0f, -10.0f, 0.0f));
    m_game_state.enemies[0].set_right_collider(glm::vec3(29.0f, -10.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(1.0f, 0.0f, 0.0f));
    m_game_state.enemies[0].set_ai_type(WALKER);
    m_game_state.enemies[0].set_sound(PIG_SOUND);


    // ENEMY_ONE
    std::vector<std::vector<int>> chicken_walking_animation =
    {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, // LEFT
        {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 } // RIGHT
    };

    m_game_state.enemies[1] = Entity(
        chicken_texture_id,        // texture id
        1.0f,                      // speed
        acceleration,              // acceleration
        0.0f,                      // jumping power
        chicken_walking_animation, // animation index sets
        0.0f,                      // animation time
        14,                        // animation frame amount
        0,                         // current animation index
        14,                        // animation column amount
        2,                         // animation row amount
        1.0f,                      // width
        1.0f,                      // height
        ENEMY
    );

    m_game_state.enemies[1].set_position(glm::vec3(29.0f, -15.0f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].face_left();
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_ai_state(IDLE);
    m_game_state.enemies[1].set_sound(CHICKEN_SOUND);

    // ENEMY_TWO
    m_game_state.enemies[2] = Entity(
        pig_texture_id,            // texture id
        1.0f,                      // speed
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

    m_game_state.enemies[2].set_position(glm::vec3(16.0f, -9.0f, 0.0f));
    m_game_state.enemies[2].set_left_collider(glm::vec3(12.0f, -9.0f, 0.0f));
    m_game_state.enemies[2].set_right_collider(glm::vec3(21.0f, -9.0f, 0.0f));
    m_game_state.enemies[2].set_movement(glm::vec3(1.0f, 0.0f, 0.0f));
    m_game_state.enemies[2].set_ai_type(WALKER);
    m_game_state.enemies[2].set_sound(PIG_SOUND);

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

bool LevelA::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
    collide_with_enemy = collide_with_enemy || m_game_state.player->get_position().y < -20.0f;
    if (collide_with_enemy) 
    { 
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);
        initialise(); 
    }

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) 
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    //std::cout << m_game_state.player->get_position().x << " " << m_game_state.player->get_position().y << std::endl;

    if (LEVELA_END_FLAG.x < m_game_state.player->get_position().x && glm::distance(LEVELA_END_FLAG, m_game_state.player->get_position()) < 2.0f) 
    {
        m_game_state.next_scene_id = 2;
    }

    return collide_with_enemy;
}

void LevelA::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) 
    {
        m_game_state.enemies[i].render(program);
    }

    GLuint fontsheet_id = Utility::load_texture(FONT_FILEPATH);
    Utility::draw_text(program, fontsheet_id, "Use the Arrow Keys", 0.2f, 0.0f, glm::vec3(6.0f, -12.0f, 0.0f));
    Utility::draw_text(program, fontsheet_id, "to Move", 0.2f, 0.0f, glm::vec3(7.0f, -12.5f, 0.0f));
    Utility::draw_text(program, fontsheet_id, "JUMP", 0.2f, 0.0f, glm::vec3(12.25f, -12.25f, 0.0f));
    Utility::draw_text(program, fontsheet_id, "DOUBLE JUMP", 0.2f, 0.0f, glm::vec3(17.5f, -11.75f, 0.0f));

}