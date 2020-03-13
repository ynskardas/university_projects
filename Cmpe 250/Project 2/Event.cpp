#include "Event.h"
#include <string>
#include <iostream>

using namespace std;

Event::Event(int _time, int _place, Passenger* _passenger){

    this->time = _time;

    this->place = _place;

    this->passenger = _passenger;

}


