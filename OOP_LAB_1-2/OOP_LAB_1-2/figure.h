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

	bool inside_triangle(POINT a, POINT b, POINT c, POINT check);
public:
	QuadFigure();
	QuadFigure(POINT* points, COLORREF pen_color, COLORREF brush_color, int depth_pen, int pen_style = PS_SOLID, int brush_style = -1);
	// set
	void set_point(int number, int x, int y); // �������� ��������� ����� ����� ��� ������� number
	void set_points(POINT* point); // �������� ��� �����
	void set_pen_color(int R, int G, int B); // �������� ���� ����
	void set_brush_color(int R, int G, int B); // �������� ���� �����
	void set_depth_pen(int value); // �������� ������� ����
	void set_pen_style(int pen_style); // �������� ����� ����
	void set_brush_style(int brush_style); //�������� ����� �����
	// get
	POINT get_point(int number); // ���������� ����� � ������� number
	COLORREF get_pen_color(); // ���������� ���� ����
	COLORREF get_brush_color(); // ���������� ���� �����
	int get_depth_pen(); // ���������� ������� ����
	const char* get_pen_style(); // ���������� ����� ����
	const char* get_brush_style(); // ���������� ����� �����
	// other
	void move(int x = 0, int y = 0);
	void draw_figuration(HWND hwnd, HDC hdc); // ������ ������
	void draw_painted(HWND hwnd, HDC hdc); // ������ ����������� 
	void save(std::string namefile); // ��������� ������ � ���� � ������ namefile
	void read(std::string namefile); // ��������� ������ �� ����� � ������ namefile
	bool is_child(QuadFigure& other_fig); // ��������� ����� �� ������ ������ other_fig
	bool is_convex();
};

