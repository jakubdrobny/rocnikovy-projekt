#ifndef lit_H
#define lit_H

class lit {
    private:
        int val;
	public:
        lit(int x);
        int getVal();
};

lit operator-(lit p);
bool sign(lit p);
int var(lit p);
int index(lit p);

#endif