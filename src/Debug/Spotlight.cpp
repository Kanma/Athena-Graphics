/**	@file	Spotlight.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Grahics::Debug::Spotlight'
*/

#include <Athena-Graphics/Debug/Spotlight.h>
#include <Athena-Graphics/Visual/Spotlight.h>
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
static const char*	__CONTEXT__			= "Debug/Spotlight";

///< Name of the type of component
const std::string	Spotlight::TYPE	= "Athena/Debug/Spotlight";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Spotlight::Spotlight(const std::string& strName, ComponentsList* pList)
: DebugComponent(strName, pList), m_pSpotlightSource(0)
{
}

//-----------------------------------------------------------------------

Spotlight::~Spotlight()
{
	hide();
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


/*************************************** METHODS ***************************************/

void Spotlight::setSpotlightSource(Visual::Spotlight* pPart)
{
	bool bShown = false;

	if (!m_lines.empty())
	{
		hide();
		bShown = true;
	}

    if (m_pSpotlightSource)
    {
        removeLinkTo(m_pSpotlightSource);
        m_pSpotlightSource = 0;
    }

	m_pSpotlightSource = pPart;

    if (m_pSpotlightSource)
	{
        addLinkTo(m_pSpotlightSource);

        if (bShown)
    		show();
	}
}

//-----------------------------------------------------------------------

void Spotlight::show()
{
    // Declarations
	const Real	cos30	= MathUtils::Cos(Degree(30));
	const Real	cos60	= MathUtils::Cos(Degree(60));
	const Real	sin30	= MathUtils::Sin(Degree(30));
	const Real	sin60	= MathUtils::Sin(Degree(60));
	Line3D*	    pLine;
	Real		range;
	Radian		outerAngle;
	Real		coneOffset;

	if (m_lines.empty())
	{
		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.5f, -0.25f, 0));
		pLine->addPoint(Vector3(0.25f, -0.5f, 0));
		pLine->addPoint(Vector3(-0.25f, -0.5f, 0));
		pLine->addPoint(Vector3(-0.5f, -0.25f, 0));
		pLine->addPoint(Vector3(-0.5f, 0.25f, 0));
		pLine->addPoint(Vector3(-0.25f, 0.5f, 0));
		pLine->addPoint(Vector3(0.25f, 0.5f, 0));
		pLine->addPoint(Vector3(0.5f, 0.25f, 0));
		pLine->addPoint(Vector3(0.5f, -0.25f, 0));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.5f, -0.25f, -1));
		pLine->addPoint(Vector3(0.25f, -0.5f, -1));
		pLine->addPoint(Vector3(-0.25f, -0.5f, -1));
		pLine->addPoint(Vector3(-0.5f, -0.25f, -1));
		pLine->addPoint(Vector3(-0.5f, 0.25f, -1));
		pLine->addPoint(Vector3(-0.25f, 0.5f, -1));
		pLine->addPoint(Vector3(0.25f, 0.5f, -1));
		pLine->addPoint(Vector3(0.5f, 0.25f, -1));
		pLine->addPoint(Vector3(0.5f, -0.25f, -1));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.5f, -0.25f, -1));
		pLine->addPoint(Vector3(0.5f, -0.25f, 0));
		pLine->addPoint(Vector3(0.8f, -0.25f, 0.7f));
		pLine->addPoint(Vector3(0.8f, 0.25f, 0.7f));
		pLine->addPoint(Vector3(0.5f, 0.25f, 0));
		pLine->addPoint(Vector3(0.5f, 0.25f, -1));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(-0.5f, -0.25f, -1));
		pLine->addPoint(Vector3(-0.5f, -0.25f, 0));
		pLine->addPoint(Vector3(-0.8f, -0.25f, 0.7f));
		pLine->addPoint(Vector3(-0.8f, 0.25f, 0.7f));
		pLine->addPoint(Vector3(-0.5f, 0.25f, 0));
		pLine->addPoint(Vector3(-0.5f, 0.25f, -1));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.25f, 0.5f, -1));
		pLine->addPoint(Vector3(0.25f, 0.5f, 0));
		pLine->addPoint(Vector3(0.25f, 0.8f, 0.7f));
		pLine->addPoint(Vector3(-0.25f, 0.8f, 0.7f));
		pLine->addPoint(Vector3(-0.25f, 0.5f, 0));
		pLine->addPoint(Vector3(-0.25f, 0.5f, -1));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.25f, -0.5f, -1));
		pLine->addPoint(Vector3(0.25f, -0.5f, 0));
		pLine->addPoint(Vector3(0.25f, -0.8f, 0.7f));
		pLine->addPoint(Vector3(-0.25f, -0.8f, 0.7f));
		pLine->addPoint(Vector3(-0.25f, -0.5f, 0));
		pLine->addPoint(Vector3(-0.25f, -0.5f, -1));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0, 0, 0));
		pLine->addPoint(Vector3(0, 0, 2));
		pLine->addPoint(Vector3(0.3f * cos30, 0.3f * sin30, 1.4f));
		pLine->addPoint(Vector3(-0.3f * cos30, 0.3f * sin30, 1.4f));
		pLine->addPoint(Vector3(0, 0, 2));
		pLine->addPoint(Vector3(0, -0.3f, 1.4f));
		pLine->drawLines();
		m_lines.push_back(pLine);

		pLine = new Line3D(m_pSceneNode);
		pLine->addPoint(Vector3(0.3f * cos30, 0.3f * sin30, 1.4f));
		pLine->addPoint(Vector3(0, -0.3f, 1.4f));
		pLine->addPoint(Vector3(-0.3f * cos30, 0.3f * sin30, 1.4f));
		pLine->drawLines();
		m_lines.push_back(pLine);

		if (m_pSpotlightSource)
		{
			range = m_pSpotlightSource->getAttenuationRange();
			outerAngle = m_pSpotlightSource->getOuterAngle();
			coneOffset = range * MathUtils::Sin(outerAngle / 2.0f);

			pLine = new Line3D(m_pSceneNode);
			pLine->drawLine(Vector3(-0.375f, 0.375f, 0.0f), Vector3(-0.375f - coneOffset, 0.375f + coneOffset, range));
			m_lines.push_back(pLine);

			pLine = new Line3D(m_pSceneNode);
			pLine->drawLine(Vector3(-0.375f, -0.375f, 0.0f), Vector3(-0.375f - coneOffset, -0.375f - coneOffset, range));
			m_lines.push_back(pLine);

			pLine = new Line3D(m_pSceneNode);
			pLine->drawLine(Vector3(0.375f, -0.375f, 0.0f), Vector3(0.375f + coneOffset, -0.375f - coneOffset, range));
			m_lines.push_back(pLine);

			pLine = new Line3D(m_pSceneNode);
			pLine->drawLine(Vector3(0.375f, 0.375f, 0.0f), Vector3(0.375f + coneOffset, 0.375f + coneOffset, range));
			m_lines.push_back(pLine);
		}


		MaterialPtr material = MaterialManager::getSingleton().getByName("Materials/Colors/YellowNoLighting");
		if (!material.isNull())
		{
			std::vector<Graphics::Line3D*>::iterator iter, iterEnd;
			for (iter = m_lines.begin(), iterEnd = m_lines.end(); iter != iterEnd; ++iter)
				(*iter)->setMaterial(material->getName());
		}
	}
}

//-----------------------------------------------------------------------

void Spotlight::hide()
{
	if (!m_lines.empty())
	{
		while (!m_lines.empty())
		{
			m_pSceneNode->detachObject(m_lines.front());
			delete m_lines.front();
			m_lines.erase(m_lines.begin());
		}
	}
}


/*********************************** LINKS MANAGEMENT **********************************/

void Spotlight::mustUnlinkComponent(Component* pComponent)
{
    // Assertions
    assert(pComponent);

    if (m_pSpotlightSource == pComponent)
    {
        hide();
        m_pSpotlightSource = 0;
    }

    DebugComponent::mustUnlinkComponent(pComponent);
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Spotlight::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = DebugComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	// Spotlight source
	if (m_pSpotlightSource)
		pProperties->set("spotlightSource", new Variant(m_pSpotlightSource->getID().toString()));
	else
		pProperties->set("spotlightSource", new Variant(tComponentID(COMP_NONE).toString()));

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

    return DebugComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Spotlight::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Skeleton source
	if (strName == "spotlightSource")
	{
		tComponentID id(pValue->toString());
		setSpotlightSource(Visual::Spotlight::cast(m_pList->getComponent(id)));
	}

	// Destroy the value
	delete pValue;

	return true;
}
