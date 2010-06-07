/** @file   Prerequisites.h
    @author Philip Abbet
    
    Declaration of the types of the Athena-Graphics module
*/

#ifndef _ATHENA_GRAPHICS_PREREQUISITES_H_
#define _ATHENA_GRAPHICS_PREREQUISITES_H_

#include <Athena-Entities/Prerequisites.h>
#include <Athena-Graphics/Config.h>
#include <Ogre/OgrePrerequisites.h>


//----------------------------------------------------------------------------------------
/// @brief	Main namespace. All the components of the Athena engine belongs to this
///			namespace
//----------------------------------------------------------------------------------------
namespace Athena
{
	//------------------------------------------------------------------------------------
	/// @brief	Contains all the graphics-related classes
	//------------------------------------------------------------------------------------
    namespace Graphics
    {
        class GraphicTools;
        class Line3D;
        class LinesList;
        class MeshBuilder;
        class MeshTransformer;
        class SceneRenderTargetListener;

    	//------------------------------------------------------------------------------------
    	/// @brief	Contains all the visual components
    	//------------------------------------------------------------------------------------
        namespace Visual
        {
            class Camera;
            class DirectionalLight;
            class Object;
            class Plane;
            class PointLight;
            class Spotlight;
            class VisualComponent;
        }

    	/// The Ogre Root
    	extern ATHENA_SYMBOL Ogre::Root*			pOgreRoot;
    	/// The Ogre Scene manager
    	extern ATHENA_SYMBOL Ogre::SceneManager*	pSceneManager;
    	/// The window
    	extern ATHENA_SYMBOL Ogre::RenderWindow*	pMainWindow;
    }
}

#endif
