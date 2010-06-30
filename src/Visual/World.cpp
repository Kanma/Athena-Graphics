/**	@file	World.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::World'
*/

#include <Athena-Graphics/Visual/World.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Entities/Scene.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreRoot.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Athena::Math;
using namespace Athena::Log;
using namespace std;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*  __CONTEXT__	        = "Visual/World";

/// Default name for the world components
const std::string World::DEFAULT_NAME   = "VisualWorld";

/// Name of the type of component
const std::string   World::TYPE         = "Athena/Visual/World";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

World::World(const std::string& strName, ComponentsList* pList)
: VisualComponent(DEFAULT_NAME, pList), m_pSceneManager(0)
{
	// Assertions
	assert(m_pList);
	assert(m_pList->getScene());
    assert(!m_pList->getEntity());

	m_id.type = COMP_VISUAL;
	
    m_pList->getScene()->_setMainComponent(this);
}

//-----------------------------------------------------------------------

World::~World()
{
	// Assertions
	assert(m_pList);
	assert(m_pList->getScene());

    Ogre::Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);

    m_pList->getScene()->_resetMainComponent(COMP_VISUAL);
}

//-----------------------------------------------------------------------

World* World::create(const std::string& strName, ComponentsList* pList)
{
	return new World(strName, pList);
}

//-----------------------------------------------------------------------

World* World::cast(Component* pComponent)
{
	return dynamic_cast<World*>(pComponent);
}


/*************************************** METHODS ***************************************/

Ogre::SceneManager* World::createSceneManager(const std::string& typeName)
{
    // Assertions
    assert(!m_pSceneManager);
    assert(!typeName.empty());
    assert(Ogre::Root::getSingletonPtr());

    try
    {
        m_pSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(typeName, m_id.strName);
    }
    catch (Ogre::Exception ex)
    {
        ATHENA_LOG_ERROR("Failed to create a scene manager of type '" + typeName + "', reason: " + ex.getFullDescription());
    }

    return m_pSceneManager;
}

//-----------------------------------------------------------------------

Ogre::SceneManager* World::createSceneManager(Ogre::SceneTypeMask typeMask)
{
    // Assertions
    assert(!m_pSceneManager);
    assert(Ogre::Root::getSingletonPtr());

    m_pSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(typeMask, m_id.strName);
    return m_pSceneManager;
}

//-----------------------------------------------------------------------

void  World::setAmbientLight(const Math::Color& color) const
{
    if (m_pSceneManager)
        m_pSceneManager->setAmbientLight(toOgre(color));
}

//-----------------------------------------------------------------------

const Math::Color World::getAmbientLight() const
{
    if (m_pSceneManager)
        return fromOgre(m_pSceneManager->getAmbientLight());

    return Color::Black;
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* World::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = VisualComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

    if (m_pSceneManager)
    {
        // Scene Manager type
	    pProperties->set("scenemanager", new Variant(m_pSceneManager->getTypeName()));

	    // Ambient light
	    pProperties->set("ambientlight", new Variant(getAmbientLight()));
    }	

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool World::setProperty(const std::string& strCategory, const std::string& strName,
							      Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return World::setProperty(strName, pValue);

	return VisualComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool World::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

    // Declarations
    bool bUsed = true;

    // Scene Manager type
	if (strName == "scenemanager")
	{
		if (!m_pSceneManager)
			createSceneManager(pValue->toString());
		else
            bUsed = false;
	}

    // Ambient light
	else if (strName == "ambientlight")
	{
		if (m_pSceneManager)
			setAmbientLight(pValue->toColor());
		else
            bUsed = false;
	}
	
	else
	{
        bUsed = false;
	}

	// Destroy the value
	delete pValue;

	return bUsed;
}
