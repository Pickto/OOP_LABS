#include "filled.h"

void Filled::set_brush_color(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0)
		throw "Invalid color value";

	brush_color = RGB(R, G, B)
}

void Filled::set_brush_style(int hash)
{
	switch (hash)
	{
	case HASH_HS_BDIAGONAL:
		this->brush_style = HS_BDIAGONAL;
		break;

	case HASH_HS_CROSS:
		this->brush_style = HS_CROSS;
		break;

	case HASH_HS_DIAGCROSS:
		this->brush_style = HS_DIAGCROSS;
		break;

	case HASH_HS_FDIAGONAL:
		this->brush_style = HS_FDIAGONAL;
		break;

	case HASH_HS_HORIZONTAL:
		this->brush_style = HS_HORIZONTAL;
		break;

	case HASH_HS_VERTICAL:
		this->brush_style = HS_VERTICAL;
		break;

	default:
		this->brush_style = -1;

	}
}

COLORREF Filled::get_brush_color()
{
	return brush_color;
}

char* Filled::get_brush_style()
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
