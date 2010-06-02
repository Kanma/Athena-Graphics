/**	@file	Object.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Object'
*/

#include <Athena-Graphics/Object.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreSubEntity.h>
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::Entity;
using Ogre::Exception;
using Ogre::MeshManager;
using Ogre::MeshPtr;
using Ogre::SubEntity;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char* __CONTEXT__	= "Visual/Object";

///< Name of the type of component
const std::string Object::TYPE  = "Athena/Visual/Object";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Object::Object(const std::string& strName, ComponentsList* pList)
: VisualComponent(strName, pList), m_pEntity(0)
{
}

//-----------------------------------------------------------------------

Object::~Object()
{
	assert(pSceneManager);
	assert(m_pSceneNode);

	if (m_pEntity)
	{
		assert(m_pEntity->getParentNode() == m_pSceneNode);

		m_pSceneNode->detachObject(m_pEntity);
		pSceneManager->destroyEntity(m_pEntity);
		m_pEntity = 0;
	}
}

//-----------------------------------------------------------------------

Object* Object::create(const std::string& strName, ComponentsList* pList)
{
	return new Object(strName, pList);
}

//-----------------------------------------------------------------------

Object* Object::cast(Component* pComponent)
{
	return dynamic_cast<Object*>(pComponent);
}


/*************************************** METHODS ***************************************/

bool Object::loadMesh(const std::string& strMeshName, const std::string& strGroupName)
{
	// Assertions
	assert(!m_pEntity);
	assert(!strMeshName.empty());
	assert(pSceneManager);
	assert(pLogManager);
	assert(m_pSceneNode);

	try
	{
		// Retrieve the mesh
		MeshPtr mesh = MeshManager::getSingletonPtr()->getByName(strMeshName);
		if (mesh.isNull())
		{
			mesh = MeshManager::getSingletonPtr()->load(strMeshName, strGroupName);
			if (mesh.isNull())
			{
				ATHENA_LOG_ERROR("Failed to load the mesh '" + strMeshName + "' on the entity '" +
								 m_id.strName + "', reason: file not found");
				return false;
			}
		}

		// Create an Ogre entity and attach it to the scene node
		m_pEntity = pSceneManager->createEntity(m_id.strEntity + ".Visual[" + m_id.strName + "].Entity", strMeshName);
		attachObject(m_pEntity);
	}
	catch (Exception& ex)
	{
		ATHENA_LOG_ERROR("Failed to load the mesh '" + strMeshName + "' on the entity '" +
						 m_id.strName + "', reason: " + ex.getFullDescription());
		return false;
	}

	return true;
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Object::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = VisualComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	if (m_pEntity)
	{
		// Mesh
		pProperties->set("mesh", new Variant(m_pEntity->getMesh()->getName()));

		// Subentities
		for (unsigned int i = 0; i < m_pEntity->getNumSubEntities(); ++i)
		{
			SubEntity* pSubEntity = m_pEntity->getSubEntity(i);

			Variant* pStruct = new Variant(Variant::STRUCT);
			pStruct->setField("index", new Variant(i));
			pStruct->setField("material", new Variant(pSubEntity->getMaterialName()));
			pStruct->setField("visible", new Variant(pSubEntity->isVisible()));
			pProperties->set("subEntity", pStruct);
		}
	}

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool Object::setProperty(const std::string& strCategory, const std::string& strName,
						 Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return Object::setProperty(strName, pValue);

    return VisualComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Object::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Declarations
	bool bUsed = true;

	// Mesh
	if (strName == "mesh")
	{
		loadMesh(pValue->toString());
	}
	else if (m_pEntity)
	{
		// Sub-entities
		if (strName == "subEntity")
		{
			SubEntity* pSubEntity = m_pEntity->getSubEntity(pValue->getField("index")->toUInt());
			pSubEntity->setMaterialName(pValue->getField("material")->toString());
			pSubEntity->setVisible(pValue->getField("visible")->toBool());
		}
	}
	else
	{
		bUsed = false;
	}

	// Destroy the value
	delete pValue;

	return bUsed;
}
