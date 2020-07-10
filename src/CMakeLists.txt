# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(pang_library ${SOURCE_LIST} ${HEADER_LIST})
#add_library(pang_library Game.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(pang_library PUBLIC ../include)

# All users of this library will need at least C++17
target_compile_features(pang_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

#target_link_libraries (pang_library sfml-graphics sfml-window sfml-system)
