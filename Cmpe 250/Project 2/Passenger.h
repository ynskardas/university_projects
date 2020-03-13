
#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
using namespace std;

class Passenger{

public:


    int arrive;
    int board;
    int luggage;
    int security;
    string vip;
    string online;

    int lastTime;

    Passenger(int _arrive, int _board, int _luggage, int _security, string _vip, string _online);


    Passenger(const Passenger& passenger);
    Passenger& operator=(const Passenger& passenger);


};

#endif //CMPEAİRLİNES_PASSENGER_H
