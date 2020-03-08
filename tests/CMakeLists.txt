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

set(APP_DIR ..)
set(APP_LIBRARIES_DIR ${APP_DIR}/export/lib)
set(SOURCE_APP_DIR ${APP_DIR}/src)
find_library(SWSLibraries NAMES SWSWeatherLib PATHS ${APP_LIBRARIES_DIR})

message("---------------- ${SWSLibraries}")
file(GLOB SOURCE
    ${SOURCE_APP_DIR}/weather/*.cpp)

file(GLOB HEADER
    ${SOURCE_APP_DIR}/weather/*.h)

add_executable(test_weatherSettings tst_weathersettings.cpp)
add_test(${PROJECT_NAME} COMMAND test_weatherSettings test_openWeatherMapAPI)

target_link_libraries(test_weatherSettings
    PRIVATE
    ${SWSLibraries}
    Qt5::Test)
