#pragma once
#include "includes.h"
#include "movable.h"
#include "turret.h"
#include "Camera.h"



class Ship : public movable
{
private:

public:

	float width; // [m]
	float length; // [m]
	float maxSpeed; // [m/s]
	float maxTurnAcceleration;
	float turnAcceleration; // [stopni/sek]
	float mass; // [kg]
	float enginePower; // [Wat]
	float force;// zale�na od waterResistance
	float waterRezistance; // zale�na od pr�dko�ci 
	float shipStaticPressure; // sta�a op�ywowo�ci kad�uba
	int gear; //biegi -1 - 4
	float acceleration; // [m/s^2]
	float actualSpeed;// [m/s]	
	std::string type;
	std::string name;
	float calculateAcceleration();
	std::vector<std::shared_ptr<turret>> turrets;
	vector<shared_ptr<bullet>> bullets;


public:


	void draw(sf::RenderWindow&);
	void accelerate(double);
	void swim(double); //przes�wa i obraca statek raz na klatk� oraz go rysuje(dzi�ki physical::draw kt�re w przysz�o�ci zostanie zmieniona na bitmap�) 
	void spin(bool, double); // natychmiastowy obr�t o akkcelerancj� kontow� w czasie
	void changeGear(bool); // zmana biegu 0 dla -- 1 dla ++
	void setCannonRotation(float);
	void setTurrets(float mousAngle, float dTime);
	float getCannonRotation();
	
	void SHOOT();

	std::string getType();
	Ship();
	~Ship();
};

