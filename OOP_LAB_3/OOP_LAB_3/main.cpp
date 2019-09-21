#include <iostream>
#include "stack.h"
#include <stack>

int main()
{
	try
	{
		QuadFigure figures[2];

		Open_Stack stack;

		for (int i = 0; i < 2; i++)
		{
			stack.push(&figures[i]);
		}

		stack.save("output.txt");

		figures[0].move(100, 100);

		stack.print();
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}

	return 0;
}