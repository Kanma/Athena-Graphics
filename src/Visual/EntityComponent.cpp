/**	@file	EntityComponent.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::EntityComponent'
*/

#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Entities/Transforms.h>
#include <Athena-Entities/Scene.h>
#include <Athena-Entities/Signals.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Ogre;
using namespace std;


/************************************** CONSTANTS **************************************/

///< Name of the type of component
const std::string EntityComponent::TYPE = "Athena/Visual/EntityComponent";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

EntityComponent::EntityComponent(const std::string& strName, ComponentsList* pList)
: VisualComponent(strName, pList), m_bVisible(true), m_bCastShadows(false), m_pSceneNode(0)
{
	// Assertions
	assert(getSceneManager());
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());
	assert(m_pList->getEntity()->getTransforms());

	m_id.type = COMP_VISUAL;

	// Create a scene node
	m_pSceneNode = getSceneManager()->createSceneNode();

	// Use the transforms of the entity by default
	setTransforms(0);

	// Register to the 'Scene shown' and 'Scene hidden' signals
	SignalsList* pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->connect(SIGNAL_SCENE_SHOWN, this, &EntityComponent::onSceneShown);
	pSignals->connect(SIGNAL_SCENE_HIDDEN, this, &EntityComponent::onSceneHidden);

	// Register to the 'Entity enabled' and 'Entity disabled' signals
	pSignals = m_pList->getEntity()->getSignalsList();
	pSignals->connect(SIGNAL_ENTITY_ENABLED, this, &EntityComponent::onEntityEnabled);
	pSignals->connect(SIGNAL_ENTITY_DISABLED, this, &EntityComponent::onEntityDisabled);

	// If the scene is already shown, simulates a signal event
	if (m_pList->getEntity()->getScene()->isShown())
		onSceneShown(0);
}

//-----------------------------------------------------------------------

EntityComponent::~EntityComponent()
{
	// Assertions
	assert(getSceneManager());
	assert(m_pSceneNode);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());

	// Unregister from the 'Entity attached' and 'Entity detached' signals
	SignalsList* pSignals = m_pList->getEntity()->getSignalsList();
	pSignals->disconnect(SIGNAL_ENTITY_ENABLED, this, &EntityComponent::onEntityEnabled);
	pSignals->disconnect(SIGNAL_ENTITY_DISABLED, this, &EntityComponent::onEntityDisabled);

	// Unregister from the 'Scene shown' and 'Scene hidden' signals
	pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->disconnect(SIGNAL_SCENE_SHOWN, this, &EntityComponent::onSceneShown);
	pSignals->disconnect(SIGNAL_SCENE_HIDDEN, this, &EntityComponent::onSceneHidden);

	// Destroy the scene node
	getSceneManager()->destroySceneNode(m_pSceneNode->getName());
}

//-----------------------------------------------------------------------

EntityComponent* EntityComponent::create(const std::string& strName, ComponentsList* pList)
{
	return new EntityComponent(strName, pList);
}

//-----------------------------------------------------------------------

EntityComponent* EntityComponent::cast(Component* pComponent)
{
	return dynamic_cast<EntityComponent*>(pComponent);
}


/*************************************** METHODS ***************************************/

void EntityComponent::setCastShadows(bool bCastShadows)
{
	// Assertions
	assert(m_pSceneNode);

	if (bCastShadows == m_bCastShadows)
		return;

	m_bCastShadows = bCastShadows;

	SceneNode::ObjectIterator iter = m_pSceneNode->getAttachedObjectIterator();
	while (iter.hasMoreElements())
		iter.getNext()->setCastShadows(bCastShadows);
}

//-----------------------------------------------------------------------

void EntityComponent::attachObject(Ogre::MovableObject* pObject)
{
	// Assertions
	assert(m_pSceneNode);
	assert(pObject);

	m_pSceneNode->attachObject(pObject);

	pObject->setCastShadows(m_bCastShadows);
	pObject->setVisible(m_bVisible);
}

//-----------------------------------------------------------------------

void EntityComponent::onTransformsChanged()
{
	// Assertions
	assert(m_pSceneNode);

	if (getTransforms())
	{
		m_pSceneNode->setPosition(toOgre(getTransforms()->getWorldPosition()));
		m_pSceneNode->setOrientation(toOgre(getTransforms()->getWorldOrientation()));
		m_pSceneNode->setScale(toOgre(getTransforms()->getWorldScale()));
	}
	else
	{
		m_pSceneNode->setPosition(Ogre::Vector3::ZERO);
		m_pSceneNode->setOrientation(Ogre::Quaternion::IDENTITY);
		m_pSceneNode->setScale(Ogre::Vector3::UNIT_SCALE);
	}
}


/**************************************** SLOTS ****************************************/

void EntityComponent::onSceneShown(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getScene());
	assert(m_pList->getEntity()->getScene()->isShown());

	if (m_pList->getEntity()->isEnabled())
		onEntityEnabled(0);
}

//-----------------------------------------------------------------------

void EntityComponent::onSceneHidden(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getScene());
	assert(!m_pList->getEntity()->getScene()->isShown());

	if (m_pList->getEntity()->isEnabled())
		getSceneManager()->getRootSceneNode()->removeChild(m_pSceneNode);
}

//-----------------------------------------------------------------------

void EntityComponent::onEntityEnabled(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(!m_pSceneNode->getParent());
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->isEnabled());

	getSceneManager()->getRootSceneNode()->addChild(m_pSceneNode);
}

//-----------------------------------------------------------------------

void EntityComponent::onEntityDisabled(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pSceneNode->getParent());
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(!m_pList->getEntity()->isEnabled());

	getSceneManager()->getRootSceneNode()->removeChild(m_pSceneNode);
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* EntityComponent::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = Component::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Visibility
	pProperties->set("visible", new Variant(isVisible()));

	// Shadows casting
	pProperties->set("castShadows", new Variant(mustCastShadows()));

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool EntityComponent::setProperty(const std::string& strCategory, const std::string& strName,
							      Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return EntityComponent::setProperty(strName, pValue);

	return Component::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool EntityComponent::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Visibility
	if (strName == "visible")
	{
		if (m_bVisible != pValue->toBool())
			setVisible(!m_bVisible);
	}

	// Shadows casting
	else if (strName == "castShadows")
	{
		if (m_bCastShadows != pValue->toBool())
			setCastShadows(!m_bCastShadows);
	}

	// Destroy the value
	delete pValue;

	return true;
}
