# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(ATHENA_GRAPHICS)


# List the source files
set(SRCS module.cpp
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

xmake_project_link(ATHENA_GRAPHICS_SCRIPTING_MODULE ATHENA_GRAPHICS ATHENA_SCRIPTING)

create_scripting_module(ATHENA_GRAPHICS_SCRIPTING_MODULE "Athena.Graphics" "${JS_SRCS}")
