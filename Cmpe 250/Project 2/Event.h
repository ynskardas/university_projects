

#ifndef EVENT_H

#define EVENT_H

#include "Passenger.h"


class Event{

public:

    int time;
    int place;
    Passenger* passenger;


    Event(int _time, int _place, Passenger* _passenger);




    friend bool operator<(const Event& event1, const Event& event2){

        if(event1.time == event2.time){

            if(event1.place == event2.place){

                if(event1.passenger->lastTime == event2.passenger->lastTime){

                    return event1.passenger->arrive > event2.passenger->arrive;

                }
                else{

                    return event1.passenger->lastTime > event2.passenger->lastTime;

                }

            }
            else{

                return event1.place > event2.place;

            }

        }
        else{

            return event1.time > event2.time;
        }


    }

};





#endif //CMPEAİRLİNES_EVENT_H
