set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")

set(DATA_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
set(PROJECT_EXPORT_DIR ${PROJECT_SOURCE_DIR}/export)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_EXPORT_DIR}/lib)

# -------------- Core Lib
file(GLOB CORE_SOURCE
    core/*.cpp)

file(GLOB CORE_HEADER
    core/*.h)

add_library(SWSCoreLib SHARED ${CORE_HEADER} ${CORE_SOURCE} )
target_link_libraries(SWSCoreLib
    PRIVATE
    Qt5::Core)

# -------------- Weather Lib
file(GLOB WEATHER_SOURCE
    weather/*.cpp
    weather/settings/*.cpp
    weather/settings/settingsgroup/*.cpp
    weather/messages/*.cpp
    weather/messages/operators/*.cpp)

file(GLOB WEATHER_HEADER
    weather/*.h
    weather/settings/*.h
    weather/settings/settingsgroup/*.h
    weather/messages/*.h
    weather/messages/operators/*.h)

add_library(SWSWeatherLib SHARED ${WEATHER_HEADER} ${WEATHER_SOURCE} )
target_link_libraries(SWSWeatherLib
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Mqtt)

# -------------- Utils Lib
file(GLOB UTILS_SOURCE
    utils/*.cpp
    utils/location/*.cpp)

file(GLOB UTILS_HEADER
    utils/*.h
    utils/location/*.h)

file(GLOB UTILS_DATA
  utils/data/*
)

add_subdirectory(utils/models/SortFilterProxyModel)
file(COPY ${UTILS_DATA} DESTINATION ${DATA_OUTPUT_DIR})

add_library(SWSUtilsLib SHARED ${UTILS_SOURCE} ${UTILS_HEADER} $<TARGET_OBJECTS:SortFilterProxyModel>)
target_link_libraries(SWSUtilsLib
    PRIVATE
    Qt5::Core
    Qt5::Quick)

# -------------- Application executable
qt5_add_resources(
    QRC_RESSOURCES
    qml/qml.qrc
    qml/images/images.qrc)

file(GLOB APP_SOURCE
    *.cpp)

file(GLOB APP_HEADER
    *.h)

set(APP_NAME ${PROJECT_NAME})
add_executable(${APP_NAME} ${APP_HEADER} ${APP_SOURCE} ${QRC_RESSOURCES})

target_compile_definitions(
    ${APP_NAME}
    PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    ${APP_NAME}
    PRIVATE
    SWSCoreLib
    SWSWeatherLib
    SWSUtilsLib
    Qt5::Core
    Qt5::Quick)


# -------------- Sensors simulator
set(SIMULATOR_SCRIPTS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/simulator/scripts)

qt5_add_resources(
    QRC_SIMULATOR_RESSOURCES
    simulator/qml/qml_simulator.qrc)

file(GLOB SIMULATOR_SOURCE
    simulator/*.cpp)

file(GLOB SIMULATOR_HEADER
    simulator/*.h)

file(GLOB SIMULATOR_SCRIPTS
    simulator/scripts/*
)

file(COPY ${SIMULATOR_SCRIPTS} DESTINATION ${SIMULATOR_SCRIPTS_OUTPUT_DIR})

set(SIMULATOR_APP_NAME sensorsSimulator)
add_executable(${SIMULATOR_APP_NAME} ${SIMULATOR_HEADER} ${SIMULATOR_SOURCE} ${QRC_SIMULATOR_RESSOURCES})

target_compile_definitions(
    ${SIMULATOR_APP_NAME}
    PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    ${SIMULATOR_APP_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Quick)
