#pragma once
#include "includes.h"
#include "movable.h"
class Ship : public movable
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
	void swim(double); //przesówa i obraca statek raz na klatkê oraz go rysuje(dziêki physical::draw które w przysz³oœci zostanie zmieniona na bitmapê) 
	void spin(bool, double); // natychmiastowy obrót o akkcelerancjê kontow¹ w czasie
	void changeGear(bool); // zmana biegu 0 dla -- 1 dla ++
	void draw(sf::RenderWindow&);

	std::string getType();
	Ship();
	~Ship();
};

