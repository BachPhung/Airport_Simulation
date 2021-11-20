#include"Airport_4.h"
#include<iostream>
using namespace std;

Airport_4::Airport_4() {
	initialize();
	arrival_runway = new Runway(queue_limit);
	departure_runway = new Runway(queue_limit);
	hybrid_runway = new Runway(queue_limit);
}

Airport_4::Airport_4(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
	arrival_runway = new Runway(queue_limit);
	departure_runway = new Runway(queue_limit);
}

Airport_4::~Airport_4(){
	delete arrival_runway;
	delete departure_runway;
	delete hybrid_runway;
}

void Airport_4::initialize() {
    cout << "This program simulates an airport with three runways." << endl
        << "One always reserved for each of landing and takeoff." << endl
        << "And this third used for landing unless the landing queue is empty"<<endl
        << "in which case it can be used for takeoffs." << endl;
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? on each runway" << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable = false;
    do
    {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 2.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_4::run_idle(int time, string runway)
{
    cout << time << ": Runway " << runway << " is idle." << endl;
}

void Airport_4::shut_down()
{
    cout << "---------------------------------\n";
    cout << "Stats for Arrival Runway\n";
    cout << "---------------------------------\n";

    arrival_runway->shut_down(end_time);

    cout << "---------------------------------\n";
    cout << "Stats for Departure Runway\n";
    cout << "---------------------------------\n";

    departure_runway->shut_down(end_time);

    cout << "---------------------------------\n";
    cout << "Stats for Hybrid Runway\n";
    cout << "---------------------------------\n";

    hybrid_runway->shut_down(end_time);
}

void Airport_4::run() {
    int flight_number = 0;
    Plane moved_plane;  // plane moved to other runway
    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway->can_land(current_plane) != success) {
                if (hybrid_runway->can_land(current_plane) == success) {
                    arrival_runway->fixChangeLandingCount();
                }
                else
                    current_plane.refuse();
            }
            if (hybrid_runway->checkEmptyLanding() && arrival_runway->getLandingSize() > 1) {
                //When hybrid_runway is empty, add landing plane form landing_queue of arrival runway
                arrival_runway->movePlaneToOtherRunway(current_time, moved_plane);
                moved_plane.setTimeMoved(current_time);
                hybrid_runway->can_land(moved_plane);
                arrival_runway->fixChangeLandingCount();
            }
        }
        int number_departures = variable.poisson(departure_rate);
        for (int i = 0; i < number_departures; i++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway->can_depart(current_plane) != success) {
                if (hybrid_runway->checkEmptyLanding() && hybrid_runway->getTakeoffSize() < queue_limit) {
                    //When departure_runway is full AND hybrid runway has no landing plane
                    //move takeoff plane from departure_queue to  hybrid_queue
                    departure_runway->movePlaneToOtherRunway(current_time, moved_plane);
                    moved_plane.setTimeMoved(current_time);
                    hybrid_runway->can_depart(moved_plane);
                    departure_runway->fixChangeTakeoffCount();
                }
                else {
                    current_plane.refuse();

                }
            }
            if (hybrid_runway->checkEmptyLanding() && hybrid_runway->getTakeoffSize() < queue_limit && departure_runway->getTakeoffSize() > 1) {
                    //When: 
                    // -hybrid_runway have no landing plane
                    // -the number of takeoff_queue < queue_limit
                    // -departure runway have more than 1 plane in queue
                    departure_runway->movePlaneToOtherRunway(current_time, moved_plane);
                    moved_plane.setTimeMoved(current_time);
                    hybrid_runway->can_depart(moved_plane);
                    departure_runway->fixChangeTakeoffCount();
            }         
        }
        Plane moving_plane;
        switch (arrival_runway->activity(current_time, moving_plane)) {
        case land: {
            moving_plane.land(current_time);
            break;
        }
        case idle: {
            run_idle(current_time,"arrival");
            break;
        }
        }
        switch (departure_runway->activity(current_time, moving_plane)) {
        case takeoffs: {
            moving_plane.fly(current_time);
            break;
        }
        case idle: {
            run_idle(current_time,"departure");
            break;
        }
        }
        switch (hybrid_runway->activity(current_time, moving_plane)) {
        case land: {
            moving_plane.land(current_time);
            hybrid_runway->serveLandingFromOtherRunway(current_time, moving_plane);
            break;
        }
        case takeoffs: {
            moving_plane.fly(current_time);
            hybrid_runway->serveTakeOffFromOtherRunway(current_time, moving_plane);
            break;
        }
        case idle: {
            run_idle(current_time, "hybrid");
            break;
        }
        }
    }
}