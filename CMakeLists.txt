cmake_minimum_required(VERSION 3.12)

project(sdl_test)


add_executable(
    game 
    main.cpp
    source/test.cpp
    source/game.cpp
    source/collision.cpp
)


find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)


target_link_libraries(
    game
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)


target_include_directories(
    game 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_directories(
    game
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/
)


set_target_properties(
    game PROPERTIES 
    SXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(
        game PRIVATE
        /W4
    )
else ()
    target_compile_options(
        game PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()