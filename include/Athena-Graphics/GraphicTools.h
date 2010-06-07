/** @file	GraphicTools.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::GraphicTools'
*/

#ifndef _ATHENA_GRAPHICS_GRAPHICTOOLS_H_
#define _ATHENA_GRAPHICS_GRAPHICTOOLS_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreSkeleton.h>
#include <Ogre/OgreResourceGroupManager.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief	Utility class containing graphics-related tools
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL GraphicTools
{ 
	//_____ Methods __________
public:
	static Ogre::SkeletonPtr cloneSkeleton(const Ogre::SkeletonPtr& srcSkeleton,
										   const std::string& strNewName,
										   const std::string& strNewGroup = "");

	static Ogre::SkeletonPtr cloneSkeleton(const std::string& strSrcSkeleton,
										   const std::string& strNewName,
										   const std::string& strGroup = 
										   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
										   const std::string& strNewGroup = "");

	static Ogre::MeshPtr cloneMesh(const Ogre::MeshPtr& srcMesh,
								   const std::string& strNewName,
								   const std::string& strNewSkeletonName = "",
								   const std::string& strNewGroup = "");

	static Ogre::MeshPtr cloneMesh(const std::string& strSrcMesh,
								   const std::string& strNewName,
								   const std::string& strNewSkeletonName = "",
								   const std::string& strGroup = 
								   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
								   const std::string& strNewGroup = "");

	static void setPolygonMode(Ogre::Entity* pOgreEntity, Ogre::PolygonMode mode,
							   const std::string& strMaterialsSuffix,
							   const std::string& strNewGroup = "");

	static void setPolygonMode(Visual::Object* pVisualPart, Ogre::PolygonMode mode,
							   const std::string& strMaterialsSuffix,
							   const std::string& strNewGroup = "");

	static void setPolygonMode(Entities::Entity* pEntity, Ogre::PolygonMode mode,
							   const std::string& strMaterialsSuffix,
							   const std::string& strNewGroup = "");

	static void resetMaterials(Ogre::Entity* pOgreEntity);
	static void resetMaterials(Visual::Object* pVisualPart);
	static void resetMaterials(Entities::Entity* pEntity);
};

}
}

#endif
