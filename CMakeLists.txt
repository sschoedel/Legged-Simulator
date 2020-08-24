cmake_minimum_required(VERSION 2.8)
project(DogSim)

set(CMAKE_BUILD_TYPE "Debug")

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )
include_directories(
    include/
    #${CINDER_PATH}/blocks/Cinder-ImGui/include/
)

set( PROJECT_SOURCES
    ${APP_PATH}/src/Robot.cpp
    ${APP_PATH}/src/simulator.cpp
    ${APP_PATH}/src/Mesh.cpp
    ${APP_PATH}/src/gui.cpp
    ${APP_PATH}/src/Camera.cpp
    ${APP_PATH}/src/Scene.cpp
    ${APP_PATH}/src/Link.cpp
)

ci_make_app (
    APP_NAME    "DogSim"
    CINDER_PATH ${CINDER_PATH}
    SOURCES     ${PROJECT_SOURCES}
    INCLUDES    ${APP_PATH}
)