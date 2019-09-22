#pragma once
#include "figure.h"
#include <iostream>

struct StackElement
{
	QuadFigure* figure;
	StackElement* next;
};

class OpenStack
{
private:
	StackElement* top; 
	int count_element;

public:
	// ����������� � ����������
	OpenStack();
	~OpenStack();
	// ���������� � �������� ��������
	void push(QuadFigure* add_element);
	QuadFigure pop();
	// ����� ��������
	bool search(QuadFigure required_element);
	// ��������� ���������� ���������
	int size();
	// ���������� ����������
	void save(std::string namefile);
	// ������ �� �����
	void read(std::string namefile);
	// ���������� �����������
	void print();
};