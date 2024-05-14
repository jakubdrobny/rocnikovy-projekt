#include "Queue.h"

template<typename T>
Queue<T>::Queue() {}

template<typename T>
void Queue<T>::insert(T x) {
    this->q.push(x);
}

template<typename T>
T Queue<T>::dequeue() {
    T elem;
    if (!this->q.empty()) {
        elem = this->q.front();
        this->q.dequeue();
    }
    return elem;
}

template<typename T>
void Queue<T>::clear() {
    while (!this->q.empty()) { 
        this->q.pop();
    }
}

template<typename T>
int Queue<T>::size() {
    return (int)this->q.size();
}