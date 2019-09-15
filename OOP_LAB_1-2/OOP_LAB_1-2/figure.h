#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>
#include "hash.h"

class QuadFigure
{
private:
	POINT points[4];
	COLORREF pen_color;
	COLORREF brush_color;
	int depth_pen;
	int pen_style;
	int brush_style;

	void set_point(int number, int x, int y); // изменяет положение одной точки под номером number

	static bool inside_triangle(POINT a, POINT b, POINT c, POINT check); // находится ли точка check в треугольнике abc
	
public:
	QuadFigure();
	// set
	void set_points(POINT* point); // изменяет все точки
	void set_pen_color(int R, int G, int B); // изменяет цвет пера
	void set_brush_color(int R, int G, int B); // изменяет цвет кисти
	void set_depth_pen(int depth_pen); // изменяет толщину пера
	void set_pen_style(int pen_style); // изменяет стиль пера
	void set_brush_style(int brush_style); //изменяет стиль кисти
	// get
	POINT get_point(int number); // возвращает точку с номером number
	COLORREF get_pen_color(); // возвращает цвет пера
	COLORREF get_brush_color(); // возвращает цвет кисти
	int get_depth_pen(); // возвращает толщину пера
	const char* get_pen_style(); // возвращает стиль пера
	const char* get_brush_style(); // возвращает стиль кисти
	// other
	void move(int x = 0, int y = 0); // передвижение фигуры на ветор (x, y)
	void draw_figuration(HWND hwnd, HDC hdc); // рисует контур
	void draw_painted(HWND hwnd, HDC hdc); // рисует закрашенную 
	void save(std::string namefile); // сохраняет объект в файл с именем namefile
	void read(std::string namefile); // загружает объект из файла с именем namefile
	bool is_child(QuadFigure& other_fig); // проверяет лежит ли объект внутри other_fig
	bool in_rect_window(HWND hnwd); // входит ли фигура в окно
	static bool is_convex(POINT* points); // проверка на выпуклость фигуры
};

