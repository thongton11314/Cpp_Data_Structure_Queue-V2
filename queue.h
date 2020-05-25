#pragma once
#ifndef QUEUE
#define QUEUE
#include <ostream>
#include <assert.h>

using namespace std;

template <typename T>
class Queue {

    // g++ has problems with friend template functions and class templates
    // so put the code for operator<< here, in the class definition
    // output operator for class queue, print data, 
    // responsibility for output is left to object stored in the queue
    friend ostream &operator<<(ostream & output, const Queue<T> & obj) {
        typename Queue<T>::Node* current = obj.front;
        while (current != nullptr) {
            output << *current->data << endl;
            current = current->next;
        }
        return output;
    }

public:
    Queue();                        // default constructor
    ~Queue();                       // destructor
    Queue(const Queue&);            // copy constructor
    void clear();                   // clear out queue
    bool isEmpty() const;           // is the queue empty?

    void buildQueue(ifstream & infile);

    // insert item, assume object passed in is valid, return whether successful
    bool enqueue(T*);

    // remove item, parameter is removed item, return whether item is removed 
    bool dequeue(T*&);

    // retrieve item, parameter is item at top, return whether item exists
    bool peek(T*&) const;

private:
    void copy(const Queue &);

    struct Node {
        T* data;          // pointer to actual data stored
        Node* next;
    };

    // for linked list implementation
    Node* front;                    // pointer to front of queue
    Node* rear;                     // pointer to rear of queue
};

//------------------------------ constructor ---------------------------------
template <typename T>
Queue<T>::Queue() {

    // front is rear at the begining
    front = rear = nullptr;
}

//----------------------------- deconstructor --------------------------------
// deallocate memory
template<typename T>
Queue<T>::~Queue() {
    clear();
}

//---------------------------- copy constructor ------------------------------
// deallocate memory
template<typename T>
Queue<T>::Queue(const Queue & other) {
    if (other.front != nullptr)
        copy(other);
    else
        front = rear = nullptr;
}

//--------------------------------- clear -----------------------------------
// delete each node carefully since allocate them
template<typename T> 
void Queue<T>::clear(void) {

    // keep deleting if queue still has datas
    while (front != nullptr) {

        // using for next node
        Node* temp = front;
        front = front->next;

        // delete node
        delete temp->data;
        delete temp;
        temp = nullptr;
    }

    // always set null pointer when done
    front = rear = nullptr;
}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
template <typename T>
bool Queue<T>::isEmpty() const {
    return (front == nullptr);
}

//----------------------------- buildQueue -----------------------------------
// check to see if queue is empty
template<typename T>
void Queue<T>::buildQueue(ifstream & infile) {
    T* ptr;
    bool successfulRead;                             // read good data
    bool success;                                    // successfully insert
    for (;;) {
        ptr = new T;

        // must have setData
        successfulRead = ptr->setData(infile);       // fill the T object
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the queue, otherwise ignore it
        if (successfulRead) {
            success = enqueue(ptr);
        }
        else {
            delete ptr;
        }
        if (!success) break;
    }
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
template <typename T>
bool Queue<T>::enqueue(T* dataptr) {

    Node* nodeptr = new Node;
    assert(nodeptr != nullptr);
    nodeptr->data = dataptr;
    nodeptr->next = nullptr;

    // link at front if empty, otherwise at the rear
    if (isEmpty())
        front = nodeptr;
    else
        rear->next = nodeptr;
    rear = nodeptr;                                // either way, rear is set
    return true;
}

//---------------------------------- dequeue ---------------------------------
// remove item from front of queue
template <typename T>
bool Queue<T>::dequeue(T *& dataptr) {
    if (isEmpty())
        return false;

    dataptr = front->data;
    Node* nodeptr = front;
    front = front->next;
    if (isEmpty())
        rear = nullptr;                   // if it's the last node in queue
    delete nodeptr;
    nodeptr = nullptr;
    return true;
}

//---------------------------------- peek ------------------------------------
// return item at front of queue
template <typename T>
bool Queue<T>::peek(T *& dataptr) const {
    if (isEmpty())
        return false;

    dataptr = front->data;
    return true;
}

//---------------------------------- copy ------------------------------------
// copy each node of other queue into this queue
template<typename T>
void Queue<T>::copy(const Queue & other) {
    if (other.front != nullptr) {

        // create a temporary node to walk into other queue
        Node* temp = other.front;
        front = rear = new Node{ new T(*temp->data), nullptr };
        temp = temp->next;

        // copy every node from other queue into this queue
        while (temp != nullptr) {
            rear->next = new Node{ new T(*temp->data), nullptr };
            rear = rear->next;
            temp = temp->next;       // walking from other node
        }
    }
}
#endif // !QUEUE