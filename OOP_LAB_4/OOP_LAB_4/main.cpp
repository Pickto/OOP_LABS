#include "quad_figure.h"

#include <stdio.h>
#include<iostream>

void clear(HWND hwnd,HDC hdc)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	FillRect(hdc, &rt, (HBRUSH)(COLOR_WINDOW + 1));
}

void main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	try
	{
		clear(hwnd, hdc);
		Shape* sh = new FilledQuadFigure();
		std::ifstream fl("tests/filled.txt");
		sh->read(fl);
		fl.close();
		sh->draw(hwnd, hdc);
		_getch();
		clear(hwnd, hdc);
		delete sh;
		sh = new OutlineQuadFigure();
		fl.open("tests/outline.txt");
		sh->read(fl);
		fl.close();
		sh->draw(hwnd, hdc);
		_getch();
		clear(hwnd, hdc);
		fl.open("tests/combine.txt");
		Shape* combo_sh = new CombineQuadFigure(fl);
		combo_sh->draw(hwnd, hdc);
		_getch();
		clear(hwnd, hdc);
	}
	catch(const char* error)
	{
		std::cout << error << "\n";
	}
}