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

template <typename Type>
void printListContent(const jora::List<Type>& list, bool endl = true) {
    std::cout << list << ": ";
    for (const auto& i : list)
        std::cout << i << ' ';
    if (endl)
        std::cout << std::endl;
}

bool test1() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list = { 1, 2, 3, 4 };

    auto it = list.begin();
    std::cout << list << ": ";
    while (it)
        std::cout << *it++ << ' ';
    std::cout << std::endl;

    return false;
}

bool test2() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    std::list<double> stdList({ 1.4, 26.72, 26.55 });
    jora::List<double> list(stdList);

    printListContent(list);
    return false;
}

bool test3() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
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
    std::cout << std::endl << __FUNCTION__ << std::endl;
    bool result = true;
    jora::List<int> list;
    auto it = list.begin();
    try {
        *it;
    }
    catch (const jora::IteratorExpiredException&) {
        try {
            ++it;
        }
        catch (const jora::IteratorExpiredException&) {
            result = false;
        }
    }
    return result;
}

bool test5() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list({ 1, 2, 4, 5 });
    auto it = list.begin();
    ++it;
    list.insertAfter(it, 3);
    printListContent(list);
    return false;
}

bool test6() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list({ -1, -1, -1, -1 });
    auto it = list.iteratorFromIndex(1);
    list.insertAfter(it, {1, 2, 3});

    std::cout << list << ':';
    for (const int& s : list)
        std::cout << ' ' << s;
    std::cout << std::endl;

    return false;
}

bool test7() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list({ -1, 1 });

    std::cout << list << " front: " << list.front() << "; back: " << list.back() << std::endl;
    int value = list.popFront();
    std::cout << "popFront: " << value << " -> "; printListContent(list);

    list.pushFront(-9);
    std::cout << "pushFront -9 -> "; printListContent(list);
    list.pushBack(9);
    std::cout << "pushBack 9 -> "; printListContent(list);

    return false;
}

bool test8() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list({ -1, 0, 1 });

    auto it = list.cbegin();
    ++it;
    list.insertAfter(it, 2);
    printListContent(list);

    return false;
}

bool test9() {
    std::cout << std::endl << __FUNCTION__ << std::endl;
    jora::List<int> list({ -1, 0, 1 });

    int *arr = list.toCArray();
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << std::endl;
    delete[] arr;

    return false;
}

int main() {
    std::list<int> l(2);
    auto i = l.begin();
    *i++ = 2;

    int failed = 0;
    failed += test1();
    failed += test2();
    failed += test3();
    failed += test4();
    failed += test5();
    failed += test6();
    failed += test7();
    failed += test8();
    failed += test9();
    std::cout << "Failed: " << failed << std::endl;
    return 0;
}
