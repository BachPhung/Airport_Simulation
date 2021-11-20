#include"Runway.h"
#include<iostream>
#include<string>
using namespace std;

Runway::Runway(int limit) {
	queue_limit = limit;
	num_land_requests = num_takeoffs_requests = 0;
	num_landings = num_takeoffs = 0;
	num_land_refused = num_takeoff_refused = 0;
	num_land_accepted = num_takeoff_accepted = 0;
	land_wait = takeoff_wait = idle_time = 0;
	num_landing_diverted = num_takeoff_diverted = 0;
}
Error_code Runway::can_land(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
	   landing Queue; otherwise, an Error_code of overflow is
	   returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
	Error_code result;
	if (landing.size() < queue_limit)
		result = landing.append(current);
	else
		result = fail;
	num_land_requests++;

	if (result != success)
		num_land_refused++;
	else
		num_land_accepted++;

	return result;
}

Error_code Runway::can_land_5(const Plane& current) {
	Error_code result;
	if (landing.size() < queue_limit)
		result = landing.append(current);
	else
		result = fail;
	num_land_requests++;

	if (result != success)
		num_land_refused++;
	else
		num_land_accepted++;

	int lowestFuelPlaneID = landing.minIndex(); // the order in queue of plane have lowest fuel
	int lowestFuelPlane = landing.minFuel();	// the lowest fuel of that plane
	int distance = landing.getDistanceWithFront(lowestFuelPlaneID);
	if (lowestFuelPlane <= distance) {
		//if the fuel remaining < the distance from that plane to the front of queue
		// -> move that plane to the front of queue and decrement the index of planes that stand forward by 1
		landing.changeOrder(lowestFuelPlaneID);
	}
	return result;
}

Error_code Runway::can_depart(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
	   takeoff Queue; otherwise, an Error_code of overflow is
	   returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
	Error_code result;
	if (takeoff.size() < queue_limit)
		result = takeoff.append(current);
	else
		result = fail;
	num_takeoffs_requests++;
	if (result != success)
		num_takeoff_refused++;
	else
		num_takeoff_accepted++;

	return result;
}
Runway_activity Runway::activity(int time, Plane& moving) {
	/* Post: If the landing Queue has entries, its front Plane is copied to the parameter
	moving and a result land is returned. Otherwise, if the takeoff Queue has
	entries, its front Plane is copied to the parameter moving and a result takeoff
	is returned. Otherwise, idle is returned. Runway statistics are updated.
	Uses: class Extended queue. */
	Runway_activity in_progress;
	if (!landing.empty()) {
		landing.retrieve(moving);
		land_wait += time - moving.started();
		num_landings++;
		in_progress = land;
		landing.serve();
	}
	else if (!takeoff.empty()) {
		takeoff.retrieve(moving);
		takeoff_wait += time - moving.started();
		num_takeoffs++;
		in_progress = takeoffs;
		takeoff.serve();
	}
	else {
		idle_time++;
		in_progress = Runway_activity::idle;
	}
	return in_progress;
}
void Runway::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
	cout << "---------------------------------\n"
		<< "Simulation has concluded after " << time << " time units." << endl
		<< "Total number of planes processed "
		<< (num_land_requests + num_takeoffs_requests) << endl
		<< "Total number of planes asking to land "
		<< num_land_requests << endl
		<< "Total number of planes asking to take off "
		<< num_takeoffs_requests << endl
		<< "Total number of planes accepted for landing "
		<< num_land_accepted << endl
		<< "Total number of planes accepted for takeoff "
		<< num_takeoff_accepted << endl
		<< "Total number of planes refused for landing "
		<< num_land_refused << endl
		<< "Total number of planes refused for takeoff "
		<< num_takeoff_refused << endl
		<< "Total number of planes that landed "
		<< num_landings << endl
		<< "Total number of planes that took off "
		<< num_takeoffs << endl
		<< "Total number landing planes diverted to other runway "
		<< num_landing_diverted << endl
		<< "Total number taking off planes diverted to other runway "
		<< num_takeoff_diverted << endl
		<< "Total number of planes left in landing queue "
		<< landing.size() << endl
		<< "Total number of planes left in takeoff queue "
		<< takeoff.size() << endl;
	cout << "Percentage of time runway idle "
		<< 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
	cout << "Average wait in landing queue ";
	num_landings != 0 ? cout << ((float)land_wait) / ((float)num_landings) : cout << 0 ;
	cout << " time units";
	cout << endl
		<< "Average wait in takeoff queue ";
	num_takeoffs != 0 ? cout << ((float)takeoff_wait) / ((float)num_takeoffs) : cout << 0;
	cout << " time units" << endl;
	cout << "Average observed rate of planes wanting to land "
		<< ((float)num_land_requests) / ((float)time)
		<< " per time unit" << endl;
	cout << "Average observed rate of planes wanting to take off "
		<< ((float)num_takeoffs_requests) / ((float)time)
		<< " per time unit" << endl;
}

void Runway::shut_down_5(int time) const /*
Post: Runway usage statistics are summarized and printed.
*/

