# File generation
configure_file(${ATHENA_GRAPHICS_SOURCE_DIR}/src/module.cpp.in
               ${XMAKE_BINARY_DIR}/generated/Athena-Graphics/module.cpp)


# List the headers files
set(HEADERS ${XMAKE_BINARY_DIR}/include/Athena-Graphics/Config.h
           ../include/Athena-Graphics/Conversions.h
           ../include/Athena-Graphics/GraphicTools.h
           ../include/Athena-Graphics/Line3D.h
           ../include/Athena-Graphics/LinesList.h
           ../include/Athena-Graphics/MeshAnimation.h
           ../include/Athena-Graphics/MeshBuilder.h
           ../include/Athena-Graphics/MeshTransformer.h
           ../include/Athena-Graphics/OgreLogListener.h
           ../include/Athena-Graphics/Prerequisites.h
           ../include/Athena-Graphics/SceneRenderTargetListener.h
           ../include/Athena-Graphics/Debug/AudioListener.h
           ../include/Athena-Graphics/Debug/AudioSource.h
           ../include/Athena-Graphics/Debug/Axes.h
           ../include/Athena-Graphics/Debug/Camera.h
           ../include/Athena-Graphics/Debug/DebugComponent.h
           ../include/Athena-Graphics/Debug/DirectionalLight.h
           ../include/Athena-Graphics/Debug/PointLight.h
           ../include/Athena-Graphics/Debug/Skeleton.h
           ../include/Athena-Graphics/Debug/Spotlight.h
           ../include/Athena-Graphics/Visual/Camera.h
           ../include/Athena-Graphics/Visual/DirectionalLight.h
           ../include/Athena-Graphics/Visual/EntityComponent.h
           ../include/Athena-Graphics/Visual/Object.h
           ../include/Athena-Graphics/Visual/Plane.h
           ../include/Athena-Graphics/Visual/PointLight.h
           ../include/Athena-Graphics/Visual/Spotlight.h
           ../include/Athena-Graphics/Visual/VisualComponent.h
           ../include/Athena-Graphics/Visual/World.h
)


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
    set(HEADERS ${HEADERS} ../include/Athena-Graphics/Scripting.h)
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
xmake_create_dynamic_library(ATHENA_GRAPHICS Athena-Graphics
                             "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                             "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                             ${HEADERS} ${SRCS})

xmake_add_to_list_property(ATHENA_GRAPHICS COMPILE_DEFINITIONS "ATHENA_GRAPHICS_EXPORTS")

if (APPLE)
    xmake_add_to_property(ATHENA_GRAPHICS LINK_FLAGS "-framework CoreFoundation")
endif()

xmake_project_link(ATHENA_GRAPHICS ATHENA_ENTITIES OGRE)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    xmake_project_link(ATHENA_GRAPHICS ATHENA_SCRIPTING)
endif()


# Exportations
xmake_export_include_paths(ATHENA_GRAPHICS ${INCLUDE_PATHS})
