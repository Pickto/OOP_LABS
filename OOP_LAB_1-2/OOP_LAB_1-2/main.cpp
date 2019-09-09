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
	QuadFigure other_fig;

	try
	{
		read_from_file("test.txt", fig);
		read_from_file("other_test.txt", other_fig);
		if (fig.is_child(other_fig))
		{
			other_fig.draw_painted(hwnd, hdc);
			fig.draw_painted(hwnd, hdc);
		}
		else if (other_fig.is_child(fig))
		{
			fig.draw_painted(hwnd, hdc);
			other_fig.draw_painted(hwnd, hdc);
		}
		else 
		{
			std::cout << "eben";
		}
	}
	catch (const char* error)
	{
		std::cout << "error: " << error << std::endl;
	}

	ReleaseDC(hwnd, hdc);

	return 0;
}
