cmake_minimum_required(VERSION 3.5)

project(smartweatherstation LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core Quick Mqtt REQUIRED)

add_subdirectory(src)
