#ifndef Vector_H
#define Vector_H

#include "Vector.h"

#include <vector>

template<typename T>
class Vector {
    private:
		T def;
        std::vector<T> v;
	
	public:
		// constructor
        Vector();
		Vector(int size);
		Vector(int size, T pad);

		// size operations
		int size();
		void shrink(int nof_elements);
		void pop();
		void growTo(int size);
		void growTo(int size, T pad);
		void clear();

		// stack interface
		void push();
		void push(T elem);
		T last();

		// vector interface
		T operator[](int index);

		// duplication
		void copyTo(Vector<T>* copy);
		void moveTo(Vector<T>* dest);
};

#endif