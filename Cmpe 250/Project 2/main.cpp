#include <iostream>
#include <fstream>
#include <queue>
#include "Passenger.h"
#include "Event.h"


using namespace std;

int check = 0;

struct Compare{

public:

    bool operator()(pair<Passenger, Passenger*> a, pair<Passenger, Passenger*> b)  {

        if(check == 0){

            if(a.first.lastTime == b.first.lastTime){

                return a.first.arrive > b.first.arrive;
            }else{

                return a.first.lastTime > b.first.lastTime;
            }

        }
        else{

            if(a.first.board == b.first.board) {

                return a.first.arrive > b.first.arrive;
            }
            else{

                return a.first.board > b.first.board;
            }

        }

    }

};

priority_queue<pair<Passenger, Passenger*>, vector<pair<Passenger, Passenger*>>, Compare> tailLug;

priority_queue<pair<Passenger, Passenger*>, vector<pair<Passenger, Passenger*>>, Compare> tailSec;

priority_queue<Event> events;

int main() {

   for(int l = 0; l <= 1; l++){

        for(int v = 0; v <= 1; v++){

            for(int f = 0; f <= 1; f++){

                check = f;

                ifstream inp("/home/student/ClionProjects/CmpeAirlines/inputLarge1.txt");
                int n;
                int capLug;
                int capSec;

				inp >> n >> capLug >>capSec;
                int countLug = 0;
                int countSec = 0;

				for(int i = 0; i < n; i++){

                    int arrive;
                    int board;
                    int luggage;
                    int security;
                    string vip;
                    string online;

                    inp >> arrive >> board >> luggage >> security >> vip >> online;
                    Passenger* passenger = new Passenger(arrive, board, luggage, security, vip, online);

					Event* eee = new Event(arrive, 2, passenger);
                    events.push(*eee);

                }

				int sumOfTime = 0;
                int miss = 0;

                while(events.size()){

                    Event check = events.top();
                    events.pop();



                    if(check.place == 2){
                        if(check.passenger->online == "N" && l == 1){

                            check.place = 1;
                            events.push(check);
                        }

                        else{

                            if(countLug < capLug){

                                countLug++;
                                check.time += check.passenger->luggage;
                                check.place = 1;
                                events.push(check);

							}

                            else{

                                pair<Passenger, Passenger*> pairLug = make_pair(*check.passenger, check.passenger);
                                tailLug.push(pairLug);

                            }

                        }
						
					}

                    else if(check.place == 1){

                        if(check.passenger->online == "L" || l == 0){

                            countLug--;
                            if(tailLug.size()){
                                int t = check.time + tailLug.top().second->luggage;
                                Event event(t, 1, tailLug.top().second);

                                events.push(event);
                                tailLug.pop();

                                countLug++;
                            }

                        }

                        if(check.passenger->vip == "V" && v == 1){

                            check.place = 0;
                            events.push(check);
                        }

                        else{

                            if(countSec < capSec){

                                countSec++;
                                check.time+= check.passenger->security;
                                check.place = 0;
                                events.push(check);

                            }

                            else{
                                check.passenger->lastTime = check.time;
                                pair<Passenger, Passenger*> pairSec = make_pair(*check.passenger, check.passenger);
                                tailSec.push(pairSec);

                            }
                        }

                    }
                    else{

                        if(check.passenger->vip == "N" || v == 0){

                            countSec--;
                            if(tailSec.size()){
                                int t = check.time + tailSec.top().second->security;
                                Event event(t, 0, tailSec.top().second);

                                events.push(event);
                                tailSec.pop();
                                countSec++;

                            }

                        }

						sumOfTime += check.time - check.passenger->arrive;

						if(check.time > check.passenger->board){

                            miss++;

                        }

                    }

				}

                float sum = sumOfTime * 1.0;
                float avgTime;
                avgTime = sum / n;

                cout << avgTime << " " << miss << endl;
			}

        }
    }

    return 0;
}

