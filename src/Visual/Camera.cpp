/**	@file	Camera.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::Visual::Camera'
*/

#include <Athena-Graphics/Visual/Camera.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreCamera.h>
#include <Ogre/OgreSceneManager.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::Exception;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__		= "Visual/Camera";

///< Name of the type of entity
const std::string	Camera::TYPE	= "Athena/Visual/Camera";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Camera::Camera(const std::string& strName, ComponentsList* pList)
: EntityComponent(strName, pList), m_pCamera(0)
{
	assert(getSceneManager() && "There isn't an Scene manager's instance");
	assert(m_pSceneNode);
	assert(pList->getEntity());

	try
	{
		// Create the camera
		m_pCamera = getSceneManager()->createCamera(m_id.strEntity + ".Visual[" + m_id.strName + "].Camera");

		// Attach it to the scene node
		m_pSceneNode->attachObject(m_pCamera);

		// Set the userDefinedData of the camera
		m_pCamera->MovableObject::setUserAny(Ogre::Any(m_pList->getEntity()));
	}
	catch (Ogre::Exception& exception)
	{
		// Destroy the camera
		if (m_pCamera)
		{
			getSceneManager()->destroyCamera(m_pCamera);
			m_pCamera = 0;
		}

		ATHENA_LOG_ERROR("Failed to create the camera '" + m_id.strName + "', exception: " +
						 exception.getFullDescription());

		throw;
	}
}

//-----------------------------------------------------------------------

Camera::~Camera()
{
	assert(getSceneManager());
	assert(m_pSceneNode);

	if (m_pCamera)
	{
		assert(m_pCamera->getParentNode() == m_pSceneNode);

		m_pSceneNode->detachObject(m_pCamera);
		getSceneManager()->destroyCamera(m_pCamera);
	}
}

//-----------------------------------------------------------------------

Camera* Camera::create(const std::string& strName, ComponentsList* pList)
{
	return new Camera(strName, pList);
}

//-----------------------------------------------------------------------

Camera* Camera::cast(Component* pComponent)
{
	return dynamic_cast<Camera*>(pComponent);
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Camera::getProperties() const
{
	// Call the base class implementation
	PropertiesList* pProperties = EntityComponent::getProperties();

	// Create the category belonging to this type
	pProperties->selectCategory(TYPE, false);

	if (m_pCamera)
	{
		// Projection type
		string str;
		switch (getProjectionType())
		{
			case Ogre::PT_PERSPECTIVE:	str = "Perspective"; break;
			case Ogre::PT_ORTHOGRAPHIC:	str = "Orthographic"; break;
		}
		pProperties->set("projectiontype", new Variant(str));

		// Polygon mode
		switch (getPolygonMode())
		{
			case Ogre::PM_SOLID:		str = "Solid"; break;
			case Ogre::PM_POINTS:		str = "Points"; break;
			case Ogre::PM_WIREFRAME:	str = "Wireframe"; break;
		}
		pProperties->set("polygonmode", new Variant(str));

		// LOD bias
		pProperties->set("lodbias", new Variant(getLodBias()));

		// Auto aspect ratio
		pProperties->set("autoaspectratio", new Variant(getAutoAspectRatio()));

		// Aspect ratio
		pProperties->set("aspectratio", new Variant(getAspectRatio()));

		// FOV y
		pProperties->set("fovy", new Variant(getFOVy()));

		// Near clip distance
		pProperties->set("nearclipdistance", new Variant(getNearClipDistance()));

		// Far clip distance
		pProperties->set("farclipdistance", new Variant(getFarClipDistance()));
	}

	// Returns the list
	return pProperties;
}

//-----------------------------------------------------------------------

bool Camera::setProperty(const std::string& strCategory, const std::string& strName,
						 Utils::Variant* pValue)
{
	assert(!strCategory.empty());
	assert(!strName.empty());
	assert(pValue);

	if (strCategory == TYPE)
		return Camera::setProperty(strName, pValue);

    return EntityComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Camera::setProperty(const std::string& strName, Utils::Variant* pValue)
{
	// Assertions
	assert(!strName.empty());
	assert(pValue);

	// Declarations
	bool bUsed = true;


	// Projection type
	if (strName == "projectiontype")
	{
		if (pValue->toString() == "Perspective")
			setProjectionType(Ogre::PT_PERSPECTIVE);
		else
			setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	}

	// Polygon mode
	else if (strName == "polygonmode")
	{
		if (pValue->toString() == "Solid")
			setPolygonMode(Ogre::PM_SOLID);
		else if (pValue->toString() == "Points")
			setPolygonMode(Ogre::PM_POINTS);
		else
			setPolygonMode(Ogre::PM_WIREFRAME);
	}

	// LOD bias
	else if (strName == "lodbias")
	{
		setLodBias(pValue->toFloat());
	}

	// Auto aspect ratio
	else if (strName == "autoaspectratio")
	{
		setAutoAspectRatio(pValue->toBool());
	}

	// Aspect ratio
	else if (strName == "aspectratio")
	{
		setAspectRatio(pValue->toFloat());
	}

	// FOV y
	else if (strName == "fovy")
	{
		setFOVy(pValue->toRadian());
	}

	// Near clip distance
	else if (strName == "nearclipdistance")
	{
		setNearClipDistance(pValue->toFloat());
	}

	// Far clip distance
	else if (strName == "farclipdistance")
	{
		setFarClipDistance(pValue->toFloat());
	}

	else
	{
		bUsed = false;
	}

	// Destroy the value
	delete pValue;

	return bUsed;
}
