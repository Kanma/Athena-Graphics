/**	@file	Axes.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Debug::Axes'
*/

#include <Athena-Graphics/Debug/Axes.h>
#include <Athena-Graphics/Line3D.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Math/MathUtils.h>
#include <Athena-Math/Vector3.h>
#include <Ogre/OgreMaterialManager.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Debug;
using namespace Athena::Math;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::MaterialPtr;
using Ogre::MaterialManager;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__	= "Debug/Axes";

///< Name of the type of entity
const std::string	Axes::TYPE	= "Athena/Debug/Axes";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Axes::Axes(const std::string& strName, Entities::ComponentsList* pList)
: DebugComponent(strName, pList), m_fScale(1.0f)
{
	memset(m_pAxes, 0, sizeof(m_pAxes));
}

//-----------------------------------------------------------------------

Axes::~Axes()
{
	hide();
}

//-----------------------------------------------------------------------

Axes* Axes::create(const std::string& strName, ComponentsList* pList)
{
	return new Axes(strName, pList);
}

//-----------------------------------------------------------------------

Axes* Axes::cast(Component* pComponent)
{
	return dynamic_cast<Axes*>(pComponent);
}


/*************************************** METHODS ***************************************/

void Axes::show()
{
	if (!m_pAxes[0])
	{
		m_pAxes[0] = new Line3D(m_pSceneNode);
		m_pAxes[0]->drawLine(Vector3(0, 0, 0), Vector3(m_fScale, 0, 0));

		MaterialPtr material = MaterialManager::getSingleton().getByName("Materials/Colors/RedNoLighting");
		if (!material.isNull())
			m_pAxes[0]->setMaterial(material->getName());

		m_pAxes[1] = new Line3D(m_pSceneNode);
		m_pAxes[1]->drawLine(Vector3(0, 0, 0), Vector3(0, m_fScale, 0));

		material = MaterialManager::getSingleton().getByName("Materials/Colors/GreenNoLighting");
		if (!material.isNull())
			m_pAxes[1]->setMaterial(material->getName());

		m_pAxes[2] = new Line3D(m_pSceneNode);
		m_pAxes[2]->drawLine(Vector3(0, 0, 0), Vector3(0, 0, m_fScale));

		material = MaterialManager::getSingleton().getByName("Materials/Colors/BlueNoLighting");
		if (!material.isNull())
			m_pAxes[2]->setMaterial(material->getName());
	}
}

//-----------------------------------------------------------------------

void Axes::hide()
{
	if (m_pAxes[0])
	{
		m_pSceneNode->detachObject(m_pAxes[0]);
		m_pSceneNode->detachObject(m_pAxes[1]);
		m_pSceneNode->detachObject(m_pAxes[2]);
		
		delete m_pAxes[0];
		delete m_pAxes[1];
		delete m_pAxes[2];

		memset(m_pAxes, 0, sizeof(Line3D*));
	}
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Axes::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = DebugComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Scale
	pProperties->set("scale", new Variant(m_fScale));

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool Axes::setProperty(const std::string& strCategory, const std::string& strName,
					   Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return Axes::setProperty(strName, pValue);

    return DebugComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Axes::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Scale
	if (strName == "scale")
	{
		setScale(pValue->toFloat());
	}

	// Destroy the value
	delete pValue;

	return true;
}
