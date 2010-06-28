/**	@file	VisualComponent.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::VisualComponent'
*/

#include <Athena-Graphics/Visual/VisualComponent.h>
#include <Athena-Graphics/Visual/World.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Entities/Scene.h>
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
: Component(strName, pList)
{
	// Assertions
	assert(m_pList);
	assert(m_pList->getScene() || m_pList->getEntity());

	m_id.type = COMP_VISUAL;
}

//-----------------------------------------------------------------------

VisualComponent::~VisualComponent()
{
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

World* VisualComponent::getWorld() const
{
    if (m_pList->getScene())
        return dynamic_cast<World*>(m_pList->getScene()->getMainComponent(Entities::COMP_VISUAL));
    else if (m_pList->getEntity())
        return dynamic_cast<World*>(m_pList->getEntity()->getScene()->getMainComponent(Entities::COMP_VISUAL));

    return 0;
}

//-----------------------------------------------------------------------

Ogre::SceneManager* VisualComponent::getSceneManager() const
{
    World* pWorld = getWorld();
    if (pWorld)
        return pWorld->getSceneManager();
    
    return 0;
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* VisualComponent::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = Component::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

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

	// Destroy the value
	delete pValue;

	return true;
}
