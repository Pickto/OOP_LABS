#include "figure.h"

bool QuadFigure::inside(POINT a, POINT b, POINT c, POINT check)
{
	int x1 = (a.x - check.x) * (b.y - a.y) * (b.x - a.x) * (a.y - check.y);
	int x2 = (b.x - check.x) * (c.y - b.y) * (c.x - b.x) * (b.y - check.y);
	int x3 = (c.x - check.x) * (a.y - a.y) * (a.x - a.x) * (c.y - check.y);

	return x1 > 0 && x2 > 0 && x3 > 0 || x1 < 0 && x2 < 0 && x3 < 0;
}

QuadFigure::QuadFigure(POINT *points, COLORREF pen_color, COLORREF brush_color, int depth_pen, int pen_style, int brush_style)
{
	for (int i = 0; i < 4; i++)
	{
		if (points[i].x < 0 || points[i].y < 0)
			throw 0;
	}

	for (int i = 0; i < 4; i++)
	{
		if (inside(points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4], points[i]))
			throw 1;
	}

	for(int i = 0; i < 4; i++)
		this->points[i] = points[i];

	this->pen_color = pen_color;
	this->brush_color = brush_color;
	this->depth_pen = depth_pen;
	this->pen_style = pen_style;
	this->brush_style = brush_style;
}

QuadFigure::QuadFigure()
{
	for (int i = 0; i < 4; i++)
		points[i] = { 0, 0 };

	pen_color = RGB(0, 0, 0);
	brush_color = RGB(0, 0, 0);
	depth_pen = 0;
	pen_style = PS_SOLID;
	brush_style = HS_BDIAGONAL;
}

// set
int QuadFigure::set_point(int number, int x, int y) 
{
	if (x < 0 || y < 0)
		return 1;

	points[number].x = x;
	points[number].y = y;

	return 0;
}

int QuadFigure::set_points(POINT *points)
{
	for (int i = 0; i < 4; i++)
		if (set_point(i, points[i].x, points[i].y))
			return 1;

	return 0;
}

int QuadFigure::set_pen_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		return 1;

	pen_color = RGB(R, G, B);

	return 0;
}

int QuadFigure::set_brush_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		return 1;

	brush_color = RGB(R, G, B);

	return 0;
}

int QuadFigure::set_depth_pen(int value)
{
	if (value < 0)
		return 1;

	depth_pen = value;

	return 0;
}

int QuadFigure::set_pen_style(int pen_style)
{
	this->pen_style = pen_style;

	return 0;
}

int QuadFigure::set_brush_style(int brush_style)
{
	this->brush_style = brush_style;

	return 0;
}

// get
POINT QuadFigure::get_point(int number) 
{
	return points[number];
}

COLORREF QuadFigure::get_pen_color()
{
	return pen_color;
}

COLORREF QuadFigure::get_brush_color()
{
	return brush_color;
}

int QuadFigure::get_depth_pen()
{
	return depth_pen;
}

// other
int QuadFigure::move(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;

		if (points[i].x < 0 || points[i].y < 0)
			return 1;
	}

	return 0;
}

int QuadFigure::draw(HDC& hdc, HWND hwnd)
{


	return 0;
}

int QuadFigure::save(char* namefile)
{
	return 0;
}