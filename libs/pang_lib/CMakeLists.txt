find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(lib_name "pang_lib")

set(sources
    src/AiPaddle.cpp
    src/Ball.cpp
    src/Entity.cpp
    src/Game.cpp
    src/Menu.cpp
    src/Paddle.cpp
    src/SplashScreen.cpp
    src/World.cpp
)

set(headers
    inc/AiPaddle.hpp
    inc/Ball.hpp
    inc/Entity.hpp
    inc/Game.hpp
    inc/Menu.hpp
    inc/Paddle.hpp
    inc/SplashScreen.hpp
    inc/World.hpp
)

# the library will be static or dynamic based on user's input in cmake command
add_library(${lib_name} 
    ${headers}
    ${sources}
)

target_include_directories(${lib_name}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_link_libraries(${lib_name}
    sfml-graphics
    sfml-window
    sfml-system
)
