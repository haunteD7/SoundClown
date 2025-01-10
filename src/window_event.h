#include <cstdint>

#ifdef WINDOW_IMP_SDL2
#include <SDL2/SDL.h>

using WindowID = Uint32;
#endif

namespace SC
{
    enum WindowEventType
    {
        Resize,
        Move,
        Close,
        MouseEnter,
        MouseLeave,
        FocusEnter,
        FocusLeave,
    };

    struct WindowEventData
    {
        WindowEventType type;
        WindowID window_id;
    };
    struct WindowResizeData
    {
        WindowEventType type;
        WindowID window_id;
        int w;
        int h;
    };
    struct WindowMoveData
    {
        WindowEventType type;
        WindowID window_id;
        int x;
        int y;
    };
    struct WindowCloseData
    {
        WindowEventType type;
        WindowID window_id;
    };
    struct WindowMouseEnterData
    {
        WindowEventType type;
        WindowID window_id;
    };
    struct WindowMouseLeaveData
    {
        WindowEventType type;
        WindowID window_id;
    };
    struct WindowFocusEnterData
    {
        WindowEventType type;
        WindowID window_id;
    };
    struct WindowFocusLeaveData
    {
        WindowEventType type;
        WindowID window_id;
    };
    union WindowEvent
    {
        WindowEventData data;
        WindowCloseData close_data;
        WindowResizeData resize_data;
        WindowMoveData move_data;
        WindowMouseEnterData mouse_enter_data;
        WindowMouseLeaveData mouse_leave_data;
        WindowFocusEnterData focus_enter_data;
        WindowFocusLeaveData focus_leave_data;
    };
    
} // namespace SC
