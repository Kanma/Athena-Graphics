/**	@file	DirectionalLight.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::DirectionalLight'
*/

#include <Athena-Graphics/DirectionalLight.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreSceneManager.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::Light;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__				= "Visual/DirectionalLight";

///< Name of the type of entity
const std::string	DirectionalLight::TYPE	= "Athena/Visual/DirectionalLight";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

DirectionalLight::DirectionalLight(const std::string& strName, ComponentsList* pList)
: VisualComponent(strName, pList), m_pLight(0)
{
	assert(pLogManager && "There isn't an Log manager's instance");
	assert(pSceneManager && "There isn't an Scene manager's instance");
	assert(m_pSceneNode);
	assert(m_pList->getEntity());
	assert(m_pList->getEntity()->getSignalsList());

	try
	{
		// Create the light
		m_pLight = pSceneManager->createLight(m_id.strEntity + ".Visual[" + m_id.strName + "].Light");
		m_pLight->setType(Light::LT_DIRECTIONAL);

		// Attach it to the scene node
		m_pSceneNode->attachObject(m_pLight);

		// Set the userAny of the light
		m_pLight->setUserAny(Ogre::Any(m_pList->getEntity()));
	}
	catch (Ogre::Exception& exception)
	{
		// Destroy the light
		if (m_pLight)
		{
			pSceneManager->destroyLight(m_pLight);
			m_pLight = 0;
		}

		ATHENA_LOG_ERROR("Failed to create the directional light '" + m_id.strName + "', exception: " +
						 exception.getFullDescription());

		throw;
	}
}

//-----------------------------------------------------------------------

DirectionalLight::~DirectionalLight()
{
	// Assertions
	assert(pSceneManager);
	assert(m_pSceneNode);

	if (m_pLight)
	{
		assert(m_pLight->getParentNode() == m_pSceneNode);

		m_pSceneNode->detachObject(m_pLight);
		pSceneManager->destroyLight(m_pLight);
		m_pLight = 0;
	}
}

//-----------------------------------------------------------------------

DirectionalLight* DirectionalLight::create(const std::string& strName, ComponentsList* pList)
{
	return new DirectionalLight(strName, pList);
}

//-----------------------------------------------------------------------

DirectionalLight* DirectionalLight::cast(Component* pComponent)
{
	return dynamic_cast<DirectionalLight*>(pComponent);
}


/****************************** MANAGEMENT OF THE LIGHT ********************************/

void DirectionalLight::setDiffuseColor(const Math::Color& color) const
{
	assert(m_pLight);

	m_pLight->setDiffuseColour(toOgre(color));
}
	
//-----------------------------------------------------------------------

const Math::Color DirectionalLight::getDiffuseColor() const
{
	assert(m_pLight);

	return fromOgre(m_pLight->getDiffuseColour());
}

//-----------------------------------------------------------------------

void DirectionalLight::setSpecularColor(const Math::Color& color) const
{
	assert(m_pLight);

	m_pLight->setSpecularColour(toOgre(color));
}

//-----------------------------------------------------------------------

const Math::Color DirectionalLight::getSpecularColor() const
{
	assert(m_pLight);

	return fromOgre(m_pLight->getSpecularColour());
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* DirectionalLight::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = VisualComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Diffuse colour
	pProperties->set("diffuse", new Variant(getDiffuseColor()));

	// Specular colour
	pProperties->set("specular", new Variant(getSpecularColor()));

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool DirectionalLight::setProperty(const std::string& strCategory, const std::string& strName,
									Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return DirectionalLight::setProperty(strName, pValue);

	return VisualComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool DirectionalLight::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Diffuse colour
	if (strName == "diffuse")
	{
		setDiffuseColor(pValue->toColor());
	}

	// Diffuse colour
	else if (strName == "specular")
	{
		setSpecularColor(pValue->toColor());
	}

	// Destroy the value
	delete pValue;

	return true;
}
