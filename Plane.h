#pragma once
#include"Utility.h"
class Plane {
public:
	Plane();
	Plane(int flt, int time, Plane_status status);
	Plane(int flt, int time, Plane_status status, int fuel);   //random an integer number range low to high
	void refuse()const;
	void land(int time) const;
	void fly(int time) const;
	int started() const;
	void setTimeMoved(int time);
	int getTimeMoved();
	int getFuel();
	void reduceFuel();
private:
	int flt_num;
	int clock_start;
	Plane_status state;
	int time_moved; // time when plane is moved to other queue
	int fuel;
};