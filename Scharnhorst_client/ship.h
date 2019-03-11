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
	float maxTurnAcceleration;
	float turnAcceleration; // [stopni/sek]
	float mass; // [kg]
	float enginePower; // [Wat]
	float actualSpeed;// [m/s]
	std::vector<float> gruboscBurty; 	
	

	std::string type;
	std::string name;

	void calculateAccelerations(); // zmienia akcelerancjê zaleznie od prêdkoœci, dziêki temu po przekroczeniu max nie bêdzie móg³ przyœpieszaæ a im bli¿ej jej tym mu trudniej 

	void accelerate(int); //{-1, 0, 1} zmienia prêdkoœæ z udzia³em silnika na przód, w ty³ oraz bez silnika 
	void swim(sf::RenderWindow *); //przesówa i obraca statek raz na klatkê oraz go rysuje(dziêki physical::draw które w przysz³oœci zostanie zmieniona na bitmapê) 
	void spin(bool); // natychmiastowy obrót o akkcelerancjê kontow¹ w czasie

public:
	ship();
	~ship();
};

