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

	void calculateAccelerations(); // zmienia akcelerancj� zaleznie od pr�dko�ci, dzi�ki temu po przekroczeniu max nie b�dzie m�g� przy�piesza� a im bli�ej jej tym mu trudniej 

	void accelerate(int); //{-1, 0, 1} zmienia pr�dko�� z udzia�em silnika na prz�d, w ty� oraz bez silnika 
	void swim(sf::RenderWindow *); //przes�wa i obraca statek raz na klatk� oraz go rysuje(dzi�ki physical::draw kt�re w przysz�o�ci zostanie zmieniona na bitmap�) 
	void spin(bool); // natychmiastowy obr�t o akkcelerancj� kontow� w czasie

public:
	ship();
	~ship();
};

