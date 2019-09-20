#pragma once
#include "figure.h"

struct StackElement
{
	QuadFigure figure;
	StackElement* next;
};

class Open_Stack
{
private:
	StackElement* top;
	int count_element;

public:
	// ����������� � ����������
	Open_Stack();
	~Open_Stack();
	// ���������� � �������� ��������
	void push(const QuadFigure& add_element);
	QuadFigure& pop();
	// ����� ��������
	bool search(const QuadFigure required_element);
	// ��������� ���������� ���������
	int size();
	// ���������� ����������
	void save(std::string namefile);
};