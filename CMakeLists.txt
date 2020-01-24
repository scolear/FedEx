cmake_minimum_required(VERSION 3.15)
project(FedEx)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(FedEx
main.cpp
DataToMat.cpp)

target_link_libraries(FedEx ${OpenCV_LIBS} )