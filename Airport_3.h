#pragma once
#include"Airport.h"
#include"Plane.h"
#include"Runway.h"
#include<string>
using namespace std;
class Airport_3 : public Airport {
private:
	Runway* arrival_runway;
	Runway* departure_runway;
public:
	Airport_3();
	Airport_3(int end_time, int queue_limit, double arrival_rate, double departure_rate);
	~Airport_3();
	void initialize() override;
	void run() override;
	void shut_down() override;
	void run_idle(int time, string runway);
};