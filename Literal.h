#ifndef Literal_H
#define Literal_H

class Literal {
    public:
        int value, node, color;

        Literal() {}
        Literal(int node, int color, int colors, bool negate = false) {
            this->node = node;
            this->color = color;
            this->value = valueFromNodeAndColor(colors, negate);
        }

        void print();
        int valueFromNodeAndColor(int K, bool negate);
};

#endif