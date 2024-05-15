QT -= gui
QT += network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../common

SOURCES += \
        ../common/common.cpp \
        ../common/communicator.cpp \
        src\main.cpp \
        src\application.cpp \
        src\house.cpp \
        src\entrance.cpp \
        src\elevator.cpp \
        src\floor.cpp \
        src\passenger.cpp

HEADERS += \
        ../common/common.h \
        ../common/communicator.h \
        headers\application.h \
        headers\house.h \
        headers\entrance.h \
        headers\elevator.h \
        headers\floor.h \
        headers\passenger.h

INCLUDEPATH += headers src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
