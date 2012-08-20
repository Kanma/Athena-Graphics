# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(OGRE)


# List the source files
set(SRCS module.cpp
)

set(JS_SRCS ""
)


# Declaration of the module
xmake_create_dynamic_library(OGRE_SCRIPTING_MODULE Ogre-Scripting-module
                            "1.7.3" "1.7.3" ${SRCS})

xmake_project_link(OGRE_SCRIPTING_MODULE ATHENA_SCRIPTING OGRE)

create_scripting_module(OGRE_SCRIPTING_MODULE "Ogre" "${JS_SRCS}")
