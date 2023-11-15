#ifndef Literal_H
#define Literal_H

class Literal {
    public:
        int value, node, color;

        Literal() {}
        Literal(int value, int node, int color): value(value), node(node), color(color) {}

        void print();
};

#endif