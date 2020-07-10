
set(ExecutableName "pang")

add_executable(${ExecutableName} pang.cpp)
target_compile_features(${ExecutableName} PRIVATE cxx_std_17)
target_link_libraries(${ExecutableName} PRIVATE pang_library sfml-graphics sfml-window sfml-system)
