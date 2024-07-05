#include <windows.h>
#include <string>
#include <stdlib.h> // for atof
#include "resources.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[] = "CalculatorClass";

// Global variables to hold the handles of the controls
HWND hNum1, hNum2, hResult, hAddButton, hSubtractButton, hMultiplyButton, hDivideButton;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx(
        0,
        szClassName,
        "Calculator",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        400,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        hNum1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 100, 20, hwnd, NULL, NULL, NULL);
        hNum2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 60, 100, 20, hwnd, NULL, NULL, NULL);
        hResult = CreateWindow("STATIC", "Result", WS_CHILD | WS_VISIBLE, 20, 100, 200, 20, hwnd, NULL, NULL, NULL);

        hAddButton = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 150, 20, 50, 20, hwnd, (HMENU)IDC_BUTTON_ADD, NULL, NULL);
        hSubtractButton = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 150, 60, 50, 20, hwnd, (HMENU)IDC_BUTTON_SUBTRACT, NULL, NULL);
        hMultiplyButton = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 210, 20, 50, 20, hwnd, (HMENU)IDC_BUTTON_MULTIPLY, NULL, NULL);
        hDivideButton = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 210, 60, 50, 20, hwnd, (HMENU)IDC_BUTTON_DIVIDE, NULL, NULL);
        break;

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            char num1[256], num2[256];
            double number1, number2, result;
            GetWindowText(hNum1, num1, 256);
            GetWindowText(hNum2, num2, 256);
            number1 = atof(num1);
            number2 = atof(num2);

            switch (LOWORD(wParam))
            {
            case IDC_BUTTON_ADD:
                result = number1 + number2;
                break;
            case IDC_BUTTON_SUBTRACT:
                result = number1 - number2;
                break;
            case IDC_BUTTON_MULTIPLY:
                result = number1 * number2;
                break;
            case IDC_BUTTON_DIVIDE:
                if (number2 != 0)
                {
                    result = number1 / number2;
                }
                else
                {
                    MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                break;
            }
            std::string resultText = "Result: " + std::to_string(result);
            SetWindowText(hResult, resultText.c_str());
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

