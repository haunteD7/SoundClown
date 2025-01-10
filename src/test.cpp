#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512
#define NOTES_NUMBER 12
#define MAX_CONTROLS 12 // 
#define BASE_FREQ 16.35
#define BASE_OCTAVE 4
#define DISTORTION_THRESHOLD 0.5

#define PI 3.1415

#define WAVE_FUNC sin_2pi

float frequencies[NOTES_NUMBER];

float volume = 1;

unsigned int current_sample = 0;
bool control_keys_pressed[MAX_CONTROLS];

float sin_2pi(float t)
{
    return sinf(2 * PI * t);
}
float square(float t)
{
    float r;

    if ((int)t % 2)
        r = 1;
    else
        r = -1;

    return r;
}

void audio_callback(void *userdata, Uint8 *stream, int len)
{
    float *fstream = (float *)stream;

    for (int current_buffer_sample = 0; current_buffer_sample < BUFFER_SIZE; current_buffer_sample++)
    {
        float val = 0;
        for (int current_control = 0; current_control < MAX_CONTROLS; current_control++)
        {
            if (control_keys_pressed[current_control])
            {
                float note = volume * WAVE_FUNC((float)current_sample / SAMPLE_RATE * frequencies[current_control]);
                val += note;
            }
        }
        if (val > volume * DISTORTION_THRESHOLD)
            val = volume * DISTORTION_THRESHOLD;
        else if (val < -volume * DISTORTION_THRESHOLD)
            val = -volume * DISTORTION_THRESHOLD;

        fstream[current_buffer_sample] = val;
        current_sample++;
    }
}

int main(int argc, char **argv)
{
    #ifdef WINDOW_IMP_SDL2
        printf("Hello\n");
    #endif
    for (int i = 0; i < NOTES_NUMBER; i++)
    {
        frequencies[i] = BASE_FREQ * pow(2, BASE_OCTAVE + (float)i / NOTES_NUMBER);
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL Init error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_AudioSpec as;
    as.callback = audio_callback;
    as.channels = 1;
    as.format = AUDIO_F32;
    as.freq = SAMPLE_RATE;
    as.samples = BUFFER_SIZE;

    if (SDL_OpenAudio(&as, NULL) < 0)
    {
        printf("Audio error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SoundClown", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 550, SDL_WINDOW_HIDDEN);
    SDL_ShowWindow(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_PauseAudio(0);

    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    bool is_open = true;
    SDL_Event e;
    while (is_open)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                is_open = false;
                break;
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (int i = 0; i < MAX_CONTROLS; i++)
        {
            SDL_Rect button_rect;
            button_rect.x = 45 + i*(100+10);
            button_rect.y = 20;
            button_rect.h = 500;
            button_rect.w = 100;

            switch (i)
            {
            case 0:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_Q];
                break;
            case 1:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_W];
                break;
            case 2:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_E];
                break;
            case 3:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_R];
                break;
            case 4:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_T];
                break;
            case 5:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_Y];
                break;
            case 6:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_U];
                break;
            case 7:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_I];
                break;
            case 8:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_O];
                break;
            case 9:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_P];
                break;
            case 10:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_LEFTBRACKET];
                break;
            case 11:
                control_keys_pressed[i] = key_state[SDL_SCANCODE_RIGHTBRACKET];
                break;
            }
            if (control_keys_pressed[i])
            {
                SDL_RenderFillRect(renderer, &button_rect);
            }
            else
            {
                SDL_RenderDrawRect(renderer, &button_rect);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
    }
    SDL_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
