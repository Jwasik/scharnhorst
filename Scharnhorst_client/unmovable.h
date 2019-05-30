#pragma once
#include "physical.h"
#include "Hitbox.h"
class unmovable : public physical
{
private:
	Hitbox hitbox;
public:
	unmovable();
	virtual ~unmovable();
};

