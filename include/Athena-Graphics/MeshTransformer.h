/** @file   MeshTransformer.h
    @author Philip Abbet

    Declaration of the class 'Athena::Graphics::MeshTransformer'
*/

#ifndef _ATHENA_GRAPHICS_MESHTRANSFORMER_H_
#define _ATHENA_GRAPHICS_MESHTRANSFORMER_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreMesh.h>
#include <Ogre/OgreResourceGroupManager.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief  Utility class used to modify a mesh
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL MeshTransformer
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    /// @param  strMeshName         Name of the mesh
    /// @param  strResourceGroup    Name of the resource group in which the mesh is located
    //-----------------------------------------------------------------------------------
    MeshTransformer(const std::string& strMeshName, const std::string& strResourceGroup =
                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    /// @param  strMeshName         Name of the mesh
    /// @param  strResourceGroup    Name of the resource group in which the mesh is located
    //-----------------------------------------------------------------------------------
    MeshTransformer(const Ogre::MeshPtr& mesh);

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    ~MeshTransformer();


    //_____ Methods __________
public:
    void scale(Math::Real fUniformScale);
    void scale(Math::Real x, Math::Real y, Math::Real z);
    void scale(const Math::Vector3& scale);

    void translateOrigin(Math::Real x, Math::Real y, Math::Real z);
    void translateOrigin(const Math::Vector3& d);

    void rotate(const Math::Quaternion& q);
    void rotate(const Math::Vector3& axis, const Math::Radian& angle);

private:
    void scale(Ogre::VertexData* pVertexData, const Math::Vector3& scale);
    void translateOrigin(Ogre::VertexData* pVertexData, const Math::Vector3& d, Math::Vector3& max);
    void rotate(Ogre::VertexData* pVertexData, const Math::Quaternion& q, Math::Vector3& max);


    //_____ Attributes __________
private:
    Ogre::MeshPtr   m_mesh;
};

}
}

#endif
