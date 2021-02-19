#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK main_window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;

    switch (message)
    {
    case WM_SIZE:
        printf("WM_SIZE\n");
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    // case WM_CLOSE:
    //     OutputDebugStringA("WM_CLOSE\n");
    //     break;

    case WM_ACTIVATEAPP:
        printf("WM_ACTIVATEAPP\n");
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT paint;
        HDC device_context = BeginPaint(window, &paint);
        int x = paint.rcPaint.left;
        int y = paint.rcPaint.top;
        int height = paint.rcPaint.bottom - paint.rcPaint.top;
        int width = paint.rcPaint.right - paint.rcPaint.left;

        PatBlt(device_context, x, y, width, height, BLACKNESS);

        EndPaint(window, &paint);
    }
        break;
    
    default:
        result = DefWindowProc(window, message, w_param, l_param);
    }

    return result;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance, PSTR command_line_options, INT show_command_line)
{

    WNDCLASS window_class = { 
        .style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = main_window_procedure, 
        .hInstance = instance,
        .lpszClassName = "yoghurt_window_class",
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)COLOR_WINDOW
    };

    if (!RegisterClass(&window_class))
    {
        // TODO: Log this as an error.
        return 0;
    }

    HWND window_handle = CreateWindowEx(
    0,                                  // Optional window styles.
    window_class.lpszClassName,          // Window class
    "Yoghurt",           // Window text
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // Window style
    CW_USEDEFAULT,                      // X Coordinate 
    CW_USEDEFAULT,                      // Y Coordinate
    CW_USEDEFAULT,                      // Width
    CW_USEDEFAULT,                      // Height
    0,                                  // Parent window    
    0,                                  // Menu
    instance,                           // Instance handle
    0                                   // Additional application data
    );

    if (window_handle == NULL)
    {
        // TODO: Log this as an error.
        return 0;
    }

    while(1)
    {
        MSG message;
        BOOL message_result = GetMessage(&message, NULL, 0, 0) > 0;

        if (message_result > 0)
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            break;
        }
    }

    return 0;
}