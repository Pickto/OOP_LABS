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

	POINT get_point(int number) const;
	int get_count_points() const;
	COLORREF get_pen_color() const;
	const char* get_pen_style() const;
	int get_pen_depth() const;

	void draw(HWND hwnd, HDC hdc) const;
	void move(int x, int y);
	void read(std::ifstream& file);
	void save(std::ofstream& file) const;

	static bool is_convex(POINT* points);

	bool operator==(const OutlineQuadFigure& compared_element);
};

class FilledQuadFigure : public OutlineQuadFigure, public Filled
{
public:
	void draw(HWND hwnd, HDC hdc);
	void read(std::ifstream& file);
	void save(std::ofstream& file);
	bool operator==(const FilledQuadFigure& compared_element);
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
	bool operator==(CombineQuadFigure& compared_element);
};
