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
	float actualSpeed;// [m/s]
	std::vector<float> gruboscBurty; 	
	

	std::string type;
	std::string name;


	void accelerate(int, double); //{-1, 0, 1} zmienia pr�dko�� z udzia�em silnika na prz�d, w ty� oraz bez silnika 
	void swim(sf::RenderWindow *, double); //przes�wa i obraca statek raz na klatk� oraz go rysuje(dzi�ki physical::draw kt�re w przysz�o�ci zostanie zmieniona na bitmap�) 
	void spin(bool, double); // natychmiastowy obr�t o akkcelerancj� kontow� w czasie

public:
	ship();
	~ship();
};

