#pragma once
#include "shape.h"
#include "filled.h"
#include "hash.h"

class OutlineQuadFigure : public Shape
{
protected:
	void set_point(int number, int x, int y);

	static bool inside_triangle(POINT a, POINT b, POINT c, POINT check);
public:
	OutlineQuadFigure();

	void set_points(POINT* points, int count_points);
	void set_pen_color(int R, int G, int B);
	void set_pen_style(int hash);
	void set_pen_depth(int pen_depth);

	POINT get_point(int number);
	int get_count_points();
	COLORREF get_pen_color();
	const char* get_pen_style();
	int get_pen_depth();

	void draw(HWND hwnd, HDC hdc);
	void move(int x, int y);
	void read(std::ifstream& file);
	void save(std::ofstream& file);

	static bool is_convex(POINT* points);
};

class FilledQuadFigure : public OutlineQuadFigure, public Filled
{
public:
	void draw(HWND hwnd, HDC hdc);
	void read(std::ifstream& file);
	void save(std::ofstream& file);
};

class CombineQuadFigure : public FilledQuadFigure
{
private:
	OutlineQuadFigure* child;

public:
	CombineQuadFigure(std::ifstream& file);
	~CombineQuadFigure();

	void move(int x, int y);
	void draw(HWND hwnd, HDC hdc);
};
