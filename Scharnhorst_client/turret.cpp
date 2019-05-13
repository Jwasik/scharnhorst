#include "pch.h"
#include "turret.h"


turret::turret()
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(-40, 0));
	shape.setPoint(1, sf::Vector2f(40, 0));
	shape.setPoint(2, sf::Vector2f(0, -50));
	type = "";
	shipOrigin = sf::Vector2f(0, 0);
	distanceFromShipOrigin = 40;
	angleFromShipOrigin = 0;
	restrictedArea[0] = 0;
	restrictedArea[1] = 0;



}

turret::turret(std::string ntype, sf::Vector2f nshipOrigin, float ndistanceFromShipOrigin, float nangleFromShipOrigin, vector<shared_ptr<barrel>> nbarrels) : type(ntype), shipOrigin(nshipOrigin), distanceFromShipOrigin(ndistanceFromShipOrigin),
angleFromShipOrigin(nangleFromShipOrigin), barrels(nbarrels)
{
	

	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, -50));
	shape.setPoint(1, sf::Vector2f(-20, 0));
	shape.setPoint(2, sf::Vector2f(20, 0));
	shape.setFillColor(sf::Color(255, 0, 0));

	deleteOrigin();
	turretAngle = 0;
	rotationSpeed = 10;
	restrictedArea[0] = 100;
	restrictedArea[1] = 260;

	if (restrictedArea[0] != restrictedArea[1])
		if (restrictedArea[0] > restrictedArea[1])
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1] + 360) / 2);
			middleOfLockedArea = middleOfLockedArea % 360;
		}
		else
		{
			middleOfLockedArea = ((restrictedArea[0] + restrictedArea[1]) / 2);
		}
	else
		middleOfLockedArea = 0;


	


}

void turret::updatePosition(float nshipAngle, float mousAngle, sf::Vector2f nshipOrigin, float dTime)
{
	arestrictedArea[0] = changeAngle(restrictedArea[0], shipAngle);
	arestrictedArea[1] = changeAngle(restrictedArea[1], shipAngle);
	
	float howManyDegreeToTurret = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), changeAngle(turretAngle, shipAngle));
	float howManyDegreeToMouse = howManyDegreeFrom(changeAngle(middleOfLockedArea, shipAngle), mousAngle);


	shipOrigin = nshipOrigin;
	shipAngle = nshipAngle;
	position = sf::Vector2f(distanceFromShipOrigin*sin(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin))), -distanceFromShipOrigin * cos(stopnieNaRadiany(changeAngle(shipAngle, angleFromShipOrigin)))) + shipOrigin;
	shape.setPosition(position);


		if (howManyDegreeToTurret < howManyDegreeToMouse)
		{
			if ((howManyDegreeToMouse - howManyDegreeToTurret) < rotationSpeed*dTime)
			{
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(turretAngle, shipAngle)))
				{
					turretAngle = movable::changeAngle(turretAngle, -1*rotationSpeed * dTime);
				}
				

			}

		}
		else
		{
			if ((howManyDegreeToTurret - howManyDegreeToMouse) < rotationSpeed*dTime)
			{
			}
			else
			{
				turretAngle = movable::changeAngle(turretAngle, -1 * rotationSpeed * dTime);
				if (howManyDegreeFrom(arestrictedArea[0], arestrictedArea[1]) > howManyDegreeFrom(arestrictedArea[0], changeAngle(turretAngle, shipAngle)))
				{
					turretAngle = movable::changeAngle(turretAngle, rotationSpeed * dTime);
				}

				

			}
		}

	shape.setRotation(changeAngle(turretAngle, shipAngle));

	for (auto a : barrels)
	{
		a->updatePosition(changeAngle(turretAngle, shipAngle), position);
		//cout << a->shape.getPosition().x << " " << a->shape.getPosition().y << endl << endl;
	}





}

barrel::barrel()
{
	;
}

barrel::barrel(sf::Vector2f npunkt, sf::ConvexShape nshape)
{
	this->shape = nshape;
	this->punkt = zamienNaPunktNaOkregu(npunkt, sf::Vector2f(0,0));
}

void barrel::updatePosition(float turretAngle, sf::Vector2f nturretOrigin)
{
	this->shape.setPosition(sf::Vector2f(punkt.r*sin(stopnieNaRadiany(changeAngle(turretAngle, punkt.a))), -punkt.r * cos(stopnieNaRadiany(changeAngle(turretAngle, punkt.a)))) + nturretOrigin);

	this->shape.setRotation(turretAngle);
}

void turret::updateRestrictedAreaBy(float moveRestricted)
{
	restrictedArea[0] += moveRestricted;
	restrictedArea[1] += moveRestricted;
	middleOfLockedArea += moveRestricted;

}
float turret::getShipAngle()
{
	return shipAngle;
}
turret::~turret()
{
}

void turret::draw(sf::RenderWindow& window)
{
	for (auto a : barrels)
	{
		window.draw(a->shape);

	}
	window.draw(shape);
	


}

float turret::getAngleByWater()
{
	return this->shape.getRotation();
}

vector<shared_ptr<sf::Vector2f>> turret::getBarrelsPositionsByWater()
{
	vector<shared_ptr<sf::Vector2f>> tem;
	for (auto a : barrels)
	{
		tem.push_back(make_shared<sf::Vector2f>(a->shape.getPosition()));
	}
	return tem;
}

vector<shared_ptr<bullet>> turret::SHOOT()
{
	float temAngle = this->getAngleByWater();
	vector<shared_ptr<bullet>> temb;
	vector<shared_ptr<sf::Vector2f>> temp = this->getBarrelsPositionsByWater();
	/*for (auto aut : temp)
	{
		cout << aut->x << " " << aut->y << endl;

	}
	cout << endl;*/

	sf::ConvexShape temc;
	temc.setPointCount(4);
	temc.setPoint(0, sf::Vector2f(-3, -3));
	temc.setPoint(1, sf::Vector2f(3, -3));
	temc.setPoint(2, sf::Vector2f(3, 3));
	temc.setPoint(3, sf::Vector2f(-3, 3));
	temc.setFillColor(sf::Color(90, 200, 0));

	for(shared_ptr<sf::Vector2f> aut : temp)
	{
		temb.push_back(make_shared<bullet>(bullet("test", temc, 1900, 270, temAngle, *aut)));
	}

	/*for (auto a : temb)
	{
		cout << 
	}*/

	return temb;
}
