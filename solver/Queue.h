#ifndef Queue_H
#define Queue_H

#include <queue>

template<typename T>
class Queue {
    private:
        std::queue<T> q;
        
	public:
        Queue();

		void insert(T x);
        T dequeue();
        void clear();
        int size();
};

#endif