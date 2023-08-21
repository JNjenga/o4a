#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")

typedef LRESULT (*windproc_callback_fn)(HWND, UINT, WPARAM, LPARAM);

HWND create_window(const wchar_t* class_name, WNDPROC windproc, const wchar_t* window_name, HWND parent, HINSTANCE h_instance, int x, int y, int w, int h);
LRESULT CALLBACK parent_windproc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
LRESULT CALLBACK child_windproc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

BOOL CALLBACK enum_window_callback(HWND hwnd, LPARAM lparam);


HWND hwnd_parent;

int WINAPI wWinMain(HINSTANCE h_instance, HINSTANCE h_previnstance, PWSTR p_cmdline, int n_cmdshow)
{
    hwnd_parent = create_window(L"O4A class name", parent_windproc, L"O4A", NULL, h_instance, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT);

    ShowWindow(hwnd_parent, n_cmdshow);

    EnumWindows(enum_window_callback, NULL);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

HWND create_window(const wchar_t* class_name, WNDPROC windproc, const wchar_t* window_name, HWND parent, HINSTANCE h_instance, int x, int y, int w = 0, int h = 0)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc   = windproc;
    wc.hInstance     = h_instance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
            0,
            class_name,
            window_name,
            WS_OVERLAPPEDWINDOW,
            x ? x : CW_USEDEFAULT, y ? y : CW_USEDEFAULT,
            w ? w : CW_USEDEFAULT, h ? h : CW_USEDEFAULT,
            parent, // Parent
            NULL,
            h_instance,
            NULL
            );

    return hwnd;
}

LRESULT CALLBACK parent_windproc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch(u_msg)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

                EndPaint(hwnd, &ps);
                return 0;
            }
            break;
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}

LRESULT CALLBACK child_windproc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch(u_msg)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 5));

                EndPaint(hwnd, &ps);
                return 0;
            }
            break;
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}

BOOL CALLBACK enum_window_callback(HWND hwnd, LPARAM lparam)
{
    if(!IsWindowVisible(hwnd))
    {
        return true;
    }

    if(hwnd != hwnd_parent)
    {
        SetParent(hwnd, hwnd_parent);
    }

    return true;
}

