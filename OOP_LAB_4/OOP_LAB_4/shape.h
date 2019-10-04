#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>

class Shape
{
protected:
	POINT* points;
	int count_points;

	COLORREF pen_color;
	int pen_style;
	int pen_depth;

	virtual void set_point() = 0;
public:
	virtual void set_points(POINT* points, int count_points) = 0;
	virtual void set_pen_color(int R, int G, int B) = 0;
	virtual void set_pen_style(int hash) = 0;
	virtual void set_pen_depth(int pen_depth) = 0;

	virtual POINT get_point() = 0;
	virtual int get_count_points() = 0;
	virtual COLORREF get_pen_color() = 0;
	virtual int get_pen_style() = 0;
	virtual int get_pen_depth() = 0;

	virtual void draw(HWND hwnd, HDC hdc) = 0;
	virtual void move(int x, int y) = 0;
	virtual void read(const std::ifstream& fl) = 0;
	virtual void save(const std::ifstream& fl) = 0;
};
