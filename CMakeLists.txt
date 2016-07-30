cmake_minimum_required(VERSION 3.3)
project(CFD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector.cpp Vector.h function/Symbolic.cpp function/Symbolic.h function/no_value.cpp function/no_value.h function/Function.cpp function/Function.h Integration/RungeKutta4.h Integration/EmbeddedRungeKutta.h Integration/StepDoublingRK4.h Integration/Uncouple.h Integration/Matrix.cpp Integration/Matrix.h Integration/ImplicitRK4.h Integration/RKC45.h Graphics/Container.cpp Graphics/Container.h Graphics/Cell.cpp Graphics/Cell.h Graphics/Node.cpp Graphics/Node.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(CFD ${SOURCE_FILES})

add_subdirectory(/Users/Hank/ClionProjects/CFD/GLFW)
target_link_libraries(CFD glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(CFD ${OPENGL_glu_LIBRARY})



