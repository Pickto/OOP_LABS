#pragma once
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string>
#include "hash.h"

class Filled
{
protected:
	COLORREF brush_color;
	int brush_style;
public:
	void set_brush_color(int R, int G, int B);
	void set_brush_style(int hash);

	COLORREF get_brush_color();
	const char* get_brush_style();
};