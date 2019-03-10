#pragma once
#include "includes.h"
#include "movable.h"
class ship : public movable
{
protected:
	float width; // [m]
	float length; // [m]
	float acceleration; // [m/s^2]
	float maxSpeed; // [m/s]
	float turnAcceleration; // <0, 1> R
	float mass; // [kg]
	float enginePower; // [Wat]
	
	
	float actualSpeed;// [m/s]

	std::string type;
	std::string name;

	void calculateAcceleration();


public:
	ship();
	~ship();
};

