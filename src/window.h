#pragma once

#include <vector>
#include <string>

#include "window_event.h"

#ifdef WINDOW_IMP_SDL2
#include <SDL2/SDL.h>
#endif

namespace SC
{
#ifdef WINDOW_IMP_SDL2
    using WindowImp = SDL_Window *;
#endif
    enum WindowParams
    {
        Resizable = 1 << 0,
        Borderless = 1 << 1,
        Minimized = 1 << 2,
        Maximized = 1 << 3
    };

    class Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        Window(const unsigned int width, const unsigned int height, const std::string &title, const int params);
        ~Window();

        void show();
        int handle_event(const WindowEvent &event);

        static int poll_event(WindowEvent &event);
        static int window_subsystem_init();
        static bool subsystem_initialized() { return is_subsystem_initialized; }

    private:
        WindowImp window_imp;
        WindowID window_id;

        unsigned int width;
        unsigned int height;

        bool is_mouse_within_window;
        bool is_window_focused;

        static bool is_subsystem_initialized;
    };

} // namespace SC
