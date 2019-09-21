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
	// конструктор и деструктор
	Open_Stack();
	~Open_Stack();
	// добавление и удаление элемента
	void push(QuadFigure* add_element);
	QuadFigure pop();
	// поиск элемента
	bool search(QuadFigure required_element);
	// получение количества элементов
	int size();
	// сохранение контейнера
	void save(std::string namefile);
	// распечатка содержимого
	void print();
};