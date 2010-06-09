/**	@file	Spotlight.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::Spotlight'
*/

#include <Athena-Graphics/Visual/Spotlight.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Core/Log/LogManager.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Athena::Math;
using namespace Athena::Log;
using namespace std;

using Ogre::Light;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__			= "Visual/Spotlight";

///< Name of the type of entity
const std::string	Spotlight::TYPE	= "Athena/Visual/Spotlight";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Spotlight::Spotlight(const std::string& strName, ComponentsList* pList)
: PointLight(strName, pList)
{
	assert(pSceneManager && "There isn't an Scene manager's instance");
	assert(m_pSceneNode);
	assert(m_pLight);

	m_pLight->setType(Light::LT_SPOTLIGHT);
}

//-----------------------------------------------------------------------

Spotlight::~Spotlight()
{
}

//-----------------------------------------------------------------------

Spotlight* Spotlight::create(const std::string& strName, ComponentsList* pList)
{
	return new Spotlight(strName, pList);
}

//-----------------------------------------------------------------------

Spotlight* Spotlight::cast(Component* pComponent)
{
	return dynamic_cast<Spotlight*>(pComponent);
}


/****************************** MANAGEMENT OF THE LIGHT ********************************/

void Spotlight::setRange(const Math::Radian &innerAngle, const Math::Radian &outerAngle,
						 Math::Real falloff)
{
	assert(m_pLight);

	m_pLight->setSpotlightRange(toOgre(innerAngle), toOgre(outerAngle), falloff);
}

//-----------------------------------------------------------------------

const Radian Spotlight::getInnerAngle() const
{
	assert(m_pLight);

	return fromOgre(m_pLight->getSpotlightInnerAngle());
}

//-----------------------------------------------------------------------

const Radian Spotlight::getOuterAngle() const
{
	assert(m_pLight);

	return fromOgre(m_pLight->getSpotlightOuterAngle());
}

//-----------------------------------------------------------------------

Real Spotlight::getFalloff() const
{
	assert(m_pLight);

	return m_pLight->getSpotlightFalloff();
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Spotlight::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = PointLight::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Inner angle
	pProperties->set("innerAngle", new Variant(getInnerAngle()));

	// Outer angle
	pProperties->set("outerAngle", new Variant(getOuterAngle()));

	// Falloff
	pProperties->set("falloff", new Variant(getFalloff()));

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool Spotlight::setProperty(const std::string& strCategory, const std::string& strName,
							Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return Spotlight::setProperty(strName, pValue);

	return PointLight::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Spotlight::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Inner angle
	if (strName == "innerAngle")
		setRange(pValue->toRadian(), getOuterAngle(), getFalloff());

	// Outer angle
	else if (strName == "outerAngle")
		setRange(getInnerAngle(), pValue->toRadian(), getFalloff());

	// Falloff
	else if (strName == "falloff")
		setRange(getInnerAngle(), getOuterAngle(), pValue->toFloat());

	// Destroy the value
	delete pValue;

	return true;
}
