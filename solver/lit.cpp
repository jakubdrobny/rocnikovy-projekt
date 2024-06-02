#include "lit.h"

lit::lit(int x) {
    this->val = x;
}

int lit::getVal() {
    return this->val;
}

// global functions
lit operator-(lit p) {
    return lit(p.getVal());
}

lit operator==(lit l1, lit l2) {
    return l1.getVal() == l2.getVal();
}

bool sign(lit p) {
    return p.getVal() < 0;
}

int var(lit p) {
    return p.getVal();
}

int index(lit p) {
    int val = p.getVal();
    return 2 * (val < 0 ? -val : val) + (val > 0);
}