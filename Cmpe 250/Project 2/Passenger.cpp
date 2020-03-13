#include "Passenger.h"


Passenger::Passenger(int _arrive, int _board, int _luggage, int _security, string _vip, string _online){

    this->arrive = _arrive;
    this->board = _board;
    this->luggage = _luggage;
    this->security = _security;
    this->vip = _vip;
    this->online = _online;
    this->lastTime = _arrive;

}

Passenger::Passenger(const Passenger& passenger){

    this->arrive = passenger.arrive;
    this->board = passenger.board;
    this->luggage = passenger.luggage;
    this->security = passenger.security;
    this->vip = passenger.vip;
    this->online = passenger.online;
    this->lastTime = passenger.lastTime;

}

Passenger& Passenger::operator=(const Passenger& passenger){

    this->arrive = passenger.arrive;
    this->board = passenger.board;
    this->luggage = passenger.luggage;
    this->security = passenger.security;
    this->vip = passenger.vip;
    this->online = passenger.online;
    this->lastTime = passenger.lastTime;

    return *this;

}









