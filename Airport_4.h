#pragma once
#include"Airport.h"
#include"Plane.h"
#include"Runway.h"
#include<string>
using namespace std;

class Airport_4 : public Airport {
private:
	Runway* arrival_runway;
	Runway* departure_runway;
	Runway* hybrid_runway;
public:
	Airport_4();
	Airport_4(int end_time, int queue_limit, double arrival_rate, double departure_rate);
	~Airport_4();
	void initialize() override;
	void run() override;
	void shut_down() override;
	void run_idle(int time, string runway);
};