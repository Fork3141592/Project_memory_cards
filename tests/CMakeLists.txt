cmake_minimum_required(VERSION 3.15)
project(flipping_cards_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#делаем exeшник

add_executable(run_tests
    test_main.cpp
    card_actions.cpp
    card_logic_tests.cpp
    mocks.cpp

)

target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

