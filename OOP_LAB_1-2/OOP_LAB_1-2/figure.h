#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>

class QuadFigure
{
private:
	POINT points[4];
	COLORREF pen_color;
	COLORREF brush_color;
	int depth_pen;
	int pen_style;
	int brush_style;

	bool inside(POINT a, POINT b, POINT c, POINT check);
public:
	QuadFigure();
	QuadFigure(POINT* points, COLORREF pen_color, COLORREF brush_color, int depth_pen, int pen_style, int brush_style);
	// set
	void set_point(int number, int x, int y); // изменяет положение одной точки под номером number
	void set_points(POINT* point); // изменяет все точки
	void set_pen_color(int R, int G, int B); // изменяет цвет пера
	void set_brush_color(int R, int G, int B); // изменяет цвет кисти
	void set_depth_pen(int value);
	void set_pen_style(int pen_style);
	void set_brush_style(int brush_style);
	// get
	POINT get_point(int number);
	COLORREF get_pen_color();
	COLORREF get_brush_color();
	int get_depth_pen();
	const char* get_pen_style();
	const char* get_brush_style();
	// other
	void move(int x, int y);
	void draw_figuration(HDC hdc, HWND hwnd); // рисует контур
	void draw_painted(HDC hdc, HWND hwnd); // рисует закрашенную 
	void save(const char* namefile);
};

