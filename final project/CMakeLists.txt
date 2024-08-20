cmake_minimum_required(VERSION 3.10)
project(ParkingLotManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ParkingLotManagement
    src/main.cpp
    src/ParkingSpaceDetector.cpp
    src/OccupancyClassifier.cpp
    src/CarSegmentation.cpp
    src/TopViewVisualizer.cpp
    src/PerformanceEvaluator.cpp
    src/XMLParser.cpp
)

target_link_libraries(ParkingLotManagement ${OpenCV_LIBS})