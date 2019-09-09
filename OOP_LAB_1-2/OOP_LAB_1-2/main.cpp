  
#include <iostream>
#include "figure.h"
#include "utils.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	LPCSTR CLASS_NAME = "Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	std::string command;
	bool isRunning = true;

	while (isRunning)
	{
		std::getline(std::cin, command);
		if (command == "draw contur")
		{
			// Create the window
			HWND hwnd = CreateWindowEx(
				0,                              // Optional window styles.
				CLASS_NAME,                     // Window class
				"Learn to Program Windows",    // Window text
				WS_OVERLAPPEDWINDOW,            // Window style

				// Size and position
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

				NULL,       // Parent window    
				NULL,       // Menu
				hInstance,  // Instance handle
				NULL        // Additional application data
			);
			ShowWindow(hwnd, nCmdShow);

			QuadFigure fig;
			read_from_file("test.txt", fig);

			MSG msg = { };

			while (GetMessage(&msg, NULL, 0, 0))
			{
				HDC hdc = GetDC(hwnd);
				try
				{
					fig.draw_figuration(hdc, hwnd);
				}
				catch (const char* error)
				{
					std::cout << "error: " << error << std::endl;
				}
				ReleaseDC(hwnd, hdc);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if (command == "quit" || command == "q")
			isRunning = false;
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
