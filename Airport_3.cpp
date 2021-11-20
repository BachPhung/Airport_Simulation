#include"Airport_3.h"
#include<iostream>
using namespace std;

Airport_3::Airport_3() {
	initialize();
	arrival_runway = new Runway(queue_limit);
	departure_runway = new Runway(queue_limit);
}
Airport_3::Airport_3(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
	arrival_runway = new Runway(queue_limit);
	departure_runway = new Runway(queue_limit);
}
Airport_3::~Airport_3() {
	delete arrival_runway;
	delete departure_runway;
}

void Airport_3::run_idle(int time, string runway)
{
    cout << time << ": Runway " << runway << " is idle." << endl;
}
void Airport_3::initialize() {
    cout << "This program simulates an airport with two runways." << endl
        << "One runway is primarily for arrivals and one for departures" << endl
        << "One plane can land on arrivals runway and depart on departure runway"
        << "in each unit of time." << endl
        << "if one runway is idle, the other can be used"
        << "if the arrivals queue is full, the arrivals will be diverted to departures\n";
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? on each runway" << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable =false;
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

void Airport_3::run() {
    int flight_number = 0;
    Plane moved_plane;   // plane moved to other runway
    bool stop = false;  // stop takeoff while landing queue is full
    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals= !stop ? variable.poisson(arrival_rate) : 0;
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway->can_land(current_plane) != success) {
                stop = true;             // this variable is used to stop takeoff activity;
                current_plane.refuse();  // when the landing queue is full, refuse all the comming planes until clear the backlogs
                departure_runway->clearTakeoffQueue();   // stop take off queue
                for (int j = 0; j < (queue_limit / 2) / 2; j++) {
                    arrival_runway->movePlaneToOtherRunway(current_time, moved_plane);
                    departure_runway->can_land(moved_plane);  
                }
            }         
            if (departure_runway->checkEmptyTakeoff() && arrival_runway->getLandingSize()>1 ) {
                //When departure runway is empty, add landing plane from landing_queue of arrival runway
                arrival_runway->movePlaneToOtherRunway(current_time, moved_plane);
                moved_plane.setTimeMoved(current_time);
                departure_runway->can_land(moved_plane);  
                arrival_runway->fixChangeLandingCount();
            }
            
        }
        int number_departures = variable.poisson(departure_rate);
        if (!stop) {
            for (int i = 0; i < number_departures; i++) {
                Plane current_plane(flight_number++, current_time, departing);
                if (departure_runway->can_depart(current_plane) != success  || departure_runway->getTakeoffSize()>1) {
                    if (arrival_runway->checkEmptyLanding()) {
                        departure_runway->movePlaneToOtherRunway(current_time, moved_plane);
                        moved_plane.setTimeMoved(current_time);
                        arrival_runway->can_depart(moved_plane);
                        departure_runway->fixChangeTakeoffCount();
                    }
                    else {
                        current_plane.refuse();
                    }
                }
            }
        }
        Plane moving_plane;
        switch (arrival_runway->activity(current_time, moving_plane)) {
        case land: {
            moving_plane.land(current_time);
            break;
            }
        case takeoffs: {
            moving_plane.fly(current_time);
            arrival_runway->serveTakeOffFromOtherRunway(current_time, moving_plane);
            break;
            }
        case idle: {
            run_idle(current_time,"arrival");
            break;
            }
        }

        switch (departure_runway->activity(current_time, moving_plane)) {
        case land: {
            moving_plane.land(current_time);
            departure_runway->serveLandingFromOtherRunway(current_time, moving_plane);
            break;
        }
        case takeoffs: {
            moving_plane.fly(current_time);
            break;
        }
        case idle: {
            run_idle(current_time,"departure");
            break;
        }
        }
        if (stop) {
            if (arrival_runway->checkEmptyLanding()) {
                stop = false;
            }
        }
    }
}

void Airport_3::shut_down()
{
    cout << "---------------------------------\n";
    cout << "Stats for Arrival Runway\n";
    cout << "---------------------------------\n";

    arrival_runway->shut_down(end_time);

    cout << "---------------------------------\n";
    cout << "Stats for Departure Runway\n";
    cout << "---------------------------------\n";

    departure_runway->shut_down(end_time);
}


