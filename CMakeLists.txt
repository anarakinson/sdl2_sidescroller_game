cmake_minimum_required(VERSION 3.12)

project(sdl_test)

add_executable(
    game 
    main.cpp
    source/test.cpp
    source/game.cpp
)


target_include_directories(
    game 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/
    "$ENV{SDL_LIBRARY}/include/"
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/source/
)

target_link_libraries(
    game 
    "$ENV{SDL_LIBRARY}/lib/x64/SDL2.lib"
)

add_custom_target(
    copy_dll
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/SDL2.dll ${CMAKE_BINARY_DIR}/Debug/SDL2.dll
)

add_dependencies(game copy_dll)


set_target_properties(
    game PROPERTIES 
    SXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)