TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

unix {
    INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include
}

SOURCES += \
        main.cpp

HEADERS += \
    jcontainer.h \
    jexception.h \
    jiterator.h \
    jiteratorexception.h \
    jlist.h \
    jlistiterator.h \
    jnode.h
