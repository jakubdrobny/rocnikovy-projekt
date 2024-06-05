#ifndef lit_H
#define lit_H

class lit {
    private:
        int val;
	public:
        lit(int x);
        int getVal();
};

lit EMPTY = lit(0);

lit operator-(lit p);
bool operator==(const lit &l1, const lit &l2);
bool sign(lit p);
int var(lit p);
int index(lit p);

#endif