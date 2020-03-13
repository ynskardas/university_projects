#include "LinkedList.h"

LinkedList::LinkedList(){

    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;

}


LinkedList::LinkedList(const LinkedList& list){

    this->length = list.length;


    if(list.head == nullptr){

        this->head  = new Node(*(list.head));

        this->tail  = new Node(*(list.tail));
    }

    else{

        this->head  = new Node(*(list.head));

        this->tail = new Node(*(list.tail));
    }


}

LinkedList& LinkedList::operator=(const LinkedList& list){


    this->length = list.length;


    if(list.head == nullptr){
        delete this->head;
        delete this->tail;
        this->head  = new Node(*(list.head));

        this->tail  = new Node(*(list.tail));
    }
    else{
        delete this->head;
        delete this->tail;
        this->head  = new Node(*(list.head));

        this->tail = new Node(*(list.tail));
    }

    return *this;
}


LinkedList::LinkedList(LinkedList&& list){

    this->length = list.length;

    this->head = move(list.head);
    this->tail = move(list.tail);

    list.head = nullptr;
    list.tail = nullptr;
    list.length = 0;


}


LinkedList& LinkedList::operator=(LinkedList&& list){

    this->length = list.length;

    delete this->head;
    this->head = move(list.head);
    delete this->tail;
    this->tail = move(list.tail);


    list.head = nullptr;
    list.tail = nullptr;
    list.length = 0;

    return *this;

}


void LinkedList::pushTail(string _name, float _amount){

    int a = this->length;

    string name = _name;
    float amount = _amount;

    Node newn(name, amount);

    Node* newTail = new Node(newn);



    if(this->head == NULL){

        this->head = newTail;

        this->tail = newTail;

       this->length = a + 1;

    }
    else{

        this->tail->next = newTail;

        this->tail = newTail;

       this->length = a + 1;

    }

}


void LinkedList::updateNode(string _name, float _amount){

    if(this->head == nullptr){

        pushTail(_name, _amount);
    }
    else{

        Node* current = this->head;
        int a = 0;
        while(current != nullptr){

            if(!current->name.compare(_name)){

                current->amount = _amount;
                a++;
                break;
            }

            current = current->next;
        }


        if(a == 0){

            pushTail(_name, _amount);
        }

    }

}


LinkedList::~LinkedList(){

    if (this->head) {

        delete this->head;
    }
}





