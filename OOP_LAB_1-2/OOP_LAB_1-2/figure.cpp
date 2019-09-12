#include "figure.h"

bool QuadFigure::inside_triangle(POINT a, POINT b, POINT c, POINT check)
{
	int x1 = (a.x - check.x) * (b.y - a.y) - (b.x - a.x) * (a.y - check.y);
	int x2 = (b.x - check.x) * (c.y - b.y) - (c.x - b.x) * (b.y - check.y);
	int x3 = (c.x - check.x) * (a.y - c.y) - (a.x - c.x) * (c.y - check.y);

	return x1 >= 0 && x2 >= 0 && x3 >= 0 || x1 <= 0 && x2 <= 0 && x3 <= 0;
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
// set 
void QuadFigure::set_point(int number, int x, int y) 
{
	if (number < 0 || number > 4)
		throw "Invalid number point";

	points[number].x = x;
	points[number].y = y;
} 
void QuadFigure::set_points(POINT *points)
{
	if (!QuadFigure::is_convex(points))
		throw "Non-convex figure";

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
void QuadFigure::set_depth_pen(int depth_pen)
{
	if (depth_pen < 0)
		throw "Invalid depth value";

	this->depth_pen = depth_pen;
}
void QuadFigure::set_pen_style(int pen_style)
{
	if(pen_style < PS_SOLID || pen_style > PS_INSIDEFRAME)
		throw "Invalid pen style";

	this->pen_style = pen_style;
}
void QuadFigure::set_brush_style(int brush_style)
{
	if ((brush_style < HS_HORIZONTAL || brush_style > HS_DIAGCROSS) && brush_style != -1)
		throw "Invalid brush style";

	this->brush_style = brush_style;
}
// get
POINT QuadFigure::get_point(int number) 
{
	if (number < 0 || number > 3)
		throw "Out of range";
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
			
	default:
		return "NONE";
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
	}
}
void QuadFigure::draw_figuration(HWND hwnd, HDC hdc)
{
	HPEN pen = CreatePen(pen_style, depth_pen, pen_color);
	
	pen = SelectPen(hdc, pen);

	Polygon(hdc, points, 4);

	SelectPen(hdc, pen);
}
void QuadFigure::draw_painted(HWND hwnd, HDC hdc)
{
	HBRUSH brush;

	if (brush_style == -1)
		brush = CreateSolidBrush(brush_color);
	else
		brush = CreateHatchBrush(brush_style, brush_color);

	brush = SelectBrush(hdc, brush);

	draw_figuration(hwnd, hdc);

	SelectBrush(hdc, brush);
}
void QuadFigure::save(std::string namefile)
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
void QuadFigure::read(std::string namefile)
{
	std::ifstream file(namefile);

	if (!file.is_open())
		throw "Can not open file ";

	std::string read;
	int x, y, R, G, B, depth, read_hash;

	while (file >> read)
	{
		read_hash = hash_string(read);

		switch (read_hash)
		{
		case HASH_POINTS:
			POINT raw_points[4];
			for (int i = 0; i < 4; i++)
			{
				file >> x >> read >> y;
				raw_points[i].x = x;
				raw_points[i].y = y;
			}
			if (!QuadFigure::is_convex(raw_points))
				throw "Non-convex figure";
			set_points(raw_points);
			break;

		case HASH_PEN:
			file >> R >> read >> G >> read >> B;
			set_pen_color(R, G, B);
			break;

		case HASH_BRUSH:
			file >> R >> read >> G >> read >> B;
			set_brush_color(R, G, B);
			break;

		case HASH_DEPTH:
			file >> depth;
			set_depth_pen(depth);
			break;

		case HASH_STYLES:
			file >> read;

			if (read == "pen")
			{
				file >> read;

				read_hash = hash_string(read);

				switch (read_hash)
				{
				case HASH_PS_SOLID:
					set_pen_style(PS_SOLID);
					break;

				case HASH_PS_DASH:
					set_pen_style(PS_DASH);
					break;

				case HASH_PS_DOT:
					set_pen_style(PS_DOT);
					break;

				case HASH_PS_DASHDOT:
					set_pen_style(PS_DASHDOT);
					break;

				case HASH_PS_DASHDOTDOT:
					set_pen_style(PS_DASHDOTDOT);
					break;

				case HASH_PS_NULL:
					set_pen_style(PS_NULL);
					break;

				case HASH_PS_INSIDEFRAME:
					set_pen_style(PS_INSIDEFRAME);
					break;
				}
			}

			file >> read;

			if (read == "brush")
			{
				file >> read;

				read_hash = hash_string(read);

				switch (read_hash)
				{
				case HASH_HS_BDIAGONAL:
					set_brush_style(HS_BDIAGONAL);
					break;

				case HASH_HS_CROSS:
					set_brush_style(HS_CROSS);
					break;

				case HASH_HS_DIAGCROSS:
					set_brush_style(HS_DIAGCROSS);
					break;

				case HASH_HS_FDIAGONAL:
					set_brush_style(HS_FDIAGONAL);
					break;

				case HASH_HS_HORIZONTAL:
					set_brush_style(HS_HORIZONTAL);
					break;

				case HASH_HS_VERTICAL:
					set_brush_style(HS_VERTICAL);
					break;
				}
			}
			break;
		}
	}

	file.close();
}
bool QuadFigure::is_child(QuadFigure& other_fig)
{
	for (int i = 0; i < 4; i++)
		if (!QuadFigure::inside_triangle(other_fig.points[0], other_fig.points[1], other_fig.points[2], points[i]) &&
			!QuadFigure::inside_triangle(other_fig.points[2], other_fig.points[3], other_fig.points[0], points[i]))
			return false;
	return true;
}
bool QuadFigure::in_rect_window(HWND hwnd)
{
	RECT size_window;
	GetClientRect(hwnd, &size_window);

	for (int i = 0; i < 4; i++)
		if (points[i].x > size_window.right || points[i].y > size_window.bottom)
			return false;
	return true;
}
bool QuadFigure::is_convex(POINT* points)
{
	for (int i = 0; i < 4; i++)
		if (QuadFigure::inside_triangle(points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4], points[i]))
			return false;
	return true;
}
