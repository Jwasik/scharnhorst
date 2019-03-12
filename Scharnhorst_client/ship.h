#pragma once
#include "includes.h"
#include "movable.h"
class ship : public movable
{
private:

protected:
	float width; // [m]
	float length; // [m]
	float maxSpeed; // [m/s]
	float maxTurnAcceleration;
	float turnAcceleration; // [stopni/sek]
	float mass; // [kg]
	float enginePower; // [Wat]
	float force;

	std::string type;
	std::string name;

	float calculateAcceleration();

public:
	int gear; //biegi -1 - 4

	float acceleration; // [m/s^2]
	float actualSpeed;// [m/s]	


	void accelerate(double);
	void swim(sf::RenderWindow *, double); //przes�wa i obraca statek raz na klatk� oraz go rysuje(dzi�ki physical::draw kt�re w przysz�o�ci zostanie zmieniona na bitmap�) 
	void spin(bool, double); // natychmiastowy obr�t o akkcelerancj� kontow� w czasie
	void changeGear(bool); // zmana biegu 0 dla -- 1 dla ++
	ship();
	~ship();
};

