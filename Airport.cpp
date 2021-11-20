#include"Airport.h"
#include<iostream>
using namespace std;

Airport::Airport()
    : end_time{ 1 }, queue_limit{ 1 }, arrival_rate{ 0.1 }, departure_rate{ 0.1 }
{}

Airport::Airport(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : end_time{ endTime }, queue_limit{ queueLimit }, arrival_rate{ arrivalRate }, departure_rate{ departureRate }
{}

Airport::~Airport(){}

void Airport::run_idle(int time) {
/*  
    Post: The specified time is printed with a message that the runway is idle.
*/
    cout << time << ": Runway is idle." << endl;
}