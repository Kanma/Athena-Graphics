# List the source files
set(SRCS Conversions.cpp
         Declarations.cpp
         GraphicTools.cpp
         Line3D.cpp
         LinesList.cpp
         MeshBuilder.cpp
         MeshTransformer.cpp
         SceneRenderTargetListener.cpp
         Debug/AudioListener.cpp
         Debug/AudioSource.cpp
         Debug/Camera.cpp
         Debug/DebugComponent.cpp
         Visual/Camera.cpp
         Visual/DirectionalLight.cpp
         Visual/Object.cpp
         Visual/Plane.cpp
         Visual/PointLight.cpp
         Visual/Spotlight.cpp
         Visual/VisualComponent.cpp
)

# Precompiler definitions
add_definitions(-DATHENA_EXPORTS)

# List the include paths
xmake_include_directories(ATHENA_GRAPHICS)

# Declaration of the library
if (NOT ATHENA_GRAPHICS_STATIC)
    add_library(Athena-Graphics SHARED ${SRCS})
    xmake_target_link_libraries(Athena-Graphics ATHENA_GRAPHICS)

    if (XMAKE_OGRE_FRAMEWORK)
        set_target_properties(Athena-Graphics PROPERTIES LINK_FLAGS "${XMAKE_OGRE_LINK_FLAGS} -Wl,-rpath,@loader_path/.,-rpath,@loader_path/../Frameworks")
    endif()

    # Set the INSTALL_PATH so that the dynamic library can be local
    set_target_properties(Athena-Graphics PROPERTIES BUILD_WITH_INSTALL_RPATH ON
                                                     INSTALL_NAME_DIR "@rpath"
    )

    if (UNIX)
        set_target_properties(Athena-Graphics PROPERTIES INSTALL_RPATH ".")
    endif()

else()
    add_library(Athena-Graphics STATIC ${SRCS})
endif()
