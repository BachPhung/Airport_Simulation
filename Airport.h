#pragma once
#include"Plane.h"
#include"Random.h"
#include"Queue.h"
#include"Utility.h"
class Airport {
protected:
	int end_time;
	int queue_limit;
	double arrival_rate, departure_rate;
	Random variable;
public:
	Airport();
	Airport(int end_time, int queue_limit, double arrival_rate, double departure_rate);
	virtual ~Airport();
	virtual void initialize() = 0;
	virtual void run() = 0;
	virtual void run_idle(int time);
	virtual void shut_down() = 0;
};