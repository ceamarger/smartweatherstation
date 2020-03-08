cmake_minimum_required(VERSION 3.5)

project(smartweatherstation_tests LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

set(SOURCE_APP_DIRECTORY ../src)
file(GLOB SOURCE
    ${SOURCE_APP_DIRECTORY}/weather/*.cpp)

file(GLOB HEADER
    ${SOURCE_APP_DIRECTORY}/weather/*.h)

add_executable(smartweatherstation_tests tst_weathersettings.cpp)
add_test(smartweatherstation_tests COMMAND smartweatherstation_tests)

target_link_libraries(smartweatherstation_tests
    PRIVATE
    SWSWeatherLib
    Qt5::Test)
