
cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_library(Application
            SHARED
            src/main/cpp/Module.h
            src/main/cpp/Shapes.h
            src/main/cpp/Tube.cpp
            src/main/cpp/Collider.cpp
            src/main/cpp/Application.cpp
            src/main/cpp/ModuleRenderer.cpp
            src/main/cpp/ModuleCollision.cpp
            src/main/cpp/ModuleMainScene.cpp
            src/main/cpp/Character.cpp)

# add lib dependencies
target_link_libraries(Application
                      android
                      log
                      EGL
                      GLESv2)

