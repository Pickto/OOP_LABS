#include "shape.h"

Shape::~Shape()
{
	delete[] points;
}
