#pragma once
#include "hash.h"
#include "figure.h"

int hash_string(std::string string);

bool read_from_file(const char* namefile, QuadFigure& figure);