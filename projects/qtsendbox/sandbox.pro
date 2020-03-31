TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += \
        ../../src/assert/assert.cpp \
        ../../src/log/log.cpp \
        ../../src/stdfn/stdfn.cpp \
        ../../src/string/string.cpp \
        ../../src/test/test.cpp \
        ../../tests/list.cpp \
        ../../tests/observer.cpp \
        ../../tests/str.cpp \
        ../../tests/main.cpp \
        ../../src/mem/heapman_default.cpp \
        ../../src/mem/heapman_impl.cpp \
        ../../src/mem/new.cpp \
        ../../src/os/qt/qtmutex.cpp \
        ../../src/ulib.cpp \
        entry.cpp

HEADERS += \
    ../../inc/assert/asrt_halt_stdio.h \
    ../../inc/assert/asrt_pc_stdio.h \
    ../../inc/assert.h \
    ../../inc/list.h \
    ../../inc/log.h \
    ../../inc/heapman.h \
    ../../inc/new.h \
    ../../inc/observer.h \
    ../../inc/mutex.h \
    ../../inc/stdfn/stdfn.h \
    ../../inc/str.h \
    ../../inc/test/test.h \
    ../../inc/ulib.h \
    ../../inc/autoptr.h \
    ../../inc/locker.h \
    ../../src/mem/heapman_default.h \
    ../../src/mem/heapman_impl.h \
    ../../src/os/qt/qtmutex.h \
    ../../tests/tests.h

DISTFILES +=

INCLUDEPATH+=$$PWD/../../inc/
DEFINES+=BPP_UNIT_TESTS
