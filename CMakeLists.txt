cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Yolov8OnnxRuntimeCPPInference)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

option(USE_CUDA "Enable CUDA support" OFF)
include_directories(${PROJECT_NAME} ./include)

set(PROJECT_SOURCES
        main.cpp
        infer.h
        infer.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} /home/thanhln/Desktop/projects/yolov8/onnxruntime/build/Linux/RelWithDebInfo/libonnxruntime.so)