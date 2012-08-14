# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(ATHENA_GRAPHICS)


# List the source files
set(SRCS module.cpp
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

set(JS_SRCS ""
)


# Declaration of the module
xmake_create_dynamic_library(ATHENA_GRAPHICS_SCRIPTING_MODULE Athena-Graphics-Scripting-module
                            "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                            "${ATHENA_GRAPHICS_VERSION_MAJOR}.${ATHENA_GRAPHICS_VERSION_MINOR}.${ATHENA_GRAPHICS_VERSION_PATCH}"
                             ${SRCS})

xmake_project_link(ATHENA_GRAPHICS_SCRIPTING_MODULE ATHENA_GRAPHICS ATHENA_SCRIPTING OGRE)

create_scripting_module(ATHENA_GRAPHICS_SCRIPTING_MODULE "Athena.Graphics" "${JS_SRCS}")
