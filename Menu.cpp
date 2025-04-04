/**
* Author: Jason Lin
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Menu.h"
#include "Utility.h"

#define LEVEL_WIDTH 1
#define LEVEL_HEIGHT 1

constexpr char PLAYER_FILEPATH[] = "assets/sprites/char_run.png";
constexpr char FONT_FILEPATH[] = "assets/sprites/modified_atari_font.png";
constexpr char TILE_FILEPATH[] = "assets/sprites/updated_cake.png";

constexpr char BGM_FILEPATH[] = "assets/audio/Cupids-Revenge.mp3";
constexpr char JUMP_FILEPATH[] = "assets/audio/187024__lloydevans09__jump2.wav";
constexpr char DEATH_FILEPATH[] = "assets/audio/157218__adamweeden__video-game-die-or-lose-life.wav";

unsigned int MENU_DATA[] =
{
    0
};

Menu::~Menu()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void Menu::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture(TILE_FILEPATH);

    // -- PLAYER -- //
    std::vector<std::vector<int>> player_walking_animation =
    {
        { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35 }, // LEFT
        { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 }, // RIGHT
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

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

    m_game_state.player->set_position(glm::vec3(0.0f));

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

bool Menu::update(float delta_time)
{
    return false;
}

void Menu::render(ShaderProgram* program)
{
    GLuint fontsheet_id = Utility::load_texture(FONT_FILEPATH);
    m_game_state.player->render(program);
    Utility::draw_text(program, fontsheet_id, "A Platformer Game", 0.4f, 0.05f, glm::vec3(-3.5f, 2.0f, 0.0f));
    Utility::draw_text(program, fontsheet_id, "Press ENTER", 0.25f, 0.05f, glm::vec3(-1.3f, -2.0f, 0.0f));
    Utility::draw_text(program, fontsheet_id, "to START!", 0.25f, 0.05f, glm::vec3(-1.0f, -2.5f, 0.0f));

}