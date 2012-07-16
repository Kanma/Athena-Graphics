# File generation
configure_file(${ATHENA_GRAPHICS_SOURCE_DIR}/src/module.cpp.in
               ${XMAKE_BINARY_DIR}/generated/Athena-Graphics/module.cpp)


# List the source files
set(SRCS ${XMAKE_BINARY_DIR}/generated/Athena-Graphics/module.cpp
         Conversions.cpp
         GraphicTools.cpp
         Line3D.cpp
         LinesList.cpp
         MeshAnimation.cpp
         MeshBuilder.cpp
         MeshTransformer.cpp
         OgreLogListener.cpp
         SceneRenderTargetListener.cpp
         Debug/AudioListener.cpp
         Debug/AudioSource.cpp
         Debug/Axes.cpp
         Debug/Camera.cpp
         Debug/DebugComponent.cpp
         Debug/DirectionalLight.cpp
         Debug/PointLight.cpp
         Debug/Skeleton.cpp
         Debug/Spotlight.cpp
         Visual/Camera.cpp
         Visual/DirectionalLight.cpp
         Visual/EntityComponent.cpp
         Visual/Object.cpp
         Visual/Plane.cpp
         Visual/PointLight.cpp
         Visual/Spotlight.cpp
         Visual/VisualComponent.cpp
         Visual/World.cpp
)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    set(SRCS ${SRCS} Scripting.cpp)
endif()


# List the include paths
set(INCLUDE_PATHS "${ATHENA_GRAPHICS_SOURCE_DIR}/include"
                  "${XMAKE_BINARY_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_ENTITIES)
xmake_import_search_paths(OGRE)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    xmake_import_search_paths(ATHENA_SCRIPTING)
endif()


# Declaration of the library
if (NOT ATHENA_GRAPHICS_STATIC)
    xmake_create_dynamic_library(ATHENA_GRAPHICS Athena-Graphics
                                 "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                                 "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                                 ${SRCS})

    xmake_add_to_list_property(ATHENA_GRAPHICS COMPILE_DEFINITIONS "ATHENA_GRAPHICS_EXPORTS")
else()
    xmake_create_static_library(ATHENA_GRAPHICS Athena-Graphics ${SRCS})
endif()

xmake_project_link(ATHENA_GRAPHICS ATHENA_ENTITIES OGRE)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    xmake_project_link(ATHENA_GRAPHICS ATHENA_SCRIPTING)
endif()

xmake_add_to_list_property(ATHENA_GRAPHICS COMPILE_DEFINITIONS "ATHENA_GRAPHICS_EXPORTS")


# Exportations
xmake_export_include_paths(ATHENA_GRAPHICS ${INCLUDE_PATHS})
