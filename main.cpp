//#define GL_SILENCE_DEPRECATION
//#define STB_IMAGE_IMPLEMENTATION
//#define GL_GLEXT_PROTOTYPES 1
#define LOG(argument) std::cout << argument << '\n'
#define FIXED_TIMESTEP 0.0166666f
#define FIXED_JUMPTIME 0.5f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include "SDL_mixer.h" // changed from <> to "" and it works?
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Effects.h"
#include "Entity.h"
#include "Map.h"
#include "Utility.h"
#include "Scene.h"
#include "LevelA.h"
#include "LevelC.h"

// ————— CONSTANTS ————— //
const float MULTI = 1.5f;
const int WINDOW_WIDTH = 640 * MULTI,
WINDOW_HEIGHT = 480 * MULTI;

const float BG_RED = 0.1922f,
BG_BLUE = 0.549f,
BG_GREEN = 0.9059f,
BG_OPACITY = 1.0f;

const int   VIEWPORT_X = 0,
            VIEWPORT_Y = 0,
            VIEWPORT_WIDTH = WINDOW_WIDTH,
            VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char  GAME_WINDOW_NAME[] = "Hello, Maps!";

const char  V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
            F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;

const char  SPRITESHEET_FILEPATH[] = "assets/george_0.png",
            MAP_TILESET_FILEPATH[] = "assets/cake_sheet.png",
            BGM_FILEPATH[] = "assets/dooblydoo.mp3",
            JUMP_SFX_FILEPATH[] = "assets/bounce.wav";

const int NUMBER_OF_TEXTURES = 1;
const GLint LEVEL_OF_DETAIL = 0;
const GLint TEXTURE_BORDER = 0;

enum AppStatus { RUNNING, TERMINATED };


// ————— VARIABLES ————— //
Scene* g_current_scene;
LevelA* g_levelA;
LevelC* g_levelC;
Effects* g_effects = nullptr;

Scene* g_levels[2];

SDL_Window* g_display_window;
AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;
float g_last_jump = 0.0f; // measures time since last jump
bool g_is_colliding_bottom = false;

int GAME_LIVES = 3;


// PROTOTYPES
void switch_to_scene(Scene* scene);
void initialise();
void process_input();
void update();
void render();
void shutdown();


// ————— GENERAL FUNCTIONS ————— //
void switch_to_scene(Scene* scene)
{
    g_current_scene = scene;
    g_current_scene->initialise(); // DON'T FORGET THIS STEP!
}

void initialise()
{
    // ————— GENERAL ————— //
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow(GAME_WINDOW_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);

#ifdef _WINDOWS
    glewInit();
#endif

    // ————— VIDEO SETUP ————— //
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    g_projection_matrix = g_projection_matrix;

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    glUseProgram(g_shader_program.get_program_id());

    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);

    // ————— MAP SET-UP ————— //
    g_levelA = new LevelA();
    g_levelC = new LevelC();
    g_levels[0] = g_levelA;
    g_levels[1] = g_levelC;

    switch_to_scene(g_levels[1]);

    // -- EFFECTS -- //
    g_effects = new Effects(g_projection_matrix, g_view_matrix);


    // MUSIC FIX LATER
    //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    //g_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    //Mix_PlayMusic(g_state.bgm, -1);
    //Mix_VolumeMusic(MIX_MAX_VOLUME / 4.0f);

    //g_state.jump_sfx = Mix_LoadWAV(JUMP_SFX_FILEPATH);

    // ————— BLENDING ————— //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input()
{
    g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            g_app_status = TERMINATED;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_q:
                // Quit the game with a keystroke
                g_app_status = TERMINATED;
                break;
            case SDLK_k:
                GAME_LIVES += 5;
            case SDLK_SPACE:
            case SDLK_UP: { // creating scope 
                // Jump
                float ticks_jump = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
                float delta_jump = ticks_jump - g_last_jump;
                g_last_jump = ticks_jump;
                if (delta_jump > FIXED_JUMPTIME && g_current_scene->get_state().player->get_collided_bottom())
                {
                    g_current_scene->get_state().player->set_jump_state(SINGLE);
                    g_current_scene->get_state().player->jump();
                    //Mix_PlayChannel(-1, g_state.jump_sfx, 0);
                }
                else if (delta_jump > FIXED_JUMPTIME && g_current_scene->get_state().player->get_jump_state() == SINGLE) {
                    g_current_scene->get_state().player->set_jump_state(DOUBLE);
                    g_current_scene->get_state().player->jump();
                }
                break;
            }
            default:
                break;
            }

        default:
            break;
        }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_LEFT]) {
        g_current_scene->get_state().player->move_left();
    }
    else if (key_state[SDL_SCANCODE_RIGHT]) {
        g_current_scene->get_state().player->move_right();
    }

    // This makes sure that the player can't move faster diagonally
    if (glm::length(g_current_scene->get_state().player->get_movement()) > 1.0f) {
        g_current_scene->get_state().player->normalise_movement();
    }

}

void update()
{
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP)
    {
        if (g_current_scene->update(FIXED_TIMESTEP)) {
            GAME_LIVES--;
            std::cout << GAME_LIVES << std::endl;
            g_effects->start(FADEIN, 0.2f);
        }
        g_effects->update(FIXED_TIMESTEP);

        //if (g_is_colliding_bottom == false && g_current_scene->get_state().player->get_collided_bottom()) g_effects->start(SHAKE, 1.0f);

        g_is_colliding_bottom = g_current_scene->get_state().player->get_collided_bottom();

        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;

    // changing view matrix
    g_view_matrix = glm::mat4(1.0f);

    //if (g_current_scene->get_state().player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->get_state().player->get_position().x, -g_current_scene->get_state().player->get_position().y, 0));
    //}
    //else {
    //    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-5, 3.75, 0));
    //}

    //if (g_current_scene == g_levelA && g_current_scene->get_state().player->get_position().y < -10.0f) switch_to_scene(g_levelA);

    //g_view_matrix = glm::translate(g_view_matrix, g_effects->get_view_offset());
}


void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);

    glClear(GL_COLOR_BUFFER_BIT);

    // ————— RENDERING THE SCENE (i.e. map, character, enemies...) ————— //
    g_current_scene->render(&g_shader_program);

    g_effects->render();

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    SDL_Quit();

    delete g_levelA;
    delete g_levelC;
    delete g_effects;
}

// ————— GAME LOOP ————— //
int main(int argc, char* argv[])
{
    initialise();

    while (g_app_status == RUNNING)
    {
        process_input();
        update();
        
        if (g_current_scene->get_state().next_scene_id >= 0) {
            switch_to_scene(g_levels[g_current_scene->get_state().next_scene_id]);
        }

        render();
    }

    shutdown();
    return 0;
}
