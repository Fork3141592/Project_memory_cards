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