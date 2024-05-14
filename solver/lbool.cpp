#include "lbool.h"

lbool::lbool() {
    this->val = NOTHING;
}

lbool::lbool(bool x) {
    this->val = x ? TRUE : FALSE;
}

// global functions
lbool operator-(lbool x) {
    return x.val == NOTHING ? lbool() : lbool(!x.val);
}

bool lbool::operator==(const lbool_val &x) {
    return this->val == x;
}