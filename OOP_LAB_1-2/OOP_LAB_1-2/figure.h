#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>

class QuadFigure
{
private:
	POINT points[4];
	COLORREF pen_color;
	COLORREF brush_color;
	int depth_pen;
	bool inside(POINT a, POINT b, POINT c, POINT check);
public:
	QuadFigure(POINT *points, COLORREF pen_color, COLORREF brush_color, int depth_pen);
	// set
	int set_point(int number, int x, int y);
	int set_points(POINT *point);
	int set_pen_color(int R, int G, int B);
	int set_brush_color(int R, int G, int B);
	int set_depth_pen(int value);
	// get
	POINT get_point(int number);
	COLORREF get_pen_color();
	COLORREF get_brush_color();
	int get_depth_pen();
	// other
	int move(int x, int y);
	int draw(HDC &hdc);
	int save(char *namefile);
};

