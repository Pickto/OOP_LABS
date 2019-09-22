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
	// конструктор и деструктор
	OpenStack();
	~OpenStack();
	// добавление и удаление элемента
	void push(QuadFigure* add_element);
	QuadFigure pop();
	// поиск элемента
	bool search(QuadFigure required_element);
	// получение количества элементов
	int size();
	// сохранение контейнера
	void save(std::string namefile);
	// чтение из файла
	void read(std::string namefile);
	// распечатка содержимого
	void print();
};