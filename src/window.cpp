#include "window.h"

#include <iostream>

namespace SC
{
    bool Window::is_subsystem_initialized = false;

#ifdef WINDOW_IMP_SDL2
    struct SDL2WindowData
    {
        SDL_Window* window;
        Uint32 window_id;
    };
    Window::Window(const unsigned int width, const unsigned int height, const std::string &title, const int params)
        : window_imp(nullptr), is_window_focused(false), is_mouse_within_window(false), width(width), height(height)
    {
        Uint32 SDL2_flags = SDL_WINDOW_HIDDEN;
        if (params & WindowParams::Resizable)
        {
            SDL2_flags |= SDL_WINDOW_RESIZABLE;
        }
        if (params & WindowParams::Borderless)
        {
            SDL2_flags |= SDL_WINDOW_BORDERLESS;
        }
        if (params & WindowParams::Minimized)
        {
            SDL2_flags |= SDL_WINDOW_MINIMIZED;
        }
        if (params & WindowParams::Maximized)
        {
            SDL2_flags |= SDL_WINDOW_MAXIMIZED;
        }

        SDL_Window *SDL2_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL2_flags);
        if (!SDL2_window)
        {
            std::cerr << "SDL2 window creation error: " << SDL_GetError() << "\n";
            return;
        }
        window_imp = SDL2_window;
    }
    Window::~Window()
    {
        if (!window_imp)
            return;
        SDL_DestroyWindow(window_imp);
    }

    void Window::show()
    {
        if (!window_imp)
            return;
        SDL_ShowWindow(window_imp);
    }

    int Window::handle_event(const WindowEvent& event)
    {
        if(window_id != event.data.window_id) return 0;
        switch (event.data.type)
        {
            case WindowEventType::Resize:
            {
                width = event.resize_data.w;
                height = event.resize_data.h;
                break;
            }
            case WindowEventType::FocusEnter:
            {
                is_window_focused = true;
                break;
            }
            case WindowEventType::FocusLeave:
            {
                is_window_focused = false;
                break;
            }
            case WindowEventType::MouseEnter:
            {
                is_mouse_within_window = true;
                break;
            }
            case WindowEventType::MouseLeave:
            {
                is_mouse_within_window = false;
                break;
            }
        }
        return 0;
    }

    int Window::poll_event(WindowEvent& event)
    {
        SDL_Event SDL2_event;
        if(!SDL_PollEvent(&SDL2_event)) return 0;

        switch(SDL2_event.type){
            case SDL_WINDOWEVENT:
            {
                switch (SDL2_event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        event.resize_data.type = WindowEventType::Resize;
                        event.resize_data.window_id = SDL2_event.window.windowID;
                        event.resize_data.w = SDL2_event.window.data1;
                        event.resize_data.h = SDL2_event.window.data2;
                        break;
                    }
                    case SDL_WINDOWEVENT_MOVED:
                    {
                        event.move_data.type = WindowEventType::Move;
                        event.move_data.window_id = SDL2_event.window.windowID;
                        event.move_data.x = SDL2_event.window.data1;
                        event.move_data.y = SDL2_event.window.data2;
                        break;
                    }
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        event.close_data.type = WindowEventType::Close;
                        event.close_data.window_id = SDL2_event.window.windowID;
                        break;
                    }
                    case SDL_WINDOWEVENT_ENTER:
                    {
                        event.mouse_enter_data.type = WindowEventType::MouseEnter;
                        event.mouse_enter_data.window_id = SDL2_event.window.windowID;
                        break;
                    }
                    case SDL_WINDOWEVENT_LEAVE:
                    {
                        event.mouse_leave_data.type = WindowEventType::MouseLeave;
                        event.mouse_leave_data.window_id = SDL2_event.window.windowID;
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        event.focus_enter_data.type = WindowEventType::FocusEnter;
                        event.focus_enter_data.window_id = SDL2_event.window.windowID;
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        event.focus_leave_data.type = WindowEventType::FocusLeave;
                        event.focus_leave_data.window_id = SDL2_event.window.windowID;
                        break;
                    }
                }
                break;
            }
        }
        return 1;
    }

    int Window::window_subsystem_init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL2 video initialization error: " << SDL_GetError() << "\n";
            return -1;
        }
        is_subsystem_initialized = true;
        return 0;
    }
#endif
} // namespace SC
