cmake_minimum_required(VERSION 3.16)
project(FedEx)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
find_package( Qt5 COMPONENTS Widgets REQUIRED )
find_package( Qt5 COMPONENTS Core )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        main.cpp
        UiMainWindow.cpp
        DataToMat.cpp
        )

qt5_wrap_cpp(SOURCES
        UiMainWindow.h
        DataToMat.h
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets)
target_link_libraries( ${PROJECT_NAME} Qt5::Core)