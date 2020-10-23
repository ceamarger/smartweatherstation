set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    weather/*.cpp)

file(GLOB WEATHER_HEADER
    weather/*.h)

add_library(SWSWeatherLib SHARED ${WEATHER_HEADER} ${WEATHER_SOURCE} )
target_link_libraries(SWSWeatherLib
    PRIVATE
    Qt5::Core
    Qt5::Quick)

# -------------- Utils Lib
file(GLOB UTILS_SOURCE
    utils/*.cpp)

file(GLOB UTILS_HEADER
    utils/*.h)

add_library(SWSUtilsLib SHARED ${UTILS_SOURCE} ${UTILS_HEADER} )
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

add_executable(${PROJECT_NAME} ${APP_HEADER} ${APP_SOURCE} ${QRC_RESSOURCES})

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    SWSCoreLib
    SWSWeatherLib
    SWSUtilsLib
    Qt5::Core
    Qt5::Quick)
