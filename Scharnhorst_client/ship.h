#pragma once
#include "includes.h"
#include "movable.h"
class ship : public movable
{
private:

protected:
	float width; // [m]
	float length; // [m]
	float acceleration; // [m/s^2]
	float maxSpeed; // [m/s]
	float maxTurnAcceleration;
	float turnAcceleration; // [stopni/sek]
	float mass; // [kg]
	float enginePower; // [Wat]
	float force;
	float actualSpeed;// [m/s]	
	int gear; //biegi -1 - 4

	std::string type;
	std::string name;

	float calculateAcceleration();
	void accelerate(double); //{-1, 0, 1} zmienia prêdkoœæ z udzia³em silnika na przód, w ty³ oraz bez silnika 
	void swim(sf::RenderWindow &, double); //przesówa i obraca statek raz na klatkê oraz go rysuje(dziêki physical::draw które w przysz³oœci zostanie zmieniona na bitmapê) 
	void spin(bool, double); // natychmiastowy obrót o akkcelerancjê kontow¹ w czasie
	void changeGear(bool); // zmana biegu 0 dla -- 1 dla ++

public:
	ship();
	~ship();
};

