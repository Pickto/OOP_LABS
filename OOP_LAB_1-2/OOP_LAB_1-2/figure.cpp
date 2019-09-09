#include "figure.h"

bool QuadFigure::inside(POINT a, POINT b, POINT c, POINT check)
{
	int x1 = (a.x - check.x) * (b.y - a.y) - (b.x - a.x) * (a.y - check.y);
	int x2 = (b.x - check.x) * (c.y - b.y) - (c.x - b.x) * (b.y - check.y);
	int x3 = (c.x - check.x) * (a.y - c.y) - (a.x - c.x) * (c.y - check.y);

	return x1 >= 0 && x2 >= 0 && x3 >= 0 || x1 <= 0 && x2 <= 0 && x3 <= 0;
}

QuadFigure::QuadFigure(POINT* points, COLORREF pen_color, COLORREF brush_color, int depth_pen, int pen_style, int brush_style)
{
	// check convexity
	for (int i = 0; i < 4; i++)
	{
		if (inside(points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4], points[i]))
			throw "non-convex figure";
	}

	for (int i = 0; i < 4; i++)
		set_point(i, points[i].x, points[i].y);

	this->pen_color = pen_color;
	this->brush_color = brush_color;
	set_depth_pen(depth_pen);
	set_pen_style(pen_style);
	set_brush_style(brush_style);
}

QuadFigure::QuadFigure()
{
	for (int i = 0; i < 4; i++)
		points[i] = { 0, 0 };

	pen_color = RGB(255, 255, 255);
	brush_color = RGB(0, 0, 0);
	depth_pen = 0;
	pen_style = PS_SOLID;
	brush_style = -1;
}

// set мб возвращать старые значения
void QuadFigure::set_point(int number, int x, int y) 
{
	if (x < 0 || y < 0)
		throw "Out of range window";

	points[number].x = x;
	points[number].y = y;
}

void QuadFigure::set_points(POINT *points)
{
	for (int i = 0; i < 4; i++)
		set_point(i, points[i].x, points[i].y);
}

void QuadFigure::set_pen_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		throw "Invalid color value";

	pen_color = RGB(R, G, B);
}

void QuadFigure::set_brush_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		throw "Invalid color value";

	brush_color = RGB(R, G, B);
}

void QuadFigure::set_depth_pen(int value)
{
	if (value < 0)
		throw "Invalid depth value";

	depth_pen = value;
}

void QuadFigure::set_pen_style(int pen_style)
{
	if(pen_style < PS_SOLID || pen_style > PS_INSIDEFRAME)
		throw "Invalid pen style";

	this->pen_style = pen_style;
}

void QuadFigure::set_brush_style(int brush_style)
{
	if (brush_style < HS_HORIZONTAL || brush_style > HS_DIAGCROSS)
		throw "Invalid brush style";

	this->brush_style = brush_style;
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

const char* QuadFigure::get_pen_style()
{
	switch (pen_style)
	{
	case PS_SOLID:
		return "PS_SOLID";

	case PS_DASH:
		return "PS_DASH";

	case PS_DOT:
		return "PS_DOT";

	case PS_DASHDOT:
		return "PS_DASHDOT";

	case PS_DASHDOTDOT:
		return "PS_DASHDOTDOT";

	case PS_NULL:
		return "PS_NULL";

	case PS_INSIDEFRAME:
		return "PS_INSIDEFRAME";
	}
}

const char* QuadFigure::get_brush_style()
{
	switch (brush_style)
	{
	case HS_BDIAGONAL:
		return "HS_BDIAGONAL";

	case HS_CROSS:
		return "HS_CROSS";

	case HS_DIAGCROSS:
		return "HS_DIAGCROSS";

	case HS_FDIAGONAL:
		return "HS_FDIAGONAL";

	case HS_HORIZONTAL:
		return "HS_HORIZONTAL";

	case HS_VERTICAL:
		return "HS_VERTICAL";

	default:
		return "NONE";
	}
}

// other
void QuadFigure::move(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;

		if (points[i].x < 0 || points[i].y < 0)
			throw "Out of range window";
	}
}

void QuadFigure::draw_figuration(HDC hdc, HWND hwnd)
{
	RECT size_window;
	GetClientRect(hwnd, &size_window);

	for (int i = 0; i < 4; i++)
	{
		if (inside(points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4], points[i]))
			throw "non-convex figure";

		if (points[i].x > size_window.right || points[i].y > size_window.bottom)
			throw "Out of range window";
	}

	HPEN pen = CreatePen(pen_style, depth_pen, pen_color);
	
	SelectPen(hdc, pen);

	Polygon(hdc, points, 4);
}

void QuadFigure::draw_painted(HDC hdc, HWND hwnd)
{
	HBRUSH brush;

	if (brush_style == -1)
		brush = CreateSolidBrush(brush_color);
	else
		brush = CreateHatchBrush(brush_style, brush_color);

	SelectBrush(hdc, brush);

	draw_figuration(hdc, hwnd);
}

void QuadFigure::save(const char* namefile)
{
	std::ofstream file(namefile);

	file << "POINTS\n";
	
	for (int i = 0; i < 4; i++)
		file << points[i].x << ", " << points[i].y << "\n";

	file << "\nCOLORS\npen ";
	file << (int)GetRValue(pen_color) << ", " << (int)GetGValue(pen_color) << ", " << (int)GetBValue(pen_color) << "\n";
	file << "brush ";
	file << (int)GetRValue(brush_color) << ", " << (int)GetGValue(brush_color) << ", " << (int)GetBValue(brush_color) << "\n";
	file << "\nDEPTH\n" << depth_pen << "\n";
	file << "\nSTYLES\npen " << get_pen_style() << "\n";
	file << "brush " << get_brush_style();
}