#include "stack.h"
#include "quad_figure.h"

#include <iostream>


int main()
{
	try
	{
		HWND hwnd = GetConsoleWindow();
		//HWND hwnd = FindWindow(TEXT("notepad"), TEXT("Безымянный - Блокнот"));
		HDC hdc = GetDC(hwnd);

		OutlineQuadFigure figures[5];
		std::ifstream fl;

		for (int i = 0; i < 5; i++)
		{
			fl.open("tests/" + std::to_string(i + 1) + ".txt");
			figures[i].read(fl);
			fl.close();
		}

		OpenStack<OutlineQuadFigure> stack;
		stack.push(&figures[0]);
		stack.push(&figures[1]);
		stack.push(&figures[2]);
		stack.push(&figures[3]);
		_getch();
		RECT rt;
		GetClientRect(hwnd, &rt);
		FillRect(hdc, &rt, (HBRUSH)(COLOR_WINDOW + 1));
		OutlineQuadFigure* fig = stack.pop();
		fig->draw(hwnd, hdc);
		_getch();
		bool res = stack.search(figures[2]);
		std::cout << res << std::endl;
		_getch();
		res = stack.search(figures[3]);
		std::cout << res << std::endl;
		_getch();
		stack.print();
		_getch();
		stack[2]->draw(hwnd, hdc);
		_getch();
		stack.save("output.txt");
		_getch();
		fl.open("test1.txt");
		CombineQuadFigure a(fl);
		fl.close();
		fl.open("test2.txt");
		CombineQuadFigure b(fl);
		fl.close();
		std::cout << (a == b);
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}

	_getch();
	return 0;
}