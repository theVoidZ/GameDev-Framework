


cmake_minimum_required(VERSION 3.14)
project(Incursio_v20)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/animation)
include_directories(src/animation/state_machine)
include_directories(src/Assets/TestCase5)
include_directories(src/Assets/TestCase5/backupobject)
include_directories(src/Assets/TestCase5/planete)
include_directories(src/Assets/TestCase5/sandbox)
include_directories(src/Assets/TestCase5/SoG)
include_directories(src/Assets/TestCase6)
include_directories(src/audio)
include_directories(src/Core)
include_directories(src/data_structure)
include_directories(src/editor)
include_directories(src/graphic)
include_directories(src/kernel)
include_directories(src/kernel/data_structure)
include_directories(src/managers)
include_directories(src/resource_management)
include_directories(src/system)
include_directories(src/time_management)
include_directories(src/tools)
include_directories(src/tools/imgui-sfml)
include_directories(src/tools/imgui-sfml/imgui)
include_directories(src/tools/SFC)
include_directories(src/tools/SFC/nanosvg++)

add_executable(Incursio_v20
        src/animation/state_machine/animatorcondition.cpp
        src/animation/state_machine/animatorcondition.h
        src/animation/state_machine/animatorconditionmode.h
        src/animation/state_machine/animatorstate.cpp
        src/animation/state_machine/animatorstate.h
        src/animation/state_machine/animatorstatemachine.cpp
        src/animation/state_machine/animatorstatemachine.h
        src/animation/state_machine/animatortransitionbase.cpp
        src/animation/state_machine/animatortransitionbase.h
        src/animation/animation.cpp
        src/animation/animation.h
        src/animation/animation2.cpp
        src/animation/animation2.h
        src/animation/animationclip.cpp
        src/animation/animationclip.h
        src/animation/animationevent.cpp
        src/animation/animationevent.h
        src/animation/animator.cpp
        src/animation/animator.h
        src/animation/animatorcontroller.cpp
        src/animation/animatorcontroller.h
        src/animation/animatorcontrollerlayer.cpp
        src/animation/animatorcontrollerlayer.h
        src/animation/blendtree.cpp
        src/animation/blendtree.h
        src/animation/keyframe.cpp
        src/animation/keyframe.h
        src/animation/motion.cpp
        src/animation/motion.h
        src/animation/wrapmode.h
        src/Assets/TestCase5/planete/Biome.cpp
        src/Assets/TestCase5/planete/Biome.h
        src/Assets/TestCase5/sandbox/cobblestone_block.json
        src/Assets/TestCase5/sandbox/OreBase.cpp
        src/Assets/TestCase5/sandbox/OreBase.h
        src/Assets/TestCase5/sandbox/silver_ore.json
        src/Assets/TestCase5/sandbox/TileSetBase.cpp
        src/Assets/TestCase5/sandbox/TileSetBase.h
        src/Assets/TestCase5/SoG/debuggeritem.cpp
        src/Assets/TestCase5/SoG/debuggeritem.h
        src/Assets/TestCase5/SoG/sog.cpp
        src/Assets/TestCase5/SoG/sog.h
        src/Assets/TestCase5/camfollower.cpp
        src/Assets/TestCase5/camfollower.h
        src/Assets/TestCase5/finalgameinfo.cpp
        src/Assets/TestCase5/finalgameinfo.h
        src/Assets/TestCase5/finalkernel.cpp
        src/Assets/TestCase5/finalkernel.h
        src/Assets/TestCase5/finalscenebuilder.cpp
        src/Assets/TestCase5/finalscenebuilder.h
        src/Assets/TestCase5/finalsceneloader.cpp
        src/Assets/TestCase5/finalsceneloader.h
        src/Assets/TestCase5/universecenter.cpp
        src/Assets/TestCase5/universecenter.h
        src/audio/audioclip.cpp
        src/audio/audioclip.h
        src/audio/audiolistener.cpp
        src/audio/audiolistener.h
        src/audio/audiosource.cpp
        src/audio/audiosource.h
        src/Core/collider.cpp
        src/Core/collider.h
        src/Core/collisionmanager.cpp
        src/Core/collisionmanager.h
        src/Core/garbagecollector.cpp
        src/Core/garbagecollector.h
        src/data_structure/bounds.cpp
        src/data_structure/bounds.h
        src/graphic/renderer.cpp
        src/graphic/renderer.h
        src/graphic/shaperenderer.cpp
        src/graphic/shaperenderer.h
        src/graphic/sprite2d.cpp
        src/graphic/sprite2d.h
        src/graphic/spriterenderer.cpp
        src/graphic/spriterenderer.h
        src/graphic/spritesheet.cpp
        src/graphic/spritesheet.h
        src/graphic/texture2d.cpp
        src/graphic/texture2d.h
        src/kernel/data_structure/componentcontainer.cpp
        src/kernel/data_structure/componentcontainer.h
        src/kernel/data_structure/componentcontainer.inl
        src/kernel/data_structure/componentfactory.cpp
        src/kernel/data_structure/componentfactory.h
        src/kernel/data_structure/hierarchy.cpp
        src/kernel/data_structure/hierarchy.h
        src/kernel/data_structure/kernelrules.cpp
        src/kernel/data_structure/kernelrules.h
        src/kernel/data_structure/tracker_ptr.cpp
        src/kernel/data_structure/tracker_ptr.h
        src/kernel/camera.cpp
        src/kernel/camera.h
        src/kernel/component.cpp
        src/kernel/component.h
        src/kernel/component.inl
        src/kernel/gameinfo.cpp
        src/kernel/gameinfo.h
        src/kernel/gameobject.cpp
        src/kernel/gameobject.h
        src/kernel/gameobject.inl
        src/kernel/monobehavior.cpp
        src/kernel/monobehavior.h
        src/kernel/object.cpp
        src/kernel/object.h
        src/kernel/scene.cpp
        src/kernel/scene.h
        src/kernel/sceneloaderbase.cpp
        src/kernel/sceneloaderbase.h
        src/kernel/transform.cpp
        src/kernel/transform.h
        src/resource_management/resource.cpp
        src/resource_management/resource.h
        src/resource_management/resourcemanager.cpp
        src/resource_management/resourcemanager.h
        src/system/algorithm.cpp
        src/system/algorithm.h
        src/system/operators.cpp
        src/system/operators.h
        src/system/terminal_colors.h
        src/time_management/chrono.cpp
        src/time_management/chrono.h
        src/tools/json.hpp
        main.cpp)

# OPENGL
FIND_PACKAGE(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

SET(LIBRARIES ${LIBRARIES} ${OPENGL_LIBRARIES})

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Incursio_v20 ${SFML_LIBRARIES})
endif()

# Boost
find_package(Boost 1.63.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(Incursio_v20 ${Boost_LIBRARIES})