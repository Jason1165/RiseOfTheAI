#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 40
#define LEVEL_HEIGHT 20

constexpr char PLAYER_FILEPATH[] = "assets/char_run.png";
constexpr char ENEMY_FILEPATH[] = "assets/angry_pig.png";


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
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture("assets/updated_cake.png");
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
        3.5f,                      // jumping power
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

    m_game_state.player->set_position(glm::vec3(7.0f, -15.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(1.0f, 0.75f, 0.0f));

    // -- ENEMIES -- //
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];

    // ENEMY_ONE
    std::vector<std::vector<int>> enemy_walking_animation =
    {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // LEFT
        { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 } // RIGHT
    };

    m_game_state.enemies[0] = Entity(
        enemy_texture_id,          // texture id
        1.0f,                      // speed
        acceleration,              // acceleration
        0.0f,                      // jumping power
        enemy_walking_animation,   // animation index sets
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
    m_game_state.enemies[0].set_ai_type(WALKER);
    m_game_state.enemies[0].set_ai_state(ATTACKING);
    m_game_state.enemies[0].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));


    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS("assets/dooblydoo.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(0.0f);

    m_game_state.jump_sfx = Mix_LoadWAV("assets/bounce.wav");
}

void LevelA::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
    //collide_with_enemy ? std::cout << "TRUE" << std::endl : std::cout << "FALSE" << std::endl;

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    //std::cout << m_game_state.player->get_position().x << " " << m_game_state.player->get_position().y << std::endl;

    //if (m_game_state.player->get_position().y < -10.0f) m_game_state.next_scene_id = 0;
}

void LevelA::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) {
        m_game_state.enemies[i].render(program);
    }
}