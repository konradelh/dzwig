#include <windows.h>
#include <gdiplus.h>
#include <vector>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

std::vector<RECT> objekty;
int ktory = 0;
bool movingleft = false;
bool movingright = false;
bool movingup = false;
bool movingdown = false;
bool wieza_ktk = false;
bool wieza_kkt = false;
bool wieza_1 = false;
bool wieza_2 = false;
bool wieza_3 = false;
std::vector<int> ksztalt;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        RECT nowy = { 285, 320, 310, 345 };
        if (LOWORD(wParam) == 1) 
        {
            if (!movingleft) 
            {
                movingleft = true;
                movingright = false;
                movingup = false;
                movingdown = false;
                SetTimer(hwnd, 1, 1, nullptr);
            }
        }
        if (LOWORD(wParam) == 2)
        {
            if (!movingright)
            {
                movingright = true;
                movingleft = false;
                movingup = false;
                movingdown = false;
                SetTimer(hwnd, 1, 1, nullptr);
            }
        }
        if (LOWORD(wParam) == 3)
        {
            if (!movingup)
            {
                movingup = true;
                movingleft = false;
                movingright = false;
                movingdown = false;
                SetTimer(hwnd, 1, 1, nullptr);
            }
        }
        if (LOWORD(wParam) == 4)
        {
            if (!movingdown)
            {
                movingdown = true;
                movingup = false;
                movingleft = false;
                movingright = false;
                SetTimer(hwnd, 1, 1, nullptr);
            }
        }
        if (LOWORD(wParam) == 5)
        {
            ksztalt.push_back(1);
            objekty.push_back(nowy);
            ktory = objekty.size() - 1;
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (LOWORD(wParam) == 6)
        {
            ksztalt.push_back(0);
            objekty.push_back(nowy);
            ktory = objekty.size() - 1;
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (LOWORD(wParam) == 7)
        {
            ksztalt.push_back(2);
            objekty.push_back(nowy);
            ktory = objekty.size() - 1;
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (LOWORD(wParam) == 8)
        {
            ksztalt.push_back(0);
            objekty.push_back(nowy);
            ktory = objekty.size() - 1;
            wieza_ktk = true;
            SetTimer(hwnd, 1, 1, nullptr);
        }
        if (LOWORD(wParam) == 9)
        {
            ksztalt.push_back(1);
            objekty.push_back(nowy);
            ktory = objekty.size() - 1;
            wieza_kkt = true;
            SetTimer(hwnd, 1, 1, nullptr);
        }
        break;
    }
    break;
    case WM_TIMER:
    {
        RECT& klocek = objekty[ktory];

        if (movingleft && !movingright && !movingup && !movingdown) {

            if (klocek.left <= 180) {
                KillTimer(hwnd, 1);
                movingleft = false;
            }
            else
            {
                klocek.left -= 4;
                klocek.right -= 4;
            }

            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (movingright && !movingleft && !movingup && !movingdown) {

            if (klocek.right >= 305) {
                KillTimer(hwnd, 1);
                movingright = false;
            }
            else
            {
                klocek.left += 4;
                klocek.right += 4;
            }

            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (movingup && !movingleft && !movingright && !movingdown) {

            if (klocek.top <= 135) {
                KillTimer(hwnd, 1);
                movingup = false;
            }
            else
            {
                klocek.top -= 4;
                klocek.bottom -= 4;
            }
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (movingdown && !movingup && !movingleft && !movingright) {

            if (klocek.bottom >= 345) {
                KillTimer(hwnd, 1);
                movingdown = false;
            }
            else
            {
                klocek.top += 4;
                klocek.bottom += 4;
            }

            InvalidateRect(hwnd, nullptr, TRUE);
        }
        if (wieza_ktk == true || wieza_kkt == true)
        {
            bool up = false;
            bool left = false;
            bool down = false;
            if (klocek.top > 135 && klocek.right > 220)
            {
                if (up == false && left == false && down == false)
                {
                    klocek.top -= 4;
                    klocek.bottom -= 4;
                }
            }
            else
            {
                up = true;
            }
            if (klocek.left > 180)
            {
                if (left == false && up == true && down == false)
                {
                    klocek.right -= 4;
                    klocek.left -= 4;
                }
            }
            else
            {
                left = true;
            }
            if (klocek.bottom < 345 && klocek.right < 220 && (wieza_1 == false || klocek.bottom < objekty[ktory - 1].top))
            {
                if (down == false && up == true && left == true)
                {
                    klocek.top += 4;
                    klocek.bottom += 4;
                }
            }
            else
            {
                down = true;
            }
            if (up == true && left == true && down == true)
            {
                RECT nowy = { 285, 320, 310, 345 };
                if (wieza_2 == true)
                    wieza_3 = true;
                if (wieza_1 == true && wieza_2 == false)
                {
                    if (wieza_ktk == true)
                        ksztalt.push_back(1);
                    else if (wieza_kkt == true)
                        ksztalt.push_back(2);
                    objekty.push_back(nowy);
                    ktory = objekty.size() - 1;
                    wieza_2 = true;
                    up = false;
                    left = false;
                    down = false;
                }
                if (wieza_1 == false)
                {
                    if (wieza_ktk == true)
                        ksztalt.push_back(2);
                    else if (wieza_kkt == true)
                        ksztalt.push_back(0);
                    objekty.push_back(nowy);
                    ktory = objekty.size() - 1;
                    wieza_1 = true;
                    up = false;
                    left = false;
                    down = false;
                }
            }
            if (wieza_1 == true && wieza_2 == true && wieza_3 == true)
            {
                KillTimer(hwnd, 1);
                wieza_ktk = false;
                wieza_kkt = false;
                wieza_1 = false;
                wieza_2 = false;
                wieza_3 = false;
                up = false;
                left = false;
                down = false;
            }
            InvalidateRect(hwnd, nullptr, TRUE);
        }
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

        for (int i = 0; i < objekty.size(); i++)
        {
            RECT &objekt = objekty[i];
            RECT &linka = objekty[ktory];
            graphics.DrawLine(&penw, (linka.left + linka.right) / 2, 135, (linka.left + linka.right) / 2, linka.top);

            switch (ksztalt[i]) {
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
            case 2:
            {
                Point trojkat[] = { Point((objekt.left + objekt.right) / 2, objekt.top),
                              Point(objekt.left, objekt.bottom),
                              Point(objekt.right, objekt.bottom), };
                graphics.FillClosedCurve(&bruh, trojkat, 3, FillModeAlternate, 0);
            }
            break;
            }
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
        20, 40, 25, 25,
        hwnd,
        (HMENU)1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND right = CreateWindow(
        L"BUTTON",
        L"right",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        100, 40, 25, 25,
        hwnd,
        (HMENU)2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND up= CreateWindow(
        L"BUTTON",
        L"up",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        60, 10, 25, 25,
        hwnd,
        (HMENU)3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND down = CreateWindow(
        L"BUTTON",
        L"down",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        60, 70, 25, 25,
        hwnd,
        (HMENU)4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND kolko = CreateWindow(
        L"BUTTON",
        L"kolko",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        140, 10, 60, 25,
        hwnd,
        (HMENU)5,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND kwadrat = CreateWindow(
        L"BUTTON",
        L"kwadrat",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        200, 10, 60, 25,
        hwnd,
        (HMENU)6,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND trojkat = CreateWindow(
        L"BUTTON",
        L"trojkat",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        260, 10, 60, 25,
        hwnd,
        (HMENU)7,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND wieza_ktk = CreateWindow(
        L"BUTTON",
        L"wieza_ktk",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        140, 40, 80, 25,
        hwnd,
        (HMENU)8,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND wieza_kkt = CreateWindow(
        L"BUTTON",
        L"wieza_kkt",
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        220, 40, 80, 25,
        hwnd,
        (HMENU)9,
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