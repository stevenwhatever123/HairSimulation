#pragma once
#include "Types.h"

#include <Spring.h>

class Strand
{
private:

public:

	std::vector<Spring*> springs;

public:

	Strand();
	~Strand();
};

