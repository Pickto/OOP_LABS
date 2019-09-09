#include <iostream>
#include "figure.h"

int main()
{
	HWND hwnd = GetConsoleWindow();
	//HWND hwnd = FindWindow(TEXT("notepad"), TEXT("Áåçûìÿííûé — Áëîêíîò"));
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));

	QuadFigure fig;
	QuadFigure other_fig;

	while (true)
	{
		try
		{
			RECT rt;
			GetClientRect(hwnd, &rt);
			std::string command;
			std::cin >> command;
			FillRect(hdc, &rt, (HBRUSH)(COLOR_WINDOW + 1));
			if (command == "draw_one")
			{
				std::string param;
				std::string namefile;
				std::cin >> param >> namefile;
				fig.read(namefile);
				if (param == "empty")
					fig.draw_figuration(hwnd, hdc);
				else if (param == "full")
					fig.draw_painted(hwnd, hdc);
			}
			else if (command == "draw_two")
			{
				std::string param_a, param_b;
				std::string namefile_a, namefile_b;
				std::cin >> param_a >> namefile_a >> param_b >> namefile_b;
				fig.read(namefile_a);
				other_fig.read(namefile_b);
				if (fig.is_child(other_fig))
				{
					if (param_b == "full")
						other_fig.draw_painted(hwnd, hdc);
					else if (param_b == "empty")
						other_fig.draw_figuration(hwnd, hdc);
					if (param_a == "full")
						fig.draw_painted(hwnd, hdc);
					else if (param_a == "empty")
						fig.draw_figuration(hwnd, hdc);
				}
				else if (other_fig.is_child(fig))
				{
					if (param_a == "full")
						fig.draw_painted(hwnd, hdc);
					else if (param_a == "empty")
						fig.draw_figuration(hwnd, hdc);
					if (param_b == "full")
						other_fig.draw_painted(hwnd, hdc);
					else if (param_b == "empty")
						other_fig.draw_figuration(hwnd, hdc);
				}
				else
					throw "no one figure is child";
			}
			else if (command == "move")
			{
				std::string param;
				int x, y;
				std::cin >> param >> x >> y;
				fig.move(x, y);
				if (param == "empty")
					fig.draw_figuration(hwnd, hdc);
				else if (param == "full")
					fig.draw_painted(hwnd, hdc);
			}
			else if (command == "quit")
			{
				break;
			}
		}
		catch (const char* error)
		{
			std::cout << "error: " << error << std::endl;
		}
	}
	ReleaseDC(hwnd, hdc);

	return 0;
}
