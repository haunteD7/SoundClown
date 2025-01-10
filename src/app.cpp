#include "app.h"

#include <iostream>

namespace SC
{
    App::App()
    {
    }
    App::~App()
    {
    }
    int App::run()
    {
        Window window(800, 600, "Test", WindowParams::Resizable);
        window.show();

        bool is_main_window_open = true;
        WindowEvent e;
        while (is_main_window_open)
        {
            while (Window::poll_event(e))
            {
                window.handle_event(e);
            }

            if (e.data.type == WindowEventType::Close)
                is_main_window_open = false;
        }

        return 0;
    }
} // namespace SC
