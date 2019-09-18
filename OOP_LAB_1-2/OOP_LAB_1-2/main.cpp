#include <iostream>
#include "figure.h"
#include "hash.h"


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
	else if (command == "get_point")
	{
		int n;
		std::cin >> n;
		std::cout << fig.get_point(n).x << " " << fig.get_point(n).y << "\n";
	}
	else if (command == "set_points")
	{
		int x, y;
		std::string read;
		POINT points[4];
		for (int i = 0; i < 4; i++)
		{
			std::cin >> x >> read >> y;
			points[i].x = x;
			points[i].y = y;
		}
		fig.set_points(points);
	}
	else if (command == "move")
	{
		int x, y;
		std::string read;
		std::cin >> x >> read >> y;
		fig.move(x, y);
	}
	else if (command == "set_brush_style")
	{
		std::string style;
		std::cin >> style;
		fig.set_brush_style(hash_string(style));
	}
	else if (command == "set_brush_color")
	{
		int R, G, B;
		std::string read;
		std::cin >> R >> read >> G >> read >> B;
		fig.set_brush_color(R, G, B);
	}
	else if (command == "set_pen_style")
	{
		std::string style;
		std::cin >> style;
		fig.set_pen_style(hash_string(style));
	}
	else if (command == "set_pen_color")
	{
		int R, G, B;
		std::string read;
		std::cin >> R >> read >> G >> read >> B;
		fig.set_pen_color(R, G, B);
	}
	else
		throw "Unknown command";
}

int main()
{
	//HWND hwnd = GetConsoleWindow();
	HWND hwnd = FindWindow(TEXT("notepad"), TEXT("Безымянный — Блокнот"));
	HDC hdc = GetDC(hwnd);

	QuadFigure A;
	QuadFigure B;

	std::string figure;

	while (figure != "quit")
	{
		try
		{
			RECT rt;
			GetClientRect(hwnd, &rt);
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
					command_handler(A, hwnd, hdc);
					command_handler(B, hwnd, hdc);
				}
				else
				{
					throw "B isn't child A";
				}
			}
			else if (figure == "BA")
			{
				if (A.is_child(B))
				{
					command_handler(B, hwnd, hdc);
					command_handler(A, hwnd, hdc);
				}
				else
				{
					throw "A isn't child B";
				}
			}
			else if (figure != "quit")
				throw "Unknown command";

		}
		catch (const char* error)
		{
			std::cout << "error: " << error << std::endl;
		}
		
		if (figure != "quit")
			std::getline(std::cin, figure);
	}

	ReleaseDC(hwnd, hdc);

	return 0;
}

