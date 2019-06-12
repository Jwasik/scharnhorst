#include "pch.h"
#include "hitbox.h"

hitbox::hitbox(sf::ConvexShape *shape)
{
	int  counter= shape->getPointCount();

	for (int i = 0; i < counter-1; i ++)
	{
		this->odcinki.push_back(odcinek(shape->getPoint(i), shape->getPoint(i+1)));
	}
	this->odcinki.push_back(odcinek( shape->getPoint(shape->getPointCount() - 1), odcinki[0].punkt1 ));
}

hitbox::hitbox()
{

}

bool hitbox::intersects(odcinek *line)
{
	for (auto odcinek : this->odcinki)
	{
		if (line->intersects(odcinek))
		{
			return 1;
		}
	}
	
	return 0;

}



void hitbox::setPosition(sf::Vector2f nposition)
{
	int counter = this->odcinki.size();
	for (int i = 0; i < counter;i++)
	{
		odcinki[i].setPosition(nposition);


	}
}

void hitbox::updateVisual()
{
	int counter = this->odcinki.size();
	for (int i = 0; i < counter; i++)
	{
		odcinki[i].updateVisual();


	}
}
