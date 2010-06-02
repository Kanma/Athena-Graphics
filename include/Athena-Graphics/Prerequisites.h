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
        class Line3D;
        class LinesList;
        class MeshBuilder;
    }
}

#endif
