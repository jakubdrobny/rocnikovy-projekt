#include "Vector.h"

// constructors
template<typename T>
Vector<T>::Vector() {}

template<typename T>
Vector<T>::Vector(int size) {
    this->v.resize(size);
}

template<typename T>
Vector<T>::Vector(int size, T pad) {
    this->v.assign(size, pad);
    this->def = pad;
}


// size operations
template<typename T>
int Vector<T>::size() {
    return (int)this->v.size();
}

template<typename T>
void Vector<T>::shrink(int nof_elements) {
    this->v.resize(nof_elements);
}

template<typename T>
void Vector<T>::pop() {
    this->v.pop_back();
}

template<typename T>
void Vector<T>::growTo(int size) {
    this->v.resize(size);
}

template<typename T>
void Vector<T>::growTo(int size, T pad) {
    while (size--) {
        this.v->push_back(pad);
    }
}

template<typename T>
void Vector<T>::clear() {
    this->v.clear();
}


// stack interface
template<typename T>
void Vector<T>::push() {
    this->v.push_back(this->def);
}

template<typename T>
void Vector<T>::push(T elem) {
    this->v.push_back(elem);
}

template<typename T>
T Vector<T>::last() {
    return this->v.back();
}

// vector interface
template<typename T>
T Vector<T>::operator[](int index) {
    if (index < 0 || index >= this->size()) {
        return def;
    }
    return this->v[index];
}

// duplication
template<typename T>
void Vector<T>::copyTo(Vector<T>* copy) {
    copy->clear();
    for (int idx = 0; idx < this->size(); idx++) {
        copy->push(this[idx]);
    }
}

template<typename T>
void Vector<T>::moveTo(Vector<T>* dest) {
    dest->v = move(this->v);
    this->clear();
}