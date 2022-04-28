#include <list>
#include <iostream>
#include "jlist.h"

struct S {
    int val;
    S operator+(int other) {
        S s;
        s.val = val + other;
        return s;
    }
};

int main() {
    std::list<int> s;
    jora::List<int> j;

    return 0;
}
