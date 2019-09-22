#include <iostream>
#include "stack.h"
#include <stack>

int main()
{
	try
	{
		QuadFigure figures[2];

		OpenStack stack;

		for (int i = 0; i < 2; i++)
		{
			stack.push(&figures[i]);
		}

		stack.save("output.txt");

		OpenStack other_stack;

		figures[0].move(100, 100);

		stack.print();

		other_stack.read("input.txt");

	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}

	return 0;
}