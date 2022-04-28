#include <list>
#include <iostream>
#include "jlist.h"

struct Sas {
    int biba() {
        return 12;
    }
};

struct Ptr {

    Sas *sas() {
        return &s;
    }

    Sas *operator->() {
        return &s;
    }
private:
    Sas s;
};

int main() {

    Sas s;
    Sas *p = &s;
    s.biba();
    p->biba();

    Ptr pp;
    pp.sas()->biba();
    pp->biba();
    return 0;
}
