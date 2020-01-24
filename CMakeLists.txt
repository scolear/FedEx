cmake_minimum_required(VERSION 3.16)
project(FedEx)

if(UNIX)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
endif()

find_package( OpenCV REQUIRED )
find_package( Qt5 COMPONENTS Widgets REQUIRED )
find_package( Qt5 COMPONENTS Core )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCES
        main.cpp
        UiMainWindow.cpp
        DataToMat.cpp
        Reader.cpp
        DataHandler.cpp
        LinuxSerial.cpp
        UARTConnection.cpp
        )

qt5_wrap_cpp(SOURCES
        UiMainWindow.h
        DataToMat.h
        Reader.h
        DataHandler.h
        LinuxSerial.h
        UARTConnection.h
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets)
target_link_libraries( ${PROJECT_NAME} Qt5::Core)