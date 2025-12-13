<<<<<<< HEAD
cmake_minimum_required(VERSION 3.10)
project(MemoryCards)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к FLTK
set(FLTK_DIR "C:/msys64/ucrt64/lib/cmake/fltk")

# Поиск FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

# Добавление исходных файлов
add_executable(memory_cards
    graphics.cpp
    logic.cpp
)

# Линковка FLTK библиотек
target_link_libraries(memory_cards
    ${FLTK_LIBRARIES}
    ${FLTK_IMAGES_LIBRARY}
)

# Для Windows специфичные настройки
if(WIN32)
    target_link_libraries(memory_cards
        -lfltk
        -lfltk_images
        -lole32
        -luuid
        -lcomctl32
        -lws2_32
    )
    set_target_properties(memory_cards PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
=======
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

include_directories(${LIB_DIR}/Graph_lib)


project("flipping_Cards" CXX)

set(TARGET "flipping_cards")

set(HEADERS
        ${LIB_DIR}/Graph_lib/fltk.h
        ${LIB_DIR}/Graph_lib/Graph.h
        ${LIB_DIR}/Graph_lib/GUI.h
        ${LIB_DIR}/Graph_lib/Point.h
        ${LIB_DIR}/Graph_lib/Simple_window.h
        ${LIB_DIR}/Graph_lib/Window.h
        working_variant/game_card.h
)
set(SOURCES
        working_variant/graphics.cpp
        working_variant/logic.cpp
        ${LIB_DIR}/Graph_lib/Graph.cpp
        ${LIB_DIR}/Graph_lib/GUI.cpp
        ${LIB_DIR}/Graph_lib/Window.cpp
)

project(${TARGET} CXX)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)
set(FLTK_ROOT "D:\\FLTK\\bin")
find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SYSTEM ${FLTK_INCLUDE_DIR})
link_directories(${FLTK_INCLUDE_DIR}/../lib)

add_executable(${TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET} ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES} gdiplus)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${TARGET} fltk_jpeg fltk_png fltk_z)
endif()

install(TARGETS ${TARGET})

file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR}) ##для видимости картинок

add_subdirectory(tests) ##для тестов

>>>>>>> bb7a92ec1552e8c37b4b8663ce7c0f56b5047b59
