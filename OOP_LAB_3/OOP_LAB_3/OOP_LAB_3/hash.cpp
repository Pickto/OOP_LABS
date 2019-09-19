#include "hash.h"

int hash_string(std::string str)
{
	int hash = 0;
	for (int i = 0; i < str.size(); i++)
		hash += (i + 1) * str[i];

	return hash;
}