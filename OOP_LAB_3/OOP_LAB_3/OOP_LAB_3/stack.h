#pragma once
#include "figure.h"

struct StackElement
{
	QuadFigure figure;
	StackElement* next;
};