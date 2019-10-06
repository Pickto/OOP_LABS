#include "quad_figure.h"

#include <stdio.h>
#include<iostream>

void main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	try
	{
		Shape* sh = new FilledQuadFigure();
		std::ifstream fl("input.txt");
		sh->read(fl);
		fl.close();
		sh->draw(hwnd, hdc);
		_getch();
		delete sh;
		sh = new OutlineQuadFigure();
		fl.open("input.txt");
		sh->read(fl);
		fl.close();
		sh->draw(hwnd, hdc);
		_getch();
		fl.open("input_combine.txt");
		Shape* combo_sh = new CombineQuadFigure(fl);
		combo_sh->draw(hwnd, hdc);
		_getch();
	}
	catch(const char* error)
	{
		std::cout << error << "\n";
	}
}