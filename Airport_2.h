#pragma once
#include"Airport.h"
#include"Plane.h"
#include"Runway.h"
class Airport_2 : public Airport {
private:
	Runway* arrival_runway;
	Runway* departure_runway;
public:
	Airport_2();
	Airport_2(int end_time, int queue_limit, double arrival_rate, double departure_rate);
	~Airport_2();
	void initialize() override;
	void run() override;
	void shut_down() override;
};