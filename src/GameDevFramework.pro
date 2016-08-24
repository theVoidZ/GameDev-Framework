# qmake -project "QT += serialport" "INCLUDEPATH += /path/to/sfml/include" "LIBS += -L/pat/to/sfml/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network" "CONFIG += c++14" "TARGET GameDev-example"

QT += serialport

LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network

CONFIG += c++14

#LIBS += -L/opt/openmpi/lib
#LIBS += -L/doc/libraries/lib

#INCLUDEPATH += /usr/include/mpi
#INCLUDEPATH += /doc/libraries/include


SOURCES += \
    main.cpp \
    kernel/gameinfo.cpp \
    kernel/scene.cpp \
    Core/gui.cpp \
    Core/System/camera.cpp \
    kernel/object.cpp \
    kernel/gameobject.cpp \
    kernel/component.cpp \
    Core/transform.cpp \
    Core/Graphic/renderer.cpp \
    Core/Graphic/spriterenderer.cpp \
    Core/scriptableobject.cpp \
    Core/DataStruct/bounds.cpp \
    Core/DataStruct/ray.cpp \
    Core/DataStruct/color.cpp \
    Core/Graphic/Animation/StateMachine/animatorstatemachine.cpp \
    Core/Graphic/Animation/StateMachine/animatorstate.cpp \
    Core/Graphic/Animation/StateMachine/animatortransitionbase.cpp \
    Core/Graphic/Animation/StateMachine/animatorcondition.cpp \
    Core/Graphic/Animation/motion.cpp \
    Core/Graphic/Animation/animatorcontroller.cpp \
    Core/Graphic/Animation/animatorcontrollerlayer.cpp \
    Core/Graphic/Animation/animationclip.cpp \
    Core/Graphic/Animation/blendtree.cpp \
    Core/Graphic/Animation/animator.cpp \
    Core/Graphic/Animation/avatarmask.cpp \
    Core/Graphic/Animation/animationevent.cpp \
    Core/Graphic/Animation/keyframe.cpp \
    Core/Graphic/Animation/animation.cpp \
    Core/Utilities/algorithm.cpp \
    Core/Graphic/Animation/animatorcontroller.tpp \
    Assets/TestCases/testcasescene.cpp \
    Core/Exception/nullpointerexception.cpp \
    Core/Exception/invalidreturn.cpp \
    Core/Exception/missingrequirementsexception.cpp \
    Core/System/behavior.cpp \
    Core/System/monobehavior.cpp \
    Core/Graphic/Animation/StateMachine/statemachinebehavior.cpp \
    Core/garbagecollector.cpp \
    Assets/TestCases/arduinotest.cpp \
    resource_management/resource.cpp \
    resource_management/resourcemanager.cpp \
    Core/Graphic/sprite2d.cpp \
    resource_management/texture2d.cpp \
    Assets/TestCases/moveobject.cpp \
    Assets/TestCases/velocitydef.cpp \
    time_management/timekeeper.cpp \
    time_management/event.cpp \
    time_management/eventtranslation.cpp \
    time_management/timewinder.cpp \
    Assets/TestCases/simulatorcomponent.cpp \
    time_management/eventvelocity.cpp \
    time_management/eventvaluechange.cpp \
    time_management/eventanimationstatechanged.cpp \
    resource_management/spritetile.cpp \
    Assets/TestCases/testcasegameinfo.cpp \
    time_management/chrono.cpp \
    kernel/kernelrules.cpp \
    kernel/component.inl \
    kernel/gameobject.inl \
    kernel/componentcontainer.cpp \
    kernel/componentcontainer.inl \
    kernel/hierarchy.cpp

HEADERS += \
    kernel/gameinfo.h \
    kernel/scene.h \
    Core/gui.h \
    Core/System/camera.h \
    kernel/object.h \
    kernel/gameobject.h \
    Core/gotag.h \
    Core/golayer.h \
    kernel/component.h \
    Core/transform.h \
    Core/Graphic/renderer.h \
    Core/Graphic/spriterenderer.h \
    Core/DataStruct/bounds.h \
    Core/DataStruct/ray.h \
    Core/DataStruct/color.h \
    Core/DataStruct/wrapmode.h \
    Core/scriptableobject.h \
    Core/Graphic/Animation/StateMachine/animatorstatemachine.h \
    Core/Graphic/Animation/StateMachine/animatorstate.h \
    Core/Graphic/Animation/StateMachine/animatortransitionbase.h \
    Core/Graphic/Animation/StateMachine/animatorcondition.h \
    Core/Graphic/Animation/motion.h \
    Core/Graphic/Animation/animatorcontroller.h \
    Core/Graphic/Animation/animatorcontrollerlayer.h \
    Core/Graphic/Animation/animationclip.h \
    Core/Graphic/Animation/blendtree.h \
    Core/Graphic/Animation/animator.h \
    Core/Graphic/Animation/avatarmask.h \
    Core/Graphic/Animation/animatorlayerblendingmode.h \
    Core/Graphic/Animation/animatorcullingmode.h \
    Core/Graphic/Animation/animatorupdatemode.h \
    Core/Graphic/Animation/animationevent.h \
    Core/Graphic/Animation/keyframe.h \
    Core/Graphic/Animation/wrapmode.h \
    Core/Graphic/Animation/animation.h \
    Core/Utilities/algorithm.h \
    Core/Graphic/Animation/StateMachine/animatorconditionmode.h \
    Core/Graphic/Animation/StateMachine/motiontype.h \
    Assets/TestCases/testcasescene.h \
    Core/Exception/nullpointerexception.h \
    Core/Exception/invalidreturn.h \
    Core/Exception/missingrequirementsexception.h \
    Core/System/behavior.h \
    Core/System/monobehavior.h \
    Core/Graphic/Animation/StateMachine/statemachinebehavior.h \
    Core/garbagecollector.h \
    Assets/TestCases/arduinotest.h \
    resource_management/resource.h \
    resource_management/resourcemanager.h \
    Core/Graphic/sprite2d.h \
    resource_management/texture2d.h \
    Assets/TestCases/moveobject.h \
    Assets/TestCases/velocitydef.h \
    time_management/timekeeper.h \
    time_management/event.h \
    time_management/eventtranslation.h \
    time_management/timewinder.h \
    Assets/TestCases/simulatorcomponent.h \
    time_management/eventvelocity.h \
    time_management/eventvaluechange.h \
    time_management/eventanimationstatechanged.h \
    resource_management/spritetile.h \
    Assets/TestCases/testcasegameinfo.h \
    Core/Utilities/terminal_colors.h \
    time_management/chrono.h \
    kernel/kernelrules.h \
    kernel/componentcontainer.h \
    kernel/hierarchy.h

DISTFILES += \
    progress_2

