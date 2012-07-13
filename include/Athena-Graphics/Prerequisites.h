/** @file   Prerequisites.h
    @author Philip Abbet

    Declaration of the types of the Athena-Graphics module
*/

#ifndef _ATHENA_GRAPHICS_PREREQUISITES_H_
#define _ATHENA_GRAPHICS_PREREQUISITES_H_

#include <Athena-Entities/Prerequisites.h>
#include <Athena-Graphics/Config.h>
#include <Ogre/OgrePrerequisites.h>


/// Used to export symbols from the library
#if (ATHENA_PLATFORM == ATHENA_PLATFORM_WIN32) && !ATHENA_GRAPHICS_STATIC
#    ifdef ATHENA_GRAPHICS_EXPORTS
#        define ATHENA_GRAPHICS_SYMBOL  __declspec(dllexport)
#    else
#        define ATHENA_GRAPHICS_SYMBOL  __declspec(dllimport)
#    endif
#else
#    define ATHENA_GRAPHICS_SYMBOL
#endif


//----------------------------------------------------------------------------------------
/// @brief  Main namespace. All the components of the Athena engine belongs to this
///         namespace
//----------------------------------------------------------------------------------------
namespace Athena
{
    //------------------------------------------------------------------------------------
    /// @brief  Contains all the graphics-related classes
    //------------------------------------------------------------------------------------
    namespace Graphics
    {
        class GraphicTools;
        class Line3D;
        class LinesList;
        class MeshAnimation;
        class MeshBuilder;
        class MeshTransformer;
        class OgreLogListener;
        class SceneRenderTargetListener;

        //------------------------------------------------------------------------------------
        /// @brief  Contains all the debug components
        //------------------------------------------------------------------------------------
        namespace Debug
        {
            class AudioListener;
            class AudioSource;
            class Axes;
            class Camera;
            class DebugComponent;
            class DirectionalLight;
            class PointLight;
            class Skeleton;
            class Spotlight;
        }

        //------------------------------------------------------------------------------------
        /// @brief  Contains all the visual components
        //------------------------------------------------------------------------------------
        namespace Visual
        {
            class Camera;
            class DirectionalLight;
            class EntityComponent;
            class Object;
            class Plane;
            class PointLight;
            class Spotlight;
            class VisualComponent;
            class World;
        }


        //------------------------------------------------------------------------------------
        /// @brief  Initialize the Graphics module
        ///
        /// The Root object of Ogre is created here
        ///
        /// @param strPluginFileName        The file that contains plugins information.
        ///                                 Defaults to "plugins.cfg", may be left blank to
        ///                                 ignore.
        /// @param strOgreConfigFileName    The file that contains the configuration to be
        ///                                 loaded. Defaults to "ogre.cfg", may be left blank
        ///                                 to load nothing.
        /// @param strOgreLogFileName       The logfile to create, defaults to Ogre.log, may
        ///                                 be left blank if you've already set up LogManager
        ///                                 & Log yourself
        /// @return                         The Ogre Root
        //------------------------------------------------------------------------------------
        extern Ogre::Root* initialize(const std::string& strPluginFileName = "plugins.cfg",
                                      const std::string& strOgreConfigFileName = "ogre.cfg",
                                      const std::string& strOgreLogFileName = "Ogre.log");



        ATHENA_GRAPHICS_SYMBOL extern const char* VERSION;
    }
}

#endif
