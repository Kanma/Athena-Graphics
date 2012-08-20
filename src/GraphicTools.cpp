/** @file   GraphicTools.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::GraphicTools'
*/

// Athena's includes
#include <Athena-Graphics/GraphicTools.h>
#include <Athena-Graphics/Visual/Object.h>
#include <Athena-Entities/Entity.h>
#include <Athena-Entities/Component.h>

// Ogre's includes
#include <Ogre/OgreSkeletonManager.h>
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreMaterialManager.h>
#include <Ogre/OgreMesh.h>
#include <Ogre/OgreSubMesh.h>
#include <Ogre/OgreBone.h>
#include <Ogre/OgreAnimation.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreSubEntity.h>
#include <Ogre/OgreTechnique.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Log;
using namespace std;

using Ogre::Bone;
using Ogre::Entity;
using Ogre::Material;
using Ogre::MaterialPtr;
using Ogre::Mesh;
using Ogre::MeshManager;
using Ogre::MeshPtr;
using Ogre::NodeAnimationTrack;
using Ogre::SceneNode;
using Ogre::Skeleton;
using Ogre::SkeletonManager;
using Ogre::SkeletonPtr;
using Ogre::SubEntity;
using Ogre::Technique;
using Ogre::TransformKeyFrame;


/************************************** METHODS ****************************************/

Ogre::SkeletonPtr GraphicTools::cloneSkeleton(const Ogre::SkeletonPtr& srcSkeleton,
                                              const std::string& strNewName,
                                              const std::string& strNewGroup)
{
    // Assertions
    assert(!srcSkeleton.isNull());
    assert(!strNewName.empty());

    // Determine the resource group of the new skeleton
    string strGroup = strNewGroup;
    if (strNewGroup.empty())
        strGroup = srcSkeleton->getGroup();

    // Create the new skeleton
    SkeletonPtr dstSkeleton = (SkeletonPtr) SkeletonManager::getSingleton().create(strNewName, strGroup, true);

    // Clone the bones
    for (unsigned short usHandle = 0; usHandle < srcSkeleton->getNumBones(); ++usHandle)
    {
        const Bone* pSrcBone = srcSkeleton->getBone(usHandle);

        Bone* pDstBone = dstSkeleton->createBone(pSrcBone->getName(), usHandle);

        // Sets initial transform
        pDstBone->setPosition(pSrcBone->getInitialPosition());
        pDstBone->setOrientation(pSrcBone->getInitialOrientation());
        pDstBone->setScale(pSrcBone->getInitialScale());
        pDstBone->setInitialState();
    }

    // Link new bones to parent
    for (unsigned short usHandle = 0; usHandle < srcSkeleton->getNumBones(); ++usHandle)
    {
        const Bone* pSrcBone = srcSkeleton->getBone(usHandle);

        const Bone* pSrcParent = static_cast<Bone*>(pSrcBone->getParent());
        if (pSrcParent)
        {
            Bone* pDstParent = dstSkeleton->getBone(pSrcParent->getHandle());
            Bone* pDstBone = dstSkeleton->getBone(usHandle);
            pDstParent->addChild(pDstBone);
        }
    }

    // Derive root bones in case it was changed
    dstSkeleton->getRootBoneIterator();

    // Reset binding pose for new skeleton
    dstSkeleton->reset(true);
    dstSkeleton->setBindingPose();


    // Clone the animations
    for (unsigned short i = 0; i < srcSkeleton->getNumAnimations(); ++i)
    {
        // Get animation of source skeleton by the given index
        const Ogre::Animation* pSrcAnimation = srcSkeleton->getAnimation(i);

        // Create target animation
        Ogre::Animation* pDstAnimation = dstSkeleton->createAnimation(pSrcAnimation->getName(), pSrcAnimation->getLength());

        // Copy interpolation modes
        pDstAnimation->setInterpolationMode(pSrcAnimation->getInterpolationMode());
        pDstAnimation->setRotationInterpolationMode(pSrcAnimation->getRotationInterpolationMode());

        // Copy track for each bone
        for (unsigned short usHandle = 0; usHandle < srcSkeleton->getNumBones(); ++usHandle)
        {
            if (pSrcAnimation->hasNodeTrack(usHandle))
            {
                // Clone track from source animation
                const NodeAnimationTrack* pSrcTrack = pSrcAnimation->getNodeTrack(usHandle);
                NodeAnimationTrack* pDstTrack = pDstAnimation->createNodeTrack(usHandle, dstSkeleton->getBone(usHandle));
                pDstTrack->setUseShortestRotationPath(pSrcTrack->getUseShortestRotationPath());

                for (unsigned short k = 0; k < pSrcTrack->getNumKeyFrames(); ++k)
                {
                    const TransformKeyFrame* pSrcKeyFrame = pSrcTrack->getNodeKeyFrame(k);
                    TransformKeyFrame* pDstKeyFrame = pDstTrack->createNodeKeyFrame(pSrcKeyFrame->getTime());

                    pDstKeyFrame->setTranslate(pSrcKeyFrame->getTranslate());
                    pDstKeyFrame->setRotation(pSrcKeyFrame->getRotation());
                    pDstKeyFrame->setScale(pSrcKeyFrame->getScale());
                }
            }
        }
    }

    return dstSkeleton;
}

//-----------------------------------------------------------------------

Ogre::SkeletonPtr GraphicTools::cloneSkeleton(const std::string& strSrcSkeleton,
                                              const std::string& strNewName,
                                              const std::string& strGroup,
                                              const std::string& strNewGroup)
{
    // Assertions
    assert(!strSrcSkeleton.empty());
    assert(!strNewName.empty());
    assert(!strGroup.empty());

    SkeletonPtr srcSkeleton = SkeletonManager::getSingletonPtr()->getByName(strSrcSkeleton);
    if (srcSkeleton.isNull())
    {
        srcSkeleton = SkeletonManager::getSingletonPtr()->load(strSrcSkeleton, strGroup);
        if (srcSkeleton.isNull())
            return srcSkeleton;
    }

    return cloneSkeleton(srcSkeleton, strNewName, strNewGroup);
}

//-----------------------------------------------------------------------

Ogre::MeshPtr GraphicTools::cloneMesh(const Ogre::MeshPtr& srcMesh, const std::string& strNewName,
                                      const std::string& strNewSkeletonName, const std::string& strNewGroup)
{
    // Assertions
    assert(!srcMesh.isNull());
    assert(!strNewName.empty());
    assert(!srcMesh->hasSkeleton() || !strNewSkeletonName.empty());

    MeshPtr cloneMesh = srcMesh->clone(strNewName, strNewGroup);

    if (srcMesh->hasSkeleton())
    {
        SkeletonPtr cloneSkeleton = SkeletonManager::getSingletonPtr()->getByName(strNewSkeletonName);
        if (cloneSkeleton.isNull())
            cloneSkeleton = GraphicTools::cloneSkeleton(srcMesh->getSkeleton(), strNewSkeletonName);

        cloneMesh->setSkeletonName(strNewSkeletonName);
    }

    return cloneMesh;
}

//-----------------------------------------------------------------------

Ogre::MeshPtr GraphicTools::cloneMesh(const std::string& strSrcMesh, const std::string& strNewName,
                                      const std::string& strNewSkeletonName,
                                      const std::string& strGroup, const std::string& strNewGroup)
{
    // Assertions
    assert(!strSrcMesh.empty());
    assert(!strNewName.empty());
    assert(!strGroup.empty());

    MeshPtr srcMesh = MeshManager::getSingletonPtr()->getByName(strSrcMesh);
    if (srcMesh.isNull())
    {
        srcMesh = MeshManager::getSingletonPtr()->load(strSrcMesh, strGroup);
        if (srcMesh.isNull())
            return srcMesh;
    }

    return cloneMesh(srcMesh, strNewName, strNewSkeletonName, strNewGroup);
}

//-----------------------------------------------------------------------

void GraphicTools::setPolygonMode(Ogre::Entity* pOgreEntity, Ogre::PolygonMode mode,
                                  const std::string& strMaterialsSuffix,
                                  const std::string& strNewGroup)
{
    // Assertions
    assert(pOgreEntity);
    assert(!strMaterialsSuffix.empty());

    // Iterate through all the sub-entities
    for (unsigned int i = 0; i < pOgreEntity->getNumSubEntities(); ++i)
    {
        // Retrieve the sub-entity and its material
        SubEntity*  pSubEntity  = pOgreEntity->getSubEntity(i);
        MaterialPtr material    = pSubEntity->getMaterial();

        // Compute a name for the clone of the material
        string strCloneMaterial = material->getName() + "/" + strMaterialsSuffix;

        // If the material doesn't already exists, clone the original one
        if (!Ogre::MaterialManager::getSingleton().resourceExists(strCloneMaterial))
            MaterialPtr cloneMaterial = material->clone(strCloneMaterial, !strNewGroup.empty(), strNewGroup);

        // Assign the cloned material to the sub-entity
        pSubEntity->setMaterialName(strCloneMaterial);

        // Retrieve the current technique used by the sub-entity
        Technique* pTechnique = pSubEntity->getTechnique();

        // Iterate over the passes of the technique to change the polygon mode
        Technique::PassIterator passIter = pTechnique->getPassIterator();
        while (passIter.hasMoreElements())
            passIter.getNext()->setPolygonMode(mode);
    }
}

//-----------------------------------------------------------------------

void GraphicTools::setPolygonMode(Visual::Object* pVisualPart, Ogre::PolygonMode mode,
                                  const std::string& strMaterialsSuffix,
                                  const std::string& strNewGroup)
{
    // Assertions
    assert(pVisualPart);
    assert(pVisualPart->getOgreEntity());
    assert(!strMaterialsSuffix.empty());

    setPolygonMode(pVisualPart->getOgreEntity(), mode, strMaterialsSuffix, strNewGroup);
}

//-----------------------------------------------------------------------

void GraphicTools::setPolygonMode(Entities::Entity* pEntity, Ogre::PolygonMode mode,
                                  const std::string& strMaterialsSuffix,
                                  const std::string& strNewGroup)
{
    // Assertions
    assert(pEntity);
    assert(!strMaterialsSuffix.empty());

    // Iterate through the visual parts
    Component::tComponentsIterator iter = pEntity->getComponentsIterator();
    while (iter.hasMoreElements())
    {
        EntityComponent* pComponent = EntityComponent::cast(iter.getNext());
        if (pComponent)
        {
            SceneNode::ObjectIterator iter = pComponent->getSceneNode()->getAttachedObjectIterator();
            while (iter.hasMoreElements())
            {
                Ogre::Entity* pOgreEntity = dynamic_cast<Ogre::Entity*>(iter.getNext());
                if (pOgreEntity)
                    setPolygonMode(pOgreEntity, mode, strMaterialsSuffix, strNewGroup);
            }
        }
    }
}

//-----------------------------------------------------------------------

void GraphicTools::resetMaterials(Ogre::Entity* pOgreEntity)
{
    // Assertions
    assert(pOgreEntity);

    // Iterate through all the sub-entities
    for (unsigned int i = 0; i < pOgreEntity->getNumSubEntities(); ++i)
    {
        // Retrieve the sub-entity
        SubEntity*  pSubEntity  = pOgreEntity->getSubEntity(i);

        // Retrieve the name of the original material of the sub-mesh corresponding to the sub-entity
        string strOriginalMaterial = pSubEntity->getSubMesh()->getMaterialName();

        // If the current material isn't the original one, change it
        if (pSubEntity->getMaterialName() != strOriginalMaterial)
            pSubEntity->setMaterialName(strOriginalMaterial);
    }
}

//-----------------------------------------------------------------------

void GraphicTools::resetMaterials(Visual::Object* pVisualPart)
{
    // Assertions
    assert(pVisualPart);
    assert(pVisualPart->getOgreEntity());

    resetMaterials(pVisualPart->getOgreEntity());
}

//-----------------------------------------------------------------------

void GraphicTools::resetMaterials(Entities::Entity* pEntity)
{
    // Assertions
    assert(pEntity);

    // Iterate through the visual parts
    Component::tComponentsIterator iter = pEntity->getComponentsIterator();
    while (iter.hasMoreElements())
    {
        EntityComponent* pComponent = EntityComponent::cast(iter.getNext());
        if (pComponent)
        {
            SceneNode::ObjectIterator iter = pComponent->getSceneNode()->getAttachedObjectIterator();
            while (iter.hasMoreElements())
            {
                Ogre::Entity* pOgreEntity = dynamic_cast<Ogre::Entity*>(iter.getNext());
                if (pOgreEntity)
                    resetMaterials(pOgreEntity);
            }
        }
    }
}
