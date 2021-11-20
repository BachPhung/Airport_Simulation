#include<iostream>
#include"Airport.h"
#include"Airport_1.h"
#include"Airport_2.h"
#include"Airport_3.h"
#include"Airport_4.h"
#include"Airport_5.h"

using namespace std;

int main()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{   
    Airport* airport = new Airport_5();
    airport->run();
    airport->shut_down();
    
    
    

    return 0;
}
