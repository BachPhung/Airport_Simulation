#include<iostream>
#include"Airport_1.h"
using namespace std;
Airport_1::Airport_1() {
	initialize();
	
}

Airport_1::Airport_1(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
	runway = new Runway(queue_limit);
}

Airport_1::~Airport_1() {
	delete runway;
}

void Airport_1::initialize() {
	/* Pre: The user specifies the number of time units in the simulation, the maximal queue
	sizes permitted, and the expected arrival and departure rates for the airport.
	Post: The program prints instructions and initializes the parameters end time,
	queue limit, arrival rate, and departure rate to the specified values.
	Uses: utility function user says yes */
	cout << "This program simulates an airport with only one runway."
		 << endl
		 << "One plane can land or depart in each unit of time." << endl;
	cout << "Up to what number of planes can be waiting to land "
		<< "or take off at any time? " << flush;
	cin >> queue_limit;
	runway = new Runway(queue_limit);
	cout << "How many units of time will the simulation run?" << flush;
	cin >> end_time;
	bool acceptable = false;
	do {
		cout << "Expected number of arrivals per unit time?" << flush;
		cin >> arrival_rate;
		cout << "Expected number of departures per unit time?" << flush;
		cin >> departure_rate;
		if (arrival_rate < 0.0 || departure_rate < 0.0)
			cerr << "These rates nust be nonnegative." << endl;
		else acceptable = true;
		if (acceptable == true && arrival_rate + departure_rate > 1.0) {
			cerr << "Safety Warning: This airport will become saturated." << endl;
		}
	} while (!acceptable);
}

void Airport_1::run() {
	int flight_number = 0;
	for (int current_time = 0; current_time < end_time; current_time++) {
		int number_arrivals = variable.poisson(arrival_rate);
		for (int i = 0; i < number_arrivals; i++) {
			Plane current_plane(flight_number++, current_time, arriving);
			if (runway->can_land(current_plane) != success)
				current_plane.refuse();
		}
		int number_departures = variable.poisson(departure_rate);
		for (int j = 0; j < number_departures; j++) {
			Plane current_plane(flight_number++, current_time, departing);
			if (runway->can_depart(current_plane) != success)
				current_plane.refuse();
		}
		Plane moving_plane;
		switch (runway->activity(current_time,moving_plane)) {
		case land: {
			moving_plane.land(current_time);
			break;
		}
		case takeoffs: {
			moving_plane.fly(current_time);
			break;
		}
		case idle: {
			run_idle(current_time);
		}
		}
	}	
}

void Airport_1::shut_down() {
	runway->shut_down(end_time);
}