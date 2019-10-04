#include "stack.h"

OpenStack::OpenStack() : count_element(0)
{
	top = NULL;
}

OpenStack::~OpenStack()
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

void OpenStack::push(QuadFigure* add_element)
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

QuadFigure* OpenStack::pop()
{
	if (top == NULL)
		throw "stack is empty";

	QuadFigure* pop_element = top->figure;

	StackElement* temp = top;
	top = top->next;
	delete temp;

	count_element--;

	return pop_element;
}

bool OpenStack::search(const QuadFigure& required_element) const
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

int OpenStack::size() const
{
	return count_element;
}

void OpenStack::save(std::string namefile) const
{
	std::ofstream file(namefile);

	StackElement* temp = top;
	int i = 1;
	
	while (temp != NULL)
	{
		temp->figure->save(file);
		temp = temp->next;
	}

	file.close();
}

void OpenStack::read(std::string namefile)
{
	OpenStack temp_stack;
	std::ifstream file(namefile);
	QuadFigure* new_figure = NULL;

	while (file.peek() != EOF)
	{
		new_figure = new QuadFigure();
		new_figure->read(file);
		temp_stack.push(new_figure);
	}
	while (temp_stack.count_element > 1)
	{
		push(temp_stack.pop());
	}
	
	delete new_figure;
}

QuadFigure* OpenStack::operator[](int index) const
{
	if (index >= count_element || index < 0)
		return NULL;

	StackElement* temp = top;

	for (int i = 0; i < index; i++)
		temp = temp->next;

	return temp->figure;
}; 

void OpenStack::print() const
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
