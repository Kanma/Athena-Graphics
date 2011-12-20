# List the source files
set(SRCS main.cpp
)

# List the include paths
xmake_include_directories(ATHENA_GRAPHICS)

add_executable(test ${SRCS})
xmake_target_link_libraries(test ATHENA_GRAPHICS)

if (XMAKE_OGRE_FRAMEWORK)
    set_target_properties(test PROPERTIES LINK_FLAGS "${XMAKE_OGRE_LINK_FLAGS} -Wl,-rpath,@loader_path/.")
elseif (UNIX)
    set_target_properties(test PROPERTIES INSTALL_RPATH ".")
endif()
