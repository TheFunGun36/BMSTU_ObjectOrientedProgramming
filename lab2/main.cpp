#include <list>
#include <iostream>
#include "jlist.h"

struct SampleStruct {
    int a, b, c;
    int setA(int a) { this->a = a; }
    int setB(int b) { this->b = b; }
    SampleStruct(int a = 1, int b = 2, int c = 3)
        : a(a), b(b), c(c) {}
};

bool test1() {
    jora::List<int> list = { 1, 2, 3, 4 };

    auto it = list.begin();

    std::cout << list << ": ";
    while (it)
        std::cout << *it++ << ' ';
    std::cout << std::endl;
    return false;
}

bool test2() {
    std::list<double> stdList({ 1.4, 26.72, 26.55 });
    jora::List<double> list(stdList);

    std::cout << list << ": ";
    for (const auto& i : list)
        std::cout << i << ' ';
    std::cout << std::endl;
    return false;
}

bool test3() {
    jora::List<SampleStruct> list(2);
    SampleStruct arr[5];
    for (int i = 0; i < 5; i++)
        arr[i] = SampleStruct(i, i, i);
    list.append(arr, 5);

    std::cout << list << ": ";
    for (const SampleStruct& s : list)
        std::cout << '(' << s.a << ',' << s.b << ',' << s.c << ")";
    std::cout << std::endl;

    return false;
}

bool test4() {
    bool result = true;
    jora::List<int> list;

    try {
        auto it = list.begin();
        *it;
    }
    catch (const jora::IteratorExpiredException&) {
        result = false;
    }

    return result;
}

bool test5() {
    jora::List<int> list({ 1, 2, 4, 5 });
    auto it = list.begin();
    ++it;
    list.insertAfter(it, 3);

    std::cout << list << ": ";
    for (const int& s : list)
        std::cout << ' ' << s;
    std::cout << std::endl;

    return false;
}

bool test6() {
    jora::List<int> list({ 1, 1, 1, 1 });
    auto it = list.begin();
    ++it;
    list.insertAfter(it, {0, 0, 0});

    std::cout << list << ": ";
    for (const int& s : list)
        std::cout << ' ' << s;
    std::cout << std::endl;

    return false;
}

bool test7() {
    jora::List<int> list({ -1, 1 });
    
    std::cout << list << " front: " << list.front() << "; back: " << list.back() << std::endl;
    int value = list.popFront();
    std::cout << "pop front: " << value << "; " << list;

    return false;
}

int main() {
    int failed = 0;
    failed += test1();
    failed += test2();
    failed += test3();
    failed += test4();
    failed += test5();
    failed += test6();
    failed += test7();
    std::cout << "Failed: " << failed << std::endl;
    return 0;
}
