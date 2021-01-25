set(executable_name "pang")
add_executable(${executable_name} pang.cpp)
target_link_libraries(${executable_name} PRIVATE pang_lib)

# copy img folder to the target
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/libs/pang_lib/img/
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/img/
)
