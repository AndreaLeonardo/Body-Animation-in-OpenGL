# Install script for directory: /Users/andrealeonardo/CLionProjects/CGproject/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/andrealeonardo/CLionProjects/CGproject/cmake-build-debug/assimp/bin/libassimpd.5.2.0.dylib"
    "/Users/andrealeonardo/CLionProjects/CGproject/cmake-build-debug/assimp/bin/libassimpd.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.2.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/andrealeonardo/CLionProjects/CGproject/cmake-build-debug/assimp/bin/libassimpd.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimpd.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/anim.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/aabb.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ai_assert.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/camera.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/color4.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/color4.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/cmake-build-debug/assimp/code/../include/assimp/config.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ColladaMetaData.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/commonMetaData.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/defs.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/cfileio.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/light.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/material.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/material.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/mesh.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ObjMaterial.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/GltfMaterial.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/postprocess.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/quaternion.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/quaternion.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/scene.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/metadata.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/texture.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/types.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/vector2.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/vector2.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/vector3.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/vector3.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/version.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/cimport.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/importerdesc.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Importer.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Logger.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/cexport.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/fast_atof.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/qnan.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Hash.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/StreamReader.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/StringComparison.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/StringUtils.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SmallVector.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Subdivision.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Vertex.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Profiler.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/LogAux.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Bitmap.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/XMLTools.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/XmlParser.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Exceptional.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/ByteSwapper.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/andrealeonardo/CLionProjects/CGproject/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

