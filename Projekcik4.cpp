#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

RECT objekt = { 275, 295, 325, 345 };
bool moving = false;
int ksztalt;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) 
        {
            if (!moving) 
            {
                moving = true;
                SetTimer(hwnd, 1, 30, nullptr);
            }
        }
        if (LOWORD(wParam) == 2 && !moving)
        {
            ksztalt = 0;
        }
        if (LOWORD(wParam) == 3 && !moving)
        {
            ksztalt = 1;
        }
        break;
    }
    break;
    case WM_TIMER:
        if (moving) {
            objekt.left -= 2;
            objekt.right -= 2;

            if (objekt.left <= 180) {
                KillTimer(hwnd, 1);
                moving = false;
            }

            InvalidateRect(hwnd, nullptr, TRUE);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        Graphics graphics(hdc);
        graphics.Clear(Color::Black);

        Pen peny(Color::Yellow, 2);
        Pen penw(Color::White, 2);
        Pen peng(Color::Gray, 2);
        Pen penr(Color::Red, 2);
        SolidBrush bruh(Color::AntiqueWhite);

        graphics.DrawRectangle(&peny, 150, 100, 10, 200);
        graphics.DrawRectangle(&peny, 100, 125, 200, 10);

        for (int i = 0; i < 10; i++)
        {
            graphics.DrawLine(&peny, 20 * i + 100, 135, 20 * i + 110, 125);
            graphics.DrawLine(&peny, 20 * i + 110, 125, 20 * i + 120, 135);
        }
        for (int i = 0; i < 20; i++)
        {
            graphics.DrawLine(&peny, 160, 10 * i + 100, 150, 10 * i + 110);
            graphics.DrawLine(&peny, 150, 10 * i + 110, 160, 10 * i + 110);
        }

        graphics.DrawLine(&penw, 150, 100, 100, 125);
        graphics.DrawLine(&penw, 160, 100, 220, 125);
        graphics.DrawLine(&penw, 160, 100, 280, 125);



        for (int i = 0; i < 4; i++)
        {
            graphics.DrawRectangle(&penw, 90 - 10 * i, 115, 10, 30);
        }

        graphics.DrawRectangle(&penw, 140, 280, 30, 5);
        for (int i = 0; i < 10; i++)
        {
            graphics.DrawRectangle(&penw, 145, 5 * i + 285, 20, 5);
        }

        graphics.DrawLine(&penw, 150, 300, 135, 345);
        graphics.DrawLine(&penw, 160, 300, 175, 345);

        graphics.DrawLine(&peng, 0, 345, 500, 345);

        Point kabina[] = {Point(145, 155),
                          Point(145, 165),
                          Point(175, 165),
                          Point(175, 140),
                          Point(160, 155) };

        graphics.FillClosedCurve(&bruh, kabina, 5, FillModeAlternate, 0);
        graphics.DrawClosedCurve(&penr, kabina, 5, 0);


        switch (ksztalt) {
        case 0:
        {
            graphics.FillRectangle(&bruh,
                static_cast<INT>(objekt.left),
                static_cast<INT>(objekt.top),
                static_cast<INT>(objekt.right - objekt.left),
                static_cast<INT>(objekt.bottom - objekt.top));
        }
        break;
        case 1:
        {
            graphics.FillEllipse(&bruh,
                static_cast<INT>(objekt.left),
                static_cast<INT>(objekt.top),
                static_cast<INT>(objekt.right - objekt.left),
                static_cast<INT>(objekt.bottom - objekt.top));
        }
        break;
        }
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"GDI+ Test", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, nullptr, nullptr, hInstance, nullptr);

    HWND left = CreateWindow(
        L"BUTTON",
        L"left",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 20, 50, 50,
        hwnd,
        (HMENU)1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND kolko= CreateWindow(
        L"BUTTON",
        L"kolko",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        80, 20, 50, 50,
        hwnd,
        (HMENU)2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND kwadrat = CreateWindow(
        L"BUTTON",
        L"kwadrat",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        140, 20, 50, 50,
        hwnd,
        (HMENU)3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return 0;

}