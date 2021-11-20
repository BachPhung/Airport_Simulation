#pragma once
#include"Airport.h"
#include"Plane.h"
#include"Runway.h"
class Airport_5 : public Airport {
private:
	Runway* runway;
public:
	Airport_5();
    Airport_5(int end_time, int queue_limit, double arrival_rate, double departure_rate);
    ~Airport_5();
    void initialize() override;
    void run() override;
    void shut_down() override;
};