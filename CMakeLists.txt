cmake_minimum_required(VERSION 4.1)

project(Tema_3_POO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
        main.cpp)

set(SFML_BASE_DIR "D:/libs/SFML-2.6.1")

set(MANUAL_INCLUDE_DIR "${SFML_BASE_DIR}/include")
set(MANUAL_LIB_DIR "${SFML_BASE_DIR}/lib")

message("--> Forcing include path to: ${MANUAL_INCLUDE_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE "${MANUAL_INCLUDE_DIR}")


target_link_directories(${PROJECT_NAME} PRIVATE "${MANUAL_LIB_DIR}")


target_link_libraries(${PROJECT_NAME}
        "${MANUAL_LIB_DIR}/libsfml-graphics.a"
        "${MANUAL_LIB_DIR}/libsfml-audio.a"
        "${MANUAL_LIB_DIR}/libsfml-window.a"
        "${MANUAL_LIB_DIR}/libsfml-system.a"
)
