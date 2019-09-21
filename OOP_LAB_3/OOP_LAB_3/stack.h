#pragma once
#include "figure.h"
#include <iostream>

struct StackElement
{
	QuadFigure* figure;
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
	void push(QuadFigure* add_element);
	QuadFigure pop();
	// ����� ��������
	bool search(QuadFigure required_element);
	// ��������� ���������� ���������
	int size();
	// ���������� ����������
	void save(std::string namefile);
	// ���������� �����������
	void print();
};