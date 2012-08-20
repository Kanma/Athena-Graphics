/** @file   Plane.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::Visual::Plane'
*/

#include <Athena-Graphics/Visual/Plane.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreSubEntity.h>
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreSceneManager.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Athena::Math::Vector3;
using Ogre::Entity;
using Ogre::Exception;
using Ogre::MeshManager;
using Ogre::MeshPtr;
using Ogre::ResourceGroupManager;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*  __CONTEXT__ = "Visual/Plane";

///< Name of the type of entity
const std::string   Plane::TYPE = "Athena/Visual/Plane";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Plane::Plane(const std::string& strName, ComponentsList* pList)
: EntityComponent(strName, pList), m_pEntity(0), m_strMaterial(""),
  m_normalVector(Vector3::ZERO), m_distance(0.0f), m_width(0.0f), m_height(0.0f), m_xSegments(1),
  m_ySegments(1), m_bNormals(true), m_iNbTexCoordSet(1), m_uTile(1.0f), m_vTile(1.0f),
  m_upVector(Vector3::UNIT_Y)
{
}

//-----------------------------------------------------------------------

Plane::~Plane()
{
    assert(getSceneManager());
    assert(m_pSceneNode);

    if (m_pEntity)
    {
        assert(m_pEntity->getParentNode() == m_pSceneNode);

        m_pSceneNode->detachObject(m_pEntity);
        getSceneManager()->destroyEntity(m_pEntity);
        m_pEntity = 0;
        MeshManager::getSingleton().remove(m_id.strEntity + ".Visual[" + m_id.strName + "].Mesh");
    }
}

//-----------------------------------------------------------------------

Plane* Plane::create(const std::string& strName, ComponentsList* pList)
{
    return new Plane(strName, pList);
}

//-----------------------------------------------------------------------

Plane* Plane::cast(Component* pComponent)
{
    return dynamic_cast<Plane*>(pComponent);
}


/*************************************** METHODS ***************************************/

bool Plane::createPlane(const std::string& strMaterial, const Math::Vector3& normalVector,
                        Math::Real distance, Math::Real width, Math::Real height,
                        int xSegments, int ySegments, bool bNormals, int iNbTexCoordSet,
                        Math::Real uTile, Math::Real vTile, const Math::Vector3& upVector)
{
    // Assertions
    assert(getSceneManager());
    assert(m_pSceneNode);

    // Copy the parameters to the internal attributes
    m_strMaterial       = strMaterial;
    m_normalVector      = normalVector;
    m_distance          = distance;
    m_width             = width;
    m_height            = height;
    m_xSegments         = xSegments;
    m_ySegments         = ySegments;
    m_bNormals          = bNormals;
    m_iNbTexCoordSet    = iNbTexCoordSet;
    m_uTile             = uTile;
    m_vTile             = vTile;
    m_upVector          = upVector;

    // Create the plane
    return createPlane();
}

//-----------------------------------------------------------------------

bool Plane::createPlane()
{
    // Assertions
    assert(getSceneManager());
    assert(m_pSceneNode);

    try
    {
        // Destroy the previous plane (if any)
        if (m_pEntity)
        {
            m_pSceneNode->detachObject(m_pEntity);
            getSceneManager()->destroyEntity(m_pEntity);
            m_pEntity = 0;
            MeshManager::getSingleton().remove(m_id.strEntity + ".Visual[" + m_id.strName + "].Mesh");
        }

        // Check that we have enough informations about the plane
        if (m_strMaterial.empty() || m_normalVector.isZeroLength() || (m_distance < 0.0f) ||
            (m_width <= 0.0f) || (m_height <= 0.0f))
            return false;

        string strPrefix = m_id.strEntity + ".Visual[" + m_id.strName + "]";

        // Create the plane
        MeshPtr mesh = MeshManager::getSingleton().createPlane(strPrefix + ".Mesh",
                                                               ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                               Ogre::Plane(toOgre(m_normalVector), m_distance), m_width, m_height,
                                                               m_xSegments, m_ySegments, m_bNormals, m_iNbTexCoordSet,
                                                               m_uTile, m_vTile, toOgre(m_upVector));
        m_pEntity = getSceneManager()->createEntity(strPrefix + ".Entity", strPrefix + ".Mesh");

        m_pEntity->setCastShadows(false);
        m_pEntity->setMaterialName(m_strMaterial);

        attachObject(m_pEntity);
    }
    catch (Exception& ex)
    {
        ATHENA_LOG_ERROR("Failed to create a plane on the entity '" +
                         m_id.strName + "', reason: " + ex.getFullDescription());
        return false;
    }

    return true;
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Plane::getProperties() const
{
    // Call the base class implementation
    PropertiesList* pProperties = EntityComponent::getProperties();

    // Create the category belonging to this type
    pProperties->selectCategory(TYPE, false);

    // Material
    pProperties->set("material", new Variant(m_strMaterial));

    // Normal
    pProperties->set("normal", new Variant(m_normalVector));

    // Distance
    pProperties->set("distance", new Variant(m_distance));

    // Width
    pProperties->set("width", new Variant(m_width));

    // Height
    pProperties->set("height", new Variant(m_height));

    // xSegments
    pProperties->set("xSegments", new Variant(m_xSegments));

    // ySegments
    pProperties->set("ySegments", new Variant(m_ySegments));

    // Normals
    pProperties->set("normals", new Variant(m_bNormals));

    // NbTexCoordSet
    pProperties->set("nbTexCoordSet", new Variant(m_iNbTexCoordSet));

    // uTile
    pProperties->set("uTile", new Variant(m_uTile));

    // vTile
    pProperties->set("vTile", new Variant(m_vTile));

    // Up
    pProperties->set("up", new Variant(m_upVector));

    // Returns the list
    return pProperties;
}

//-----------------------------------------------------------------------

bool Plane::setProperty(const std::string& strCategory, const std::string& strName,
                        Utils::Variant* pValue)
{
    assert(!strCategory.empty());
    assert(!strName.empty());
    assert(pValue);

    if (strCategory == TYPE)
        return Plane::setProperty(strName, pValue);

    return EntityComponent::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool Plane::setProperty(const std::string& strName, Utils::Variant* pValue)
{
    // Assertions
    assert(!strName.empty());
    assert(pValue);

    // Declarations
    bool bUsed = true;

    // Mesh
    if (strName == "material")
    {
        m_strMaterial = pValue->toString();
    }

    // Normal
    else if (strName == "normal")
    {
        m_normalVector = pValue->toVector3();
    }

    // Distance
    else if (strName == "distance")
    {
        m_distance = pValue->toFloat();
    }

    // Width
    else if (strName == "width")
    {
        m_width = pValue->toFloat();
    }

    // Height
    else if (strName == "height")
    {
        m_height = pValue->toFloat();
    }

    // xSegments
    else if (strName == "xSegments")
    {
        m_xSegments = pValue->toInt();
    }

    // ySegments
    else if (strName == "ySegments")
    {
        m_ySegments = pValue->toInt();
    }

    // Normals
    else if (strName == "normals")
    {
        m_bNormals = pValue->toBool();
    }

    // NbTexCoordSet
    else if (strName == "nbTexCoordSet")
    {
        m_iNbTexCoordSet = pValue->toInt();
    }

    // uTile
    else if (strName == "uTile")
    {
        m_uTile = pValue->toFloat();
    }

    // vTile
    else if (strName == "vTile")
    {
        m_vTile = pValue->toFloat();
    }

    // Up
    else if (strName == "up")
    {
        m_upVector = pValue->toVector3();
    }

    else
    {
        bUsed = false;
    }

    // Recreate the plane
    createPlane();

    // Destroy the value
    delete pValue;

    return bUsed;
}
