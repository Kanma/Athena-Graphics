/**	@file	DebugComponent.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Debug::DebugComponent'
*/

#include <Athena-Graphics/Debug/DebugComponent.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Entities/Transforms.h>
#include <Athena-Entities/Scene.h>
#include <Athena-Entities/Signals.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Ogre;
using namespace std;


/************************************** CONSTANTS **************************************/

///< Name of the type of component
const std::string DebugComponent::TYPE = "Athena/Debug/DebugComponent";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

DebugComponent::DebugComponent(const std::string& strName, ComponentsList* pList)
: Component(strName, pList), m_pSceneNode(0)
{
	// Assertions
	assert(pSceneManager);
	assert(m_pList);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());
	assert(m_pList->getEntity()->getTransforms());

	m_id.type = COMP_DEBUG;

	// Create a scene node
	m_pSceneNode = pSceneManager->createSceneNode();

	// Signals handling
	m_signals.connect(SIGNAL_COMPONENT_TRANSFORMS_ORIGIN_CHANGED, this, &DebugComponent::onTransformsOriginChanged);

	// Register to the 'Scene shown' and 'Scene hidden' signals
	SignalsList* pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->connect(SIGNAL_SCENE_SHOWN, this, &DebugComponent::onSceneShown);
	pSignals->connect(SIGNAL_SCENE_HIDDEN, this, &DebugComponent::onSceneHidden);

	// Register to the 'Entity enabled' and 'Entity disabled' signals
	pSignals = m_pList->getEntity()->getSignalsList();
	pSignals->connect(SIGNAL_ENTITY_ENABLED, this, &DebugComponent::onEntityEnabled);
	pSignals->connect(SIGNAL_ENTITY_DISABLED, this, &DebugComponent::onEntityDisabled);

	// Use the transforms of the entity as our origin by default
	setTransformsOrigin(m_pList->getEntity()->getTransforms());

	// If the scene is already shown, simulates a signal event
	if (m_pList->getEntity()->getScene()->isShown())
		onSceneShown(0);
}

//-----------------------------------------------------------------------

DebugComponent::~DebugComponent()
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
	pSignals->disconnect(SIGNAL_ENTITY_ENABLED, this, &DebugComponent::onEntityEnabled);
	pSignals->disconnect(SIGNAL_ENTITY_DISABLED, this, &DebugComponent::onEntityDisabled);

	// Unregister from the 'Scene shown' and 'Scene hidden' signals
	pSignals = m_pList->getEntity()->getScene()->getSignalsList();
	pSignals->disconnect(SIGNAL_SCENE_SHOWN, this, &DebugComponent::onSceneShown);
	pSignals->disconnect(SIGNAL_SCENE_HIDDEN, this, &DebugComponent::onSceneHidden);

	// Signals handling
	m_signals.disconnect(SIGNAL_COMPONENT_TRANSFORMS_ORIGIN_CHANGED, this, &DebugComponent::onTransformsOriginChanged);

	// Destroy the scene node
	pSceneManager->destroySceneNode(m_pSceneNode->getName());
}

//-----------------------------------------------------------------------

DebugComponent* DebugComponent::create(const std::string& strName, ComponentsList* pList)
{
	return new DebugComponent(strName, pList);
}

//-----------------------------------------------------------------------

DebugComponent* DebugComponent::cast(Component* pComponent)
{
	return dynamic_cast<DebugComponent*>(pComponent);
}


/**************************************** SLOTS ****************************************/

void DebugComponent::onTransformsOriginChanged(Utils::Variant* pValue)
{
	// Assertions
	assert(m_pSceneNode);
	assert(m_pList);
	assert(pValue);

	// Unregister to the signals of the previous origin
	if (m_pTransformsOrigin)
	{
		SignalsList* pSignals = m_pTransformsOrigin->getSignalsList();
		pSignals->disconnect(SIGNAL_COMPONENT_TRANSFORMS_CHANGED, this, &DebugComponent::onTransformsChanged);

		m_pSceneNode->setPosition(Vector3::ZERO);
		m_pSceneNode->setOrientation(Quaternion::IDENTITY);
		m_pSceneNode->setScale(Vector3::UNIT_SCALE);
	}

	Transforms* pTransforms = Transforms::cast(m_pList->getComponent(tComponentID(pValue->toString())));

	// Register to the signals of the new origin
	if (pTransforms)
	{
		SignalsList* pSignals = pTransforms->getSignalsList();
		pSignals->connect(SIGNAL_COMPONENT_TRANSFORMS_CHANGED, this, &DebugComponent::onTransformsChanged);
	}
}

//-----------------------------------------------------------------------

void DebugComponent::onTransformsChanged(Utils::Variant* pValue)
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
		m_pSceneNode->setPosition(Vector3::ZERO);
		m_pSceneNode->setOrientation(Quaternion::IDENTITY);
		m_pSceneNode->setScale(Vector3::UNIT_SCALE);
	}
}

//-----------------------------------------------------------------------

void DebugComponent::onSceneShown(Utils::Variant* pValue)
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

void DebugComponent::onSceneHidden(Utils::Variant* pValue)
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

void DebugComponent::onEntityEnabled(Utils::Variant* pValue)
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

void DebugComponent::onEntityDisabled(Utils::Variant* pValue)
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

Utils::PropertiesList* DebugComponent::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = Component::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Returns the list
	return pProperties;
}