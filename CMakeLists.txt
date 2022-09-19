cmake_minimum_required(VERSION 3.17)
project(CGproject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(ASSIMP_DIR ${LIB_DIR}assimp/)
add_subdirectory(${ASSIMP_DIR})
include_directories(${ASSIMP_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(CGproject  ogldev/ogldev_util.cpp math_3d.cpp ogldev/ogldev_texture.cpp ogldev/ogldev_basic_mesh.cpp ogldev/ogldev_world_transform.cpp
        debug_skinning_technique.cpp
        skinning_technique.cpp
        technique.cpp
        skinned_mesh.cpp
        camera.cpp
        main.cpp
        stb_image.cpp
        AssimpObjLoader.h AnimationProgram.h SkinningDebug.h)
target_link_libraries(CGproject assimp)
target_link_libraries(CGproject GLEW::glew ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})