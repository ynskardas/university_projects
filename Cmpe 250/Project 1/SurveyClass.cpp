#include "SurveyClass.h"

SurveyClass::SurveyClass(){

    this->members = new LinkedList();

}

SurveyClass::SurveyClass(const SurveyClass& other){

    this->members = new LinkedList(*(other.members));

}

SurveyClass& SurveyClass::operator=(const SurveyClass& list){

    delete this->members;
    this->members = new LinkedList(*(list.members));

    return *this;
}

SurveyClass::SurveyClass(SurveyClass&& other){

    this->members = move(other.members);
    other.members = nullptr;

}

SurveyClass& SurveyClass::operator=(SurveyClass&& list){

    delete this->members;
    this->members = move(list.members);

    list.members = nullptr;
    return *this;

}


void SurveyClass::handleNewRecord(string _name, float _amount){

    bool test = true;

    if(this->members->length == 0){

        this->members->pushTail(_name, _amount);


    }

    else{


        Node* jumper = this->members->head;

        while(jumper != nullptr){

            if(!jumper->name.compare(_name)){

                this->members->updateNode(_name, _amount);
                test = false;
                break;
            }

            jumper = jumper->next;

        }

        if(test){

            this->members->pushTail(_name, _amount);
        }


    }

}


float SurveyClass::calculateMinimumExpense(){

    float a = 0;

    if(this->members->length == 0){

        return 0;

    }

    else{



        Node* jumper = this->members->head;

        a = jumper->amount;

        while(jumper != nullptr){

            if(a > jumper->amount){

                a = jumper->amount;
            }

            jumper = jumper->next;
        }

        a = ((int)(a * 100) / 100.0);

        return a;

    }


}

float SurveyClass::calculateMaximumExpense(){

    float a = 0;

    if(this->members->length == 0){

        return 0;

    }

    else{

        Node* jumper = this->members->head;

        a = jumper->amount;

        while(jumper != nullptr){

            if(a < jumper->amount){

                a = jumper->amount;
            }

            jumper = jumper->next;
        }


        a = ((int)(a * 100) / 100.0);

        return a;

    }

}

float SurveyClass::calculateAverageExpense(){

    float a = 0;
    float avg = 0;

    if(this->members->length == 0){

        return 0;

    }

    else{

        Node* jumper = this->members->head;

        while(jumper != nullptr){


            float b = jumper->amount;
            a = a + b;
            jumper = jumper->next;
        }

        avg = a / this->members->length;

        avg = ((int)(avg * 100) / 100.0);

        return avg;

    }

}



SurveyClass::~SurveyClass(){

    if (this->members) {

        delete this->members;
    }
}
