/**	@file	VisualComponent.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::VisualComponent'
*/

#include <Athena-Graphics/Visual/VisualComponent.h>
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
const std::string VisualComponent::TYPE = "Athena/Visual/VisualComponent";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

VisualComponent::VisualComponent(const std::string& strName, ComponentsList* pList)
: Component(strName, pList), m_bVisible(true), m_bCastShadows(false), m_pSceneNode(0)
{
	// Assertions
	assert(pSceneManager);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());
	assert(m_pList->getEntity()->getTransforms());

	m_id.type = COMP_VISUAL;

	// Create a scene node
	m_pSceneNode = pSceneManager->createSceneNode();

	// Signals handling
	m_signals.connect(SIGNAL_COMPONENT_TRANSFORMS_ORIGIN_CHANGED, this, &VisualComponent::onTransformsOriginChanged);

	// Register to the 'Scene shown' and 'Scene hidden' signals
	SignalsList* pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->connect(SIGNAL_SCENE_SHOWN, this, &VisualComponent::onSceneShown);
	pSignals->connect(SIGNAL_SCENE_HIDDEN, this, &VisualComponent::onSceneHidden);

	// Register to the 'Entity enabled' and 'Entity disabled' signals
	pSignals = m_pList->getEntity()->getSignalsList();
	pSignals->connect(SIGNAL_ENTITY_ENABLED, this, &VisualComponent::onEntityEnabled);
	pSignals->connect(SIGNAL_ENTITY_DISABLED, this, &VisualComponent::onEntityDisabled);

	// Use the transforms of the entity as our origin by default
	setTransformsOrigin(m_pList->getEntity()->getTransforms());

	// If the scene is already shown, simulates a signal event
	if (m_pList->getEntity()->getScene()->isShown())
		onSceneShown(0);
}

//-----------------------------------------------------------------------

VisualComponent::~VisualComponent()
{
	// Assertions
	assert(pSceneManager);
	assert(m_pSceneNode);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());

	setTransformsOrigin(0);

	// Unregister from the 'Entity attached' and 'Entity detached' signals
	SignalsList* pSignals = m_pList->getEntity()->getSignalsList();
	pSignals->disconnect(SIGNAL_ENTITY_ENABLED, this, &VisualComponent::onEntityEnabled);
	pSignals->disconnect(SIGNAL_ENTITY_DISABLED, this, &VisualComponent::onEntityDisabled);

	// Unregister from the 'Scene shown' and 'Scene hidden' signals
	pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->disconnect(SIGNAL_SCENE_SHOWN, this, &VisualComponent::onSceneShown);
	pSignals->disconnect(SIGNAL_SCENE_HIDDEN, this, &VisualComponent::onSceneHidden);

	// Signals handling
	m_signals.disconnect(SIGNAL_COMPONENT_TRANSFORMS_ORIGIN_CHANGED, this, &VisualComponent::onTransformsOriginChanged);

	// Destroy the scene node
	pSceneManager->destroySceneNode(m_pSceneNode->getName());
}

//-----------------------------------------------------------------------

VisualComponent* VisualComponent::create(const std::string& strName, ComponentsList* pList)
{
	return new VisualComponent(strName, pList);
}

//-----------------------------------------------------------------------

VisualComponent* VisualComponent::cast(Component* pComponent)
{
	return dynamic_cast<VisualComponent*>(pComponent);
}


/*************************************** METHODS ***************************************/

void VisualComponent::setCastShadows(bool bCastShadows)
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

void VisualComponent::attachObject(Ogre::MovableObject* pObject)
{
	// Assertions
	assert(m_pSceneNode);
	assert(pObject);

	m_pSceneNode->attachObject(pObject);

	pObject->setCastShadows(m_bCastShadows);
	pObject->setVisible(m_bVisible);
}


/**************************************** SLOTS ****************************************/

void VisualComponent::onTransformsOriginChanged(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pList);
	assert(pValue);

	// Unregister to the signals of the previous origin
	if (m_pTransformsOrigin)
	{
		SignalsList* pSignals = m_pTransformsOrigin->getSignalsList();
		pSignals->disconnect(SIGNAL_COMPONENT_TRANSFORMS_CHANGED, this, &VisualComponent::onTransformsChanged);

		m_pSceneNode->setPosition(Vector3::ZERO);
		m_pSceneNode->setOrientation(Quaternion::IDENTITY);
		m_pSceneNode->setScale(Vector3::UNIT_SCALE);
	}

	Transforms* pTransforms = Transforms::cast(m_pList->getComponent(tComponentID(pValue->toString())));

	// Register to the signals of the new origin
	if (pTransforms)
	{
		SignalsList* pSignals = pTransforms->getSignalsList();
		pSignals->connect(SIGNAL_COMPONENT_TRANSFORMS_CHANGED, this, &VisualComponent::onTransformsChanged);
	}
}

//-----------------------------------------------------------------------

void VisualComponent::onTransformsChanged(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);

	if (m_pTransformsOrigin)
	{
		m_pSceneNode->setPosition(toOgre(m_pTransformsOrigin->getWorldPosition()));
		m_pSceneNode->setOrientation(toOgre(m_pTransformsOrigin->getWorldOrientation()));
		m_pSceneNode->setScale(toOgre(m_pTransformsOrigin->getWorldScale()));
	}
	else
	{
		m_pSceneNode->setPosition(Ogre::Vector3::ZERO);
		m_pSceneNode->setOrientation(Ogre::Quaternion::IDENTITY);
		m_pSceneNode->setScale(Ogre::Vector3::UNIT_SCALE);
	}
}

//-----------------------------------------------------------------------

void VisualComponent::onSceneShown(Utils::Variant* pValue)
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

void VisualComponent::onSceneHidden(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getScene());
	assert(!m_pList->getEntity()->getScene()->isShown());

	if (m_pList->getEntity()->isEnabled())
		pSceneManager->getRootSceneNode()->removeChild(m_pSceneNode);
}

//-----------------------------------------------------------------------

void VisualComponent::onEntityEnabled(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(!m_pSceneNode->getParent());
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->isEnabled());

	pSceneManager->getRootSceneNode()->addChild(m_pSceneNode);
}

//-----------------------------------------------------------------------

void VisualComponent::onEntityDisabled(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pSceneNode->getParent());
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(!m_pList->getEntity()->isEnabled());

	pSceneManager->getRootSceneNode()->removeChild(m_pSceneNode);
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* VisualComponent::getProperties() const
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

bool VisualComponent::setProperty(const std::string& strCategory, const std::string& strName,
							      Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return VisualComponent::setProperty(strName, pValue);

	return Component::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool VisualComponent::setProperty(const std::string& strName, Utils::Variant* pValue)
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
