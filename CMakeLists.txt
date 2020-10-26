cmake_minimum_required(VERSION 3.5)

project(LRWidgets LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "d")

# declare variables
set(BUILD_SHARED_LIBRARY FALSE CACHE BOOL FALSE)
set(BUILD_EXAMPLES TRUE CACHE BOOL TRUE)

find_package(Qt5 COMPONENTS Widgets Charts LinguistTools OpenGL CONFIG REQUIRED)
set(TS_FILES translation/LRWidgets_zh_CN.ts)

#add_subdirectory(widgets)
set(INCLUDE_DIRS
    ${INCLUDE_DIRS}
)

FILE(GLOB BASE_HEADERS *.h)

FILE(GLOB COMMON_HEADERS common/*.h)
FILE(GLOB COMMON_SOURCES common/*.cpp)

FILE(GLOB UTIL_HEADERS util/*.h)
FILE(GLOB UTIL_SOURCES util/*.cpp)

FILE(GLOB WIDGET_HEADERS widget/*.h)
FILE(GLOB WIDGET_SOURCES widget/*.cpp)

FILE(GLOB RES res/*.qrc)
FILE(GLOB TRANSLATIONS translation/*.ts)

FILE(GLOB MOCS ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/*.cpp)

set(OTHER_FILES
    README.md
    LICENSE.md
    .gitignore
)

source_group("ui" FILES ${UIS})
source_group("others" FILES ${OTHER_FILES})

set(HEADER_FILES
    ${HEADER_FILES}
    ${BASE_HEADERS}
    ${COMMON_HEADERS}
    ${UI_HEADERS}
    ${UTIL_HEADERS}
    ${WIDGET_HEADERS}
)

set(SRC_FILES
    ${SRC_FILES}
    ${COMMON_SOURCES}
    ${UI_SOURCES}
    ${UI_FILES}
    ${UTIL_SOURCES}
    ${WIDGET_SOURCES}
    ${RES}
)

IF(MSVC)
    source_group("base" FILES ${BASE_HEADERS})
    source_group("common" FILES ${COMMON_SOURCES})
    source_group("common" FILES ${COMMON_HEADERS})
    source_group("ui" FILES ${UI_SOURCES} ${UI_FILES})
    source_group("ui" FILES ${UI_HEADERS})
    source_group("util" FILES ${UTIL_SOURCES})
    source_group("util" FILES ${UTIL_HEADERS})
    source_group("widget" FILES ${WIDGET_HEADERS})
    source_group("widget" FILES ${WIDGET_SOURCES})
    source_group("mocs" FILES ${MOCS})
    source_group("res" FILES ${RES})
ENDIF(MSVC)

include_directories(${INCLUDE_DIRS})

set(LINK_LIBRARIES 
    Qt5::Widgets Qt5::Charts Qt5::OpenGL
)

if(BUILD_SHARED_LIBRARY)
    SET(BUILD_LIBRARY_MODE SHARED)
else(BUILD_SHARED_LIBRARY)
    SET(BUILD_LIBRARY_MODE STATIC)
endif(BUILD_SHARED_LIBRARY)

add_library(${PROJECT_NAME} ${BUILD_LIBRARY_MODE} ${SRC_FILES} ${SRC_FILES} ${HEADER_FILES} ${OTHER_FILES} ${TS_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE EXPORT_LRWIDGETS BUILD_SHARED_LIBRARY)

set(QM_FILES
    ${QM_FILES}
    ${SRC_FILES}
    ${HEADER_FILES}
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_subdirectory(examples)

## Install 
INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

INSTALL(FILES 
            "${CMAKE_SOURCE_DIR}/README.md"
            "${CMAKE_SOURCE_DIR}/LICENSE.md"
        DESTINATION ${CMAKE_INSTALL_PREFIX})
INSTALL(CODE "
            if (EXISTS ${CMAKE_SOURCE_DIR}/translations/${PROJECT_NAME}_zh_CN.qm)
            INSTALL(FILES
                ${CMAKE_SOURCE_DIR}/translations/${PROJECT_NAME}_zh_CN.qm
            DESTINATION ${CMAKE_INSTALL_PREFIX}/translations)
        endif()")

INSTALL(FILES ${BASE_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
INSTALL(FILES ${WIDGET_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/widget)
INSTALL(FILES ${COMMON_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/common)
INSTALL(FILES ${UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/util)
INSTALL(FILES ${TRANSLATIONS} DESTINATION ${CMAKE_INSTALL_PREFIX}/translations)

