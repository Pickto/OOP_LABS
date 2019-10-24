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

	virtual void set_point(int number, int x, int y) = 0;
public:
	virtual ~Shape();

	virtual void set_points(POINT* points, int count_points) = 0;
	virtual void set_pen_color(int R, int G, int B) = 0;
	virtual void set_pen_style(int hash) = 0;
	virtual void set_pen_depth(int pen_depth) = 0;

	virtual POINT get_point(int number) const = 0;
	virtual int get_count_points() const = 0 ;
	virtual COLORREF get_pen_color() const = 0;
	virtual const char* get_pen_style() const = 0;
	virtual int get_pen_depth() const = 0;

	virtual void draw(HWND hwnd, HDC hdc) const = 0;
	virtual void move(int x, int y) = 0;
	virtual void read(std::ifstream& file) = 0;
	virtual void save(std::ofstream& file) const = 0;
};
