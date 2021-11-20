#pragma once
#include"Airport.h"
#include"Plane.h"
#include"Runway.h"
class Airport_1 : public Airport {
private:
	Runway* runway;
public:
    Airport_1( );
    Airport_1(int end_time, int queue_limit, double arrival_rate, double departure_rate);
    ~Airport_1();
    void initialize() override;
    void run() override;
    void shut_down() override;
};