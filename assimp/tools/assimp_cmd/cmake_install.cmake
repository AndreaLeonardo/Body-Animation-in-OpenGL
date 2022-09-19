# Install script for directory: /Users/andrealeonardo/CLionProjects/CG_PROJECTS/CGproject/assimp/tools/assimp_cmd

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-binx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/andrealeonardo/CLionProjects/CG_PROJECTS/CGproject/assimp/bin/assimpd")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/andrealeonardo/CLionProjects/CG_PROJECTS/CGproject/assimp"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/andrealeonardo/CLionProjects/CG_PROJECTS/CGproject/assimp/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/andrealeonardo/CLionProjects/CG_PROJECTS/CGproject/assimp/bin"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/assimpd")
    endif()
  endif()
endif()

