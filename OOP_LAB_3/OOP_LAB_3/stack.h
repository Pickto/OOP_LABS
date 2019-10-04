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
	QuadFigure* pop();
	// ����� ��������
	bool search(const QuadFigure& required_element) const;
	// ��������� ���������� ���������
	int size() const;
	// ���������� ����������
	void save(std::string namefile) const;
	// ������ �� �����
	void read(std::string namefile);
	// ���������� �����������
	void print() const;
	// ������� ��������� []
	QuadFigure* operator[](int index) const;
};