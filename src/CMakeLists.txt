set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt5_add_resources(QRC_RESSOURCES qml/qml.qrc)

set(SOURCE
    ${SOURCE}
    main.cpp)

set(HEADER
    ${HEADER})

add_executable(${PROJECT_NAME} ${HEADER} ${SOURCE} ${QRC_RESSOURCES})

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Quick)
