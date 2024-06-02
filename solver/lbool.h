#ifndef lbool_H
#define lbool_H

enum lbool_val { FALSE, TRUE, NOTHING };

class lbool {
	public:
        lbool_val val;
        lbool();
        lbool(bool x);

        bool operator==(const lbool_val &x);
        bool operator!=(const lbool_val &x);
};

lbool operator-(lbool x);

#endif