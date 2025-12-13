cmake_minimum_required(VERSION 3.20)

project(card_game CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

# --- Пути к исходникам ---
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SRC_DIR})

# копируем папку images в папку сборки, чтобы exe видел её при запуске
file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})

# --- Список исходных файлов проекта ---
set(SOURCES
    #${SRC_DIR}/main.cpp
    ${SRC_DIR}/graphics.cpp
    ${SRC_DIR}/logic.cpp
    ${SRC_DIR}/Graph_lib/Graph.cpp
    ${SRC_DIR}/Graph_lib/GUI.cpp
    ${SRC_DIR}/Graph_lib/Window.cpp
    
)

# --- Создаём исполняемый файл ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Линкуем FLTK ---
target_link_libraries(${PROJECT_NAME} PRIVATE
    fltk
    fltk_images
)


find_package(FLTK)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${fltk_SOURCE_DIR}
)
