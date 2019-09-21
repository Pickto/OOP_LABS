#include "stack.h"

Open_Stack::Open_Stack() : count_element(0)
{
	top = NULL;
}

Open_Stack::~Open_Stack()
{
	StackElement* temp;

	while (top != NULL)
	{
		temp = top;
		top = top->next;
		delete temp;
	}

	count_element = 0;
}

void Open_Stack::push(QuadFigure* add_element)
{
	if (top == NULL)
	{
		top = new StackElement;
		top->figure = add_element;
		top->next = NULL;
	}
	else
	{
		StackElement* temp = new StackElement;
		temp->figure = add_element;
		temp->next = top;
		top = temp;
	}

	count_element++;
}

QuadFigure Open_Stack::pop()
{
	if (top == NULL)
		throw "stack is empty";

	QuadFigure* pop_element = top->figure;

	StackElement* temp = top;
	top = top->next;
	delete temp;

	count_element--;

	return *pop_element;
}

bool Open_Stack::search(QuadFigure required_element)
{
	StackElement* temp = top;
	while (temp != NULL)
	{
		if (*(temp->figure) == required_element)
			return true;

		temp = temp->next;
	}

	return false;
}

int Open_Stack::size()
{
	return count_element;
}

void Open_Stack::save(std::string namefile)
{
	std::ofstream file(namefile);

	StackElement* temp = top;
	int i = 1;
	
	while (temp != NULL)
	{
		temp->figure->save(namefile, file);
		temp = temp->next;
	}

	file.close();
}

void Open_Stack::print()
{
	StackElement* temp = top;
	POINT print_point;

	while (temp != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			print_point = temp->figure->get_point(i);
			std::cout << print_point.x << ", " << print_point.y <<"\n";
		}

		std::cout << "\n";
		temp = temp->next;
	}
}
