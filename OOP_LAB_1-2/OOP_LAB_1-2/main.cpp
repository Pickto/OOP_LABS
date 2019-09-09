#include <iostream>
#include "figure.h"
#include "utils.h"

int main()
{
	HWND hwnd = GetConsoleWindow();
	//HWND hwnd = FindWindow(TEXT("notepad"), TEXT("Áåçûìÿííûé — Áëîêíîò"));
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));

	QuadFigure fig;

	try
	{
		read_from_file("test.txt", fig);

		fig.draw_figuration(hdc, hwnd);
		fig.move(150, 0);
		fig.draw_painted(hdc, hwnd);
	}
	catch (const char* error)
	{
		std::cout << "error: " << error << std::endl;
	}

	ReleaseDC(hwnd, hdc);

	return 0;
}
