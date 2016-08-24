# qmake -project "QT += serialport" "INCLUDEPATH += /path/to/sfml/include" "LIBS += -L/pat/to/sfml/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network" "CONFIG += c++14" "TARGET GameDev-example"

QT += serialport

LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network

CONFIG += c++14

#LIBS += -L/opt/openmpi/lib
#LIBS += -L/doc/libraries/lib

#INCLUDEPATH += /usr/include/mpi
#INCLUDEPATH += /doc/libraries/include


HEADERS += Core/transform.h \
           example/mycomponent.h \
           example/testcasegameinfo.h \
           example/testcasescene.h \
           kernel/component.h \
           kernel/componentcontainer.h \
           kernel/gameinfo.h \
           kernel/gameobject.h \
           kernel/hierarchy.h \
           kernel/kernelrules.h \
           kernel/object.h \
           kernel/scene.h \
           Core/DataStruct/bounds.h \
           Core/System/behavior.h \
           Core/System/camera.h \
           Core/System/monobehavior.h \
           Core/Utilities/algorithm.h \
           Core/Utilities/terminal_colors.h
SOURCES += main.cpp \
           Core/transform.cpp \
           example/mycomponent.cpp \
           example/testcasegameinfo.cpp \
           example/testcasescene.cpp \
           kernel/component.cpp \
           kernel/componentcontainer.cpp \
           kernel/gameinfo.cpp \
           kernel/gameobject.cpp \
           kernel/hierarchy.cpp \
           kernel/kernelrules.cpp \
           kernel/object.cpp \
           kernel/scene.cpp \
           Core/DataStruct/bounds.cpp \
           Core/System/behavior.cpp \
           Core/System/camera.cpp \
           Core/System/monobehavior.cpp \
           Core/Utilities/algorithm.cpp
