#include "quad_figure.h"

void OutlineQuadFigure::set_point(int number, int x, int y)
{
	if (number < 0 || number > 4)
		throw "Invalid number point";

	points[number].x = x;
	points[number].y = y;
}

bool OutlineQuadFigure::inside_triangle(POINT a, POINT b, POINT c, POINT check)
{
	int x1 = (a.x - check.x) * (b.y - a.y) - (b.x - a.x) * (a.y - check.y);
	int x2 = (b.x - check.x) * (c.y - b.y) - (c.x - b.x) * (b.y - check.y);
	int x3 = (c.x - check.x) * (a.y - c.y) - (a.x - c.x) * (c.y - check.y);

	return x1 >= 0 && x2 >= 0 && x3 >= 0 || x1 <= 0 && x2 <= 0 && x3 <= 0;
}

OutlineQuadFigure::OutlineQuadFigure()
{
	points = new POINT[4];
	count_points = 4;
}

void OutlineQuadFigure::set_points(POINT* points, int count_points)
{
	if (!OutlineQuadFigure::is_convex(points))
		throw "Non-convex figure";

	for (int i = 0; i < 4; i++)
		set_point(i, points[i].x, points[i].y);
}

void OutlineQuadFigure::set_pen_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		throw "Invalid color value";

	pen_color = RGB(R, G, B);
}

void OutlineQuadFigure::set_pen_style(int hash)
{
	switch (hash)
	{
	case HASH_PS_SOLID:
		this->pen_style = PS_SOLID;
		break;

	case HASH_PS_DASH:
		this->pen_style = PS_DASH;
		break;

	case HASH_PS_DOT:
		this->pen_style = PS_DOT;
		break;

	case HASH_PS_DASHDOT:
		this->pen_style = PS_DASHDOT;
		break;

	case HASH_PS_DASHDOTDOT:
		this->pen_style = PS_DASHDOTDOT;
		break;

	case HASH_PS_NULL:
		this->pen_style = PS_NULL;
		break;

	case HASH_PS_INSIDEFRAME:
		this->pen_style = PS_INSIDEFRAME;
		break;

	default:
		this->pen_style = PS_SOLID;
		break;
	}
}

void OutlineQuadFigure::set_pen_depth(int pen_depth)
{
	if (pen_depth < 0)
		throw "Invalid depth value";

	this->pen_depth = pen_depth;
}

POINT OutlineQuadFigure::get_point(int number)
{
	if (number < 0 || number > 3)
		throw "Out of range";

	return points[number];
}

int OutlineQuadFigure::get_count_points()
{
	return count_points;
}

COLORREF OutlineQuadFigure::get_pen_color()
{
	return pen_color;
}

const char* OutlineQuadFigure::get_pen_style()
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

int OutlineQuadFigure::get_pen_depth()
{
	return pen_depth;
}

void OutlineQuadFigure::draw(HWND hwnd, HDC hdc)
{
	HPEN pen = CreatePen(pen_style, pen_depth, pen_color);

	pen = SelectPen(hdc, pen);

	Polygon(hdc, points, 4);

	SelectPen(hdc, pen);
}

void OutlineQuadFigure::move(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;
	}
}

void OutlineQuadFigure::read(std::ifstream& file)
{
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
			set_points(raw_points, 4);
			break;

		case HASH_PEN:
			file >> R >> read >> G >> read >> B;
			set_pen_color(R, G, B);
			break;

		case HASH_DEPTH:
			file >> depth;
			set_pen_depth(depth);
			break;

		case HASH_STYLES:
			file >> read;

			if (read == "pen")
			{
				file >> read;

				set_pen_style(hash_string(read));
			}
		case HASH_NEW_FIGURE:
			return;
		}
	}
}

void OutlineQuadFigure::save(std::ofstream& file)
{
	file << "POINTS\n";

	for (int i = 0; i < 4; i++)
		file << points[i].x << ", " << points[i].y << "\n";

	file << "\nCOLORS\npen ";
	file << (int)GetRValue(pen_color) << ", " << (int)GetGValue(pen_color) << ", " << (int)GetBValue(pen_color) << "\n";
	file << "\nDEPTH\n" << pen_depth << "\n";
	file << "\nSTYLES\npen " << get_pen_style() << "\n";
	file << "\n______________________________________\n";
}

bool OutlineQuadFigure::is_convex(POINT* points)
{
	for (int i = 0; i < 4; i++)
		if (OutlineQuadFigure::inside_triangle(points[(i + 1) % 4], points[(i + 2) % 4], points[(i + 3) % 4], points[i]))
			return false;

	return true;
}

void FilledQuadFigure::draw(HWND hwnd, HDC hdc)
{
	HBRUSH brush;

	if (brush_style == -1)
		brush = CreateSolidBrush(brush_color);
	else
		brush = CreateHatchBrush(brush_style, brush_color);

	brush = SelectBrush(hdc, brush);

	OutlineQuadFigure::draw(hwnd, hdc);

	SelectBrush(hdc, brush);
}

void FilledQuadFigure::read(std::ifstream& file)
{
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
			set_points(raw_points, 4);
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
			set_pen_depth(depth);
			break;

		case HASH_STYLES:
			file >> read;

			if (read == "pen")
			{
				file >> read;

				set_pen_style(hash_string(read));
			}

			file >> read;

			if (read == "brush")
			{
				file >> read;

				set_brush_style(hash_string(read));
			}
			break;
		case HASH_NEW_FIGURE:
			return;
		}
	}
}

void FilledQuadFigure::save(std::ofstream& file)
{
	file << "POINTS\n";

	for (int i = 0; i < 4; i++)
		file << points[i].x << ", " << points[i].y << "\n";

	file << "\nCOLORS\npen ";
	file << (int)GetRValue(pen_color) << ", " << (int)GetGValue(pen_color) << ", " << (int)GetBValue(pen_color) << "\n";
	file << "brush ";
	file << (int)GetRValue(brush_color) << ", " << (int)GetGValue(brush_color) << ", " << (int)GetBValue(brush_color) << "\n";
	file << "\nDEPTH\n" << pen_depth << "\n";
	file << "\nSTYLES\npen " << get_pen_style() << "\n";
	file << "brush " << get_brush_style() << "\n______________________________________\n";
}

CombineQuadFigure::CombineQuadFigure(std::ifstream& file)
{
	FilledQuadFigure::read(file);
	child = new OutlineQuadFigure();
	child->read(file);

	for (int i = 0; i < 4; i++)
		if (!OutlineQuadFigure::inside_triangle(points[0], points[1], points[2], child->get_point(i)) &&
			!OutlineQuadFigure::inside_triangle(points[2], points[3], points[0], child->get_point(i)))
			throw "Non child";

}

CombineQuadFigure::~CombineQuadFigure()
{
	delete child;
}

void CombineQuadFigure::move(int x, int y)
{
	FilledQuadFigure::move(x, y);
	child->move(x, y);
}

void CombineQuadFigure::draw(HWND hwnd, HDC hdc)
{
	FilledQuadFigure::draw(hwnd, hdc);
	child->draw(hwnd, hdc);
}