{
	cout << "---------------------------------\n"
		<< "Simulation has concluded after " << time << " time units." << endl
		<< "Total number of planes processed "
		<< (num_land_requests + num_takeoffs_requests) << endl
		<< "Total number of planes asking to land "
		<< num_land_requests << endl
		<< "Total number of planes asking to take off "
		<< num_takeoffs_requests << endl
		<< "Total number of planes accepted for landing "
		<< num_land_accepted << endl
		<< "Total number of planes accepted for takeoff "
		<< num_takeoff_accepted << endl
		<< "Total number of planes refused for landing "
		<< num_land_refused << endl
		<< "Total number of planes refused for takeoff "
		<< num_takeoff_refused << endl
		<< "Total number of planes that landed "
		<< num_landings << endl
		<< "Total number of planes that took off "
		<< num_takeoffs << endl
		<< "Total number of planes left in landing queue "
		<< landing.size() << endl
		<< "Total number of planes left in takeoff queue "
		<< takeoff.size() << endl
		<< "Total number of planes crashed in the landing queue "
		<< num_landing_crashed << endl;
	cout << "Percentage of time runway idle "
		<< 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
	cout << "Average wait in landing queue ";
	num_landings != 0 ? cout << ((float)land_wait) / ((float)num_landings) : cout << 0;
	cout << " time units";
	cout << endl
		<< "Average wait in takeoff queue ";
	num_takeoffs != 0 ? cout << ((float)takeoff_wait) / ((float)num_takeoffs) : cout << 0;
	cout << " time units" << endl;
	cout << "Average observed rate of planes wanting to land "
		<< ((float)num_land_requests) / ((float)time)
		<< " per time unit" << endl;
	cout << "Average observed rate of planes wanting to take off "
		<< ((float)num_takeoffs_requests) / ((float)time)
		<< " per time unit" << endl;
}

int Runway::getLandingSize() {
	return this->landing.size();
}

int Runway::getTakeoffSize() {
	return this->takeoff.size();
}

bool Runway::checkEmptyLanding() {
	return this->landing.empty();
}
bool Runway::checkEmptyTakeoff() {
	return this->takeoff.empty();
}

void Runway::idle() {
	this->idle_time++;
}

void Runway::clearTakeoffQueue() {
	this->takeoff.clear();
}

void Runway::fixChangeLandingCount() {
	//this->num_land_refused--;
	num_landing_diverted++;
	//num_land_refused--;
}

void Runway::fixChangeTakeoffCount() {
	//this->num_takeoff_refused--;
	num_takeoff_diverted++;
	//num_takeoff_refused--;
}

Runway_activity Runway::movePlaneToOtherRunway(int time, Plane& moving) {
	Runway_activity in_progress;
	if (!landing.empty()) {
		landing.retrieve(moving);
		land_wait += time - moving.started();
		landing.serve();
		in_progress = land;
	}
	if (!takeoff.empty()) {
		takeoff.retrieve(moving);
		takeoff_wait += time - moving.started();
		takeoff.serve();
		in_progress = takeoffs;
	}
	else {
		//idle_time++;
		in_progress = Runway_activity::idle;
	}
	return in_progress;
}

Runway_activity Runway::serveLandingFromOtherRunway(int time, Plane& current) {
	land_wait += time - current.getTimeMoved();
	//num_landings++;
	return land;
}

Runway_activity Runway::serveTakeOffFromOtherRunway(int time, Plane& current) {
	land_wait += time - current.getTimeMoved();
	//num_takeoffs++;
	return takeoffs;
}

Runway_activity Runway::activity_3(int time, Plane& current) {
	/* Post: If the landing Queue has entries, its front Plane is copied to the parameter
	moving and a result land is returned. Otherwise, if the takeoff Queue has
	entries, its front Plane is copied to the parameter moving and a result takeoff
	is returned. Otherwise, idle is returned. Runway statistics are updated.
	Uses: class Extended queue. */
	Runway_activity in_progress;
	if (!landing.empty()) {
		landing.retrieve(current);
		land_wait += time - current.started();
		num_landings++;
		in_progress = land;
		landing.serve();
	}
	else if (!takeoff.empty()) {
		takeoff.retrieve(current);
		takeoff_wait += time - current.started();
		num_takeoffs++;
		in_progress = takeoffs;
		takeoff.serve();
	}
	else {
		in_progress = Runway_activity::idle;
	}
	return in_progress;
}


Runway_activity Runway::activity_5(int time, Plane& current) {
	/* Post: If the landing Queue has entries, its front Plane is copied to the parameter
	moving and a result land is returned. Otherwise, if the takeoff Queue has
	entries, its front Plane is copied to the parameter moving and a result takeoff
	is returned. Otherwise, idle is returned. Runway statistics are updated.
	Uses: class Extended queue. */
	Runway_activity in_progress;
	if (!landing.empty()) {			// remove plane exhausted fuel from landing queue.
		landing.retrieve(current);
		if (current.getFuel() <= 0) {
			num_landing_crashed++;
			landing.serve();
		}
	}

	if (!landing.empty()) {
		landing.retrieve(current);
		land_wait += time - current.started();
		num_landings++;
		in_progress = land;
		landing.serve();
		landing.reduceFuel();
	}
	else if (!takeoff.empty()) {
		takeoff.retrieve(current);
		takeoff_wait += time - current.started();
		num_takeoffs++;
		in_progress = takeoffs;
		takeoff.serve();
	}
	else {
		in_progress = Runway_activity::idle;
	}
	return in_progress;
}