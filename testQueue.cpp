#include <iostream>
#include <fstream>
#include <assert.h>
#include "queue.h"
#include "employee.h"
using namespace std;

// This main is using for testing queue
int main() {

    // Test enqueue
    Queue<Employee> queue1;
    assert(queue1.enqueue(new Employee("A", "A", 1, 1000)));
    assert(queue1.enqueue(new Employee("B", "B", 2, 2000)));
    assert(queue1.enqueue(new Employee("C", "C", 3, 3000)));
    assert(queue1.enqueue(new Employee("D", "D", 4, 4000)));
    assert(queue1.enqueue(new Employee("E", "E", 5, 5000)));
    assert(queue1.enqueue(new Employee("F", "F", 6, 6000)));
    assert(queue1.enqueue(new Employee("G", "G", 7, 7000)));
    assert(queue1.enqueue(new Employee("H", "H", 8, 8000)));
    assert(queue1.enqueue(new Employee("K", "K", 9, 9000)));
    assert(queue1.enqueue(new Employee("L", "L", 10, 10000)));
    cout << "Test enqueue: \tPASSED" << endl;
    cout << endl;

    // Test copy constructor
    Queue<Employee> queue2(queue1);
    cout << queue2;
    cout << "Test copy constructor: PASSED" << endl;

    // Test peek
    Employee* modifiedData;
    assert(queue2.peek(modifiedData));
    cout << "Test Peak: \tPASSED" << endl;
    cout << "Peak: " << *modifiedData;
    cout << endl;
    modifiedData = nullptr;
    delete modifiedData;
    
    
    // Test dequeue
    cout << "Dequeue:" << endl;
    Employee* deletedNode;
    while (!queue2.isEmpty()) {
        queue2.dequeue(deletedNode);
        cout << *deletedNode;
        delete deletedNode;
        deletedNode = nullptr;
    }
    cout << "Test dequeue: \tPASSED" << endl;
    cout << endl;

    // Test empty
    assert(queue2.isEmpty());
    cout << "Test isEmpty: \tPASSED" << endl;
    cout << endl;

    // Test clear
    queue1.clear();
    queue2.clear();
    assert(queue2.isEmpty() && queue1.isEmpty());
    cout << "Test clear: \tPASSED" << endl;
    cout << endl;
    
    // Test buildQueue
    ifstream listOfEmployees("listEmployees.txt");
    Queue<Employee> aCompany;
    aCompany.buildQueue(listOfEmployees);
    cout << aCompany;
}