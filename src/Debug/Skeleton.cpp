/**	@file	Skeleton.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Debug::Skeleton'
*/

// Athena's includes
#include <Athena-Graphics/Debug/Skeleton.h>
#include <Athena-Graphics/Visual/Object.h>
#include <Athena-Graphics/MeshBuilder.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Core/Log/LogManager.h>

// Ogre's includes
#include <Ogre/OgreSkeletonInstance.h>
#include <Ogre/OgreBone.h>
#include <Ogre/OgreSceneNode.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreSubEntity.h>
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Debug;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Math;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::Bone;
using Ogre::Entity;
using Ogre::MeshManager;
using Ogre::MeshPtr;
using Ogre::Node;
using Ogre::SceneManager;
using Ogre::SceneNode;
using Ogre::SkeletonInstance;
using Ogre::SubEntity;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__		= "Debug/Skeleton";

///< Name of the type of entity
const std::string	Skeleton::TYPE	= "Athena/Debug/Skeleton";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Skeleton::Skeleton(const std::string& strName, Entities::ComponentsList* pList)
: DebugComponent(strName, pList), m_pSkeletonSource(0), m_pSkeletonEntity(0),
  m_strBoneMaterial("Athena/Materials/Bone"), m_strSelectedBoneMaterial("Athena/Materials/SelectedBone")
{
}

//-----------------------------------------------------------------------

Skeleton::~Skeleton()
{
	hide();
}

//-----------------------------------------------------------------------

Skeleton* Skeleton::create(const std::string& strName, ComponentsList* pList)
{
	return new Skeleton(strName, pList);
}

//-----------------------------------------------------------------------

Skeleton* Skeleton::cast(Component* pComponent)
{
	return dynamic_cast<Skeleton*>(pComponent);
}


/*************************************** METHODS ***************************************/

void Skeleton::show()
{
	// Assertions
	assert(!m_strBoneMaterial.empty());
	assert(!m_strSelectedBoneMaterial.empty());

	// Check that we have a skeleton source
	if (!m_pSkeletonSource)
		return;

	// Check that the skeleton isn't already shown
	if (m_pSkeletonEntity)
		return;

	// Retrieve the Ogre entity of the skeleton source
	Ogre::Entity* pEntity = m_pSkeletonSource->getOgreEntity();
	if (!pEntity)
		return;

	// Retrieve the skeleton of the entity
	SkeletonInstance* pSkeleton = pEntity->getSkeleton();
	if (!pSkeleton)
		return;

	const string strBaseName = m_pList->getEntity()->getName() + ".Debug[" + getName() + "]";

	// Create a mesh builder
	MeshBuilder builder(strBaseName + ".SkeletonMesh");

	// Assign the skeleton to the mesh builder
	builder.setSkeletonName(pSkeleton->getName());

	// No we create one submesh per bone, in order to be able the color the selected ones differently
	pSkeleton->reset();
	Ogre::Skeleton::BoneIterator bones = pSkeleton->getBoneIterator();
	while (bones.hasMoreElements())
	{
		Bone* pBone = bones.getNext();
		Bone* pParent = (Bone*) pBone->getParent();

		// Latest bone of the chain?
		if (pBone->numChildren() == 0)
		{
			float fMinSize			= (pParent ? pParent->getPosition().length() * 0.2f : pBone->getPosition().length() * 0.2f);
			float size				= std::max(fMinSize, pBone->getPosition().length() * 0.2f) * 0.5f;
			Vector3 bonePos			= fromOgre(pBone->_getDerivedPosition());
			Quaternion orientation	= fromOgre(pBone->_getDerivedOrientation());

			builder.begin(pBone->getName(), m_strBoneMaterial);

			Vector3 point1;
			Vector3 point2;
			Vector3 point3;

			point1 = bonePos + orientation * Vector3(-size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, 0, size);
			point3 = bonePos + orientation * Vector3(0, size, 0);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(-size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, size, 0);
			point3 = bonePos + orientation * Vector3(0, 0, -size);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(-size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, -size, 0);
			point3 = bonePos + orientation * Vector3(0, 0, size);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(-size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, 0, -size);
			point3 = bonePos + orientation * Vector3(0, -size, 0);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, 0, size);
			point3 = bonePos + orientation * Vector3(0, -size, 0);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, -size, 0);
			point3 = bonePos + orientation * Vector3(0, 0, -size);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, size, 0);
			point3 = bonePos + orientation * Vector3(0, 0, size);
			_addFace(point1, point2, point3, pBone, &builder);

			point1 = bonePos + orientation * Vector3(size, 0, 0);
			point2 = bonePos + orientation * Vector3(0, 0, -size);
			point3 = bonePos + orientation * Vector3(0, size, 0);
			_addFace(point1, point2, point3, pBone, &builder);

			builder.end();
		}
		else
		{
			Vector3 bonePos = fromOgre(pBone->_getDerivedPosition());
			Node::ChildNodeIterator children = pBone->getChildIterator();

			builder.begin(pBone->getName(), m_strBoneMaterial);

			while (children.hasMoreElements())
			{
				Bone* pChild = (Bone*) children.getNext();

				Vector3 childPos		= fromOgre(pChild->_getDerivedPosition());
				Vector3 dir				= childPos - bonePos;
				Quaternion orientation	= Vector3::UNIT_X.getRotationTo(dir);
				float width				= dir.length() * 0.2f;

				Vector3 point1;
				Vector3 point2;
				Vector3 point3;

				point1 = bonePos;
				point2 = bonePos + orientation * Vector3(width, -width * 0.5f, width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, width * 0.5f, width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, -width * 0.5f, -width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, -width * 0.5f, width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, width * 0.5f, -width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, -width * 0.5f, -width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, width * 0.5f, width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, width * 0.5f, -width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point1 = childPos;
				point2 = bonePos + orientation * Vector3(width, width * 0.5f, width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, -width * 0.5f, width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, -width * 0.5f, width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, -width * 0.5f, -width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, -width * 0.5f, -width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, width * 0.5f, -width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);

				point2 = bonePos + orientation * Vector3(width, width * 0.5f, -width * 0.5f);
				point3 = bonePos + orientation * Vector3(width, width * 0.5f, width * 0.5f);
				_addFace(point1, point2, point3, pBone, &builder);
			}

			builder.end();
		}
	}

    // Copy the bounds of the original mesh
	MeshPtr mesh = builder.getMesh();
	MeshPtr refMesh = pEntity->getMesh();
	mesh->_setBounds(refMesh->getBounds());
	mesh->_setBoundingSphereRadius(refMesh->getBoundingSphereRadius());

	// Create an entity to display the skeleton representation
	m_pSkeletonEntity = getSceneManager()->createEntity(strBaseName + ".Skeleton", mesh->getName());
	m_pSkeletonEntity->shareSkeletonInstanceWith(pEntity);
	m_pSceneNode->attachObject(m_pSkeletonEntity);
}

//-----------------------------------------------------------------------

void Skeleton::hide()
{
	if (m_pSkeletonEntity)
	{
		string strMeshName = m_pSkeletonEntity->getMesh()->getName();

		m_pSceneNode->detachObject(m_pSkeletonEntity);
		getSceneManager()->destroyEntity(m_pSkeletonEntity);
		m_pSkeletonEntity = 0;

		MeshManager::getSingleton().remove(strMeshName);

		m_pSkeletonEntity = 0;
	}
}

//-----------------------------------------------------------------------

void Skeleton::setSkeletonSource(Visual::Object* pPart)
{
	bool bShown = false;

	if (m_pSkeletonEntity)
	{
		hide();
		bShown = true;
	}

	m_pSkeletonSource = pPart;

	if (bShown && m_pSkeletonSource)
		show();
}

//-----------------------------------------------------------------------

void Skeleton::selectBone(const std::string& strBone)
{
	try
	{
		if (m_pSkeletonEntity)
		{
			SubEntity* pSubEntity = m_pSkeletonEntity->getSubEntity(strBone);
			if (pSubEntity)
				pSubEntity->setMaterialName(m_strSelectedBoneMaterial);
		}
	}
	catch (Ogre::Exception ex)
	{
		ATHENA_LOG_ERROR("Failed to select the bone '" + strBone + "', reason: " + ex.getFullDescription());
	}
}

//-----------------------------------------------------------------------

void Skeleton::deselectBone(const std::string& strBone)
{
	try
	{
		if (m_pSkeletonEntity)
		{
			SubEntity* pSubEntity = m_pSkeletonEntity->getSubEntity(strBone);
			if (pSubEntity)
				pSubEntity->setMaterialName(m_strBoneMaterial);
		}
	}
	catch (Ogre::Exception ex)
	{
		ATHENA_LOG_ERROR("Failed to deselect the bone '" + strBone + "', reason: " + ex.getFullDescription());
	}
}

//-----------------------------------------------------------------------

void Skeleton::deselectAllBones()
{
	if (m_pSkeletonEntity)
	{
		for (unsigned int i = 0; i < m_pSkeletonEntity->getNumSubEntities(); ++i)
		{
			SubEntity* pSubEntity = m_pSkeletonEntity->getSubEntity(i);
			pSubEntity->setMaterialName(m_strBoneMaterial);
		}
	}
}

//-----------------------------------------------------------------------

void Skeleton::_addFace(const Math::Vector3& point1, const Math::Vector3& point2,
						const Math::Vector3& point3, Ogre::Bone* pBone,
						Graphics::MeshBuilder* pBuilder)
{
	unsigned short usNbVertices = pBuilder->getNbVertices();
		
	Vector3 normal = (point2 - point1).crossProduct(point3 - point1);

	pBuilder->position(point1);
	pBuilder->blendingIndices(pBone->getHandle());
	pBuilder->normal(normal);

	pBuilder->position(point2);
	pBuilder->blendingIndices(pBone->getHandle());
	pBuilder->normal(normal);

	pBuilder->position(point3);
	pBuilder->blendingIndices(pBone->getHandle());
	pBuilder->normal(normal);

	pBuilder->triangle(usNbVertices, usNbVertices + 1, usNbVertices + 2);
}


/**************************** REFERERS / REFEREES MANAGEMENT ***************************/

void Skeleton::onComponentDestroyed(Component* pReferee)
{
    // Assertions
    assert(pReferee);

    if (m_pSkeletonSource == pReferee)
        hide();

    DebugComponent::onComponentDestroyed(pReferee);
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Skeleton::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = DebugComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Skeleton source
	if (m_pSkeletonSource)
		pProperties->set("skeletonSource", new Variant(m_pSkeletonSource->getID().toString()));
	else
		pProperties->set("skeletonSource", new Variant(tComponentID(COMP_NONE).toString()));

	// Bone material
	pProperties->set("boneMaterial", new Variant(m_strBoneMaterial));

	// Selected bone material
	pProperties->set("selectedBoneMaterial", new Variant(m_strSelectedBoneMaterial));

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool Skeleton::setProperty(const std::string& strCategory, const std::string& strName,
						   Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return Skeleton::setProperty(strName, pValue);

    return DebugComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Skeleton::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Skeleton source
	if (strName == "skeletonSource")
	{
		tComponentID id(pValue->toString());
		setSkeletonSource(Object::cast(m_pList->getComponent(id)));
	}

	// Bone material
	else if (strName == "boneMaterial")
		setBoneMaterial(pValue->toString());
	
	// Selected bone material
	else if (strName == "selectedBoneMaterial")
		setSelectedBoneMaterial(pValue->toString());

	// Destroy the value
	delete pValue;

	return true;
}
