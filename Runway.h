#pragma once
#include"Utility.h"
#include"Queue.h"
#include"Plane.h"
class Runway {
public:
	Runway(int limit);
	Error_code can_land(const Plane& current);
	Error_code can_depart(const Plane& current);
	Error_code can_land_5(const Plane& current);  // check and reorder the queue if necessary
	Runway_activity activity(int time, Plane& current);
	Runway_activity activity_3(int time, Plane& current);
	Runway_activity activity_5(int time, Plane& current);
	void shut_down(int time) const;
	void shut_down_5(int time) const; //add feature print out the number planes crashed
	void idle();
	void fixChangeLandingCount();
	void fixChangeTakeoffCount();
	void clearTakeoffQueue(); // clear the planes from takeoff queue
	int getLandingSize();
	int getTakeoffSize();
	bool checkEmptyLanding();
	bool checkEmptyTakeoff();
	Runway_activity movePlaneToOtherRunway(int time, Plane& moving);
	Runway_activity serveLandingFromOtherRunway(int time, Plane& moving);
	Runway_activity serveTakeOffFromOtherRunway(int time, Plane& moving);
private:
	Extended_queue landing;
	Extended_queue takeoff;
	int queue_limit;
	int num_land_requests;		//number of planes ask to land
	int num_takeoffs_requests;	//number of planes ask to takeoff
	int num_landings;			//number of planes that have landed
	int num_takeoffs;			//number of planes that have taken off
	int num_land_accepted;		//number of planes queued to land
	int num_takeoff_accepted;	//number of planes queued to takeoff
	int num_land_refused;		//number of	landing planes refused
	int num_takeoff_refused;	//number of departing planes refused
	int land_wait;				//total time of planes waiting to land
	int takeoff_wait;			//total time of planes waiting to take off
	int idle_time;				//total time runway is idle
	int num_landing_diverted =0; //  number of landing planes diverted to other runway
	int num_takeoff_diverted =0; //  number of departing planes diverted to other runway
	int num_landing_crashed = 0;
};