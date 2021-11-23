#include<iostream>
#include <climits>
#include"Airport.h"
#include"Airport_1.h"
#include"Airport_2.h"
#include"Airport_3.h"
#include"Airport_4.h"
#include"Airport_5.h"

using namespace std;

int chooseVersion()
{
    int userChoise;

    bool acceptable = false;

    while (true)
    {

        cout << "Welcome to airport simulator.\n "
            << "Please choose the version you would like to run\n"
            << "1: task 1: single shared runway\n"
            << "2: task 2: separate runways for arrival and departure\n"
            << "3: task 3: separate runways for arrival and departure, planes can be moved between\n"
            << "4: task 4: three runways, two always for arrival and departure, one primary for arrival \n"
            << "5: task 5: single shared runway, each arrival plane has its own fuel.\n"
            << "Input: "
            << flush;

        if (cin >> userChoise)
        {
            if (userChoise == 1 || userChoise == 2 || userChoise == 3 || userChoise == 4 || userChoise == 5)
            {
                return userChoise;
            }
        }
        else
        {
            // clear error from cin so it works correctly when asking again.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    return userChoise;
}


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
    int version = chooseVersion();
    Airport* airport = NULL ;
    switch (version)
    {
    case 1:
        airport = new Airport_1();
        break;
    case 2:
        airport = new Airport_2();
        break;
    case 3:
        airport = new Airport_3();
        break;
    case 4:
        airport = new Airport_4();
        break;
    case 5:
        airport = new Airport_5();
        break;
    }
    airport->run();
    airport->shut_down();
    delete airport;
    return 0;
}
