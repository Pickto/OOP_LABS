#include "utils.h"

int hash_string(std::string string)
{
	int hash = 0;
	for (int i = 0; i < string.size(); i++)
		hash += (i + 1) * string[i];

	return hash;
}

bool read_from_file(const char* namefile, QuadFigure& figure)
{
	std::ifstream file(namefile);

	if (!file.is_open())
		return false;

	std::string read;
	int x, y, R, G, B, depth, read_hash;

	while (file >> read)
	{
		read_hash = hash_string(read);

		switch (read_hash)
		{
		case HASH_POINTS:
			for (int i = 0; i < 4; i++)
			{
				file >> x >> read >> y;
				figure.set_point(i, x, y);
			}
			break;

		case HASH_PEN:
			file >> R >> read >> G >> read >> B;
			figure.set_pen_color(R, G, B);
			break;

		case HASH_BRUSH:
			file >> R >> read >> G >> read >> B;
			figure.set_brush_color(R, G, B);
			break;

		case HASH_DEPTH:
			file >> depth;
			figure.set_depth_pen(depth);
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
					figure.set_pen_style(PS_SOLID);
					break;

				case HASH_PS_DASH:
					figure.set_pen_style(PS_DASH);
					break;

				case HASH_PS_DOT:
					figure.set_pen_style(PS_DOT);
					break;

				case HASH_PS_DASHDOT:
					figure.set_pen_style(PS_DASHDOT);
					break;

				case HASH_PS_DASHDOTDOT:
					figure.set_pen_style(PS_DASHDOTDOT);
					break;

				case HASH_PS_NULL:
					figure.set_pen_style(PS_NULL);
					break;

				case HASH_PS_INSIDEFRAME:
					figure.set_pen_style(PS_INSIDEFRAME);
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
					figure.set_brush_style(HS_BDIAGONAL);
					break;

				case HASH_HS_CROSS:
					figure.set_brush_style(HS_CROSS);
					break;

				case HASH_HS_DIAGCROSS:
					figure.set_brush_style(HS_DIAGCROSS);
					break;

				case HASH_HS_FDIAGONAL:
					figure.set_brush_style(HS_FDIAGONAL);
					break;

				case HASH_HS_HORIZONTAL:
					figure.set_brush_style(HS_HORIZONTAL);
					break;

				case HASH_HS_VERTICAL:
					figure.set_brush_style(HS_VERTICAL);
					break;
				}
			}
			break;
		}
	}

	file.close();

	return 0;
}