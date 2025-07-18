TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

SOURCES += main.cpp \
    utility.cpp \
    edge.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += $$(PWD)\opencv_3_1_0\include
LIBS += $$(PWD)\opencv_3_1_0\x86\mingw\lib\libopencv_world310.dll.a



HEADERS += \
    utility.h \
    edge.h
