#include <iostream>
#include "figure.h"


void command_handler(QuadFigure &fig, HWND &hwnd, HDC &hdc)
{
	std::string command;
	std::cin >> command;
	if (command == "read")
	{
		std::string namefile;
		std::cin >> namefile;
		fig.read(namefile);
	}
	else if (command == "save")
	{
		std::string namefile;
		std::cin >> namefile;
		fig.save(namefile);
	}
	else if (command == "draw_fill")
	{
		fig.draw_painted(hwnd, hdc);
	}
	else if (command == "draw_figuration")
	{
		fig.draw_figuration(hwnd, hdc);
	}
	else if (command == "set_point")
	{
		std::string read;
		int n, x, y;
		std::cin >> n >> x >> read >> y;
		fig.set_point(n, x, y);
	}
	else if (command == "get_point")
	{
		int n;
		std::cin >> n;
		std::cout << fig.get_point(n).x << fig.get_point(n).y << "\n";
	}
}

int main()
{
	HWND hwnd = GetConsoleWindow();
	//HWND hwnd = FindWindow(TEXT("notepad"), TEXT("Безымянный — Блокнот"));
	HDC hdc = GetDC(hwnd);

	QuadFigure A;
	QuadFigure B;


	while (command != "quit")
	{
		try
		{
			RECT rt;
			GetClientRect(hwnd, &rt);
			std::string figure;
			std::cin >> figure;
			FillRect(hdc, &rt, (HBRUSH)(COLOR_WINDOW + 1));
			if (figure == "A")
				command_handler(A, hwnd, hdc);
			else if (figure == "B")
				command_handler(B, hwnd, hdc);
			else if (figure == "AB")
			{
				if (B.is_child(A))
				{
					A.draw_painted(hwnd, hdc);
					B.draw_painted(hwnd, hdc);
				}
				else
				{
					throw "A isn't child B";
				}
			}
			else if (figure == "BA")
			{
				if (A.is_child(B))

				{
					B.draw_painted(hwnd, hdc);
					A.draw_painted(hwnd, hdc);
				}
				else
				{
					throw "B isn't child A";
				}
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

