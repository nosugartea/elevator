QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\elevator.cpp \
    src\entrance.cpp \
    src\floor.cpp \
    src\house.cpp \
    src\main.cpp \
    src\param.cpp \
    src\interface.cpp \
    src\passenger.cpp \
    src\manager.cpp \
    src\state.cpp

HEADERS += \
    headers\param.h \
    headers\elevator.h \
    headers\entrance.h \
    headers\floor.h \
    headers\house.h \
    headers\interface.h \
    headers\passenger.h \
    headers\manager.h \
    headers\state.h

INCLUDEPATH += headers src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
