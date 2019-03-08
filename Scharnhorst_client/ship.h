#pragma once
#include "includes.h"
#include "movable.h"
class ship : public movable
{
protected:
	float width;
	float length;
	std::string type;

public:
	ship();
	~ship();
};

