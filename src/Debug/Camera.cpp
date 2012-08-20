/** @file   Camera.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::Debug::Camera'
*/

#include <Athena-Graphics/Debug/Camera.h>
#include <Athena-Graphics/MeshBuilder.h>
#include <Athena-Core/Log/LogManager.h>
#include <Ogre/OgreMaterialManager.h>
#include <Ogre/OgreSceneManager.h>
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreEntity.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Debug;
using namespace Athena::Math;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::MeshManager;
using Ogre::MeshPtr;
using Ogre::RenderOperation;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*  __CONTEXT__     = "Debug/Camera";

///< Name of the type of component
const std::string   Camera::TYPE    = "Athena/Debug/Camera";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Camera::Camera(const std::string& strName, ComponentsList* pList)
: DebugComponent(strName, pList), m_pEntity(0)
{
}

//-----------------------------------------------------------------------

Camera::~Camera()
{
    hide();
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


/*************************************** METHODS ***************************************/

void Camera::show()
{
    // Declarations
    const Real  cos30   = MathUtils::Cos(Degree(30));
    const Real  cos60   = MathUtils::Cos(Degree(60));
    const Real  sin30   = MathUtils::Sin(Degree(30));
    const Real  sin60   = MathUtils::Sin(Degree(60));

    if (!m_pEntity)
    {
        MeshPtr mesh = MeshManager::getSingletonPtr()->getByName("AthenaCamera.mesh");
        if (mesh.isNull())
        {
            MeshBuilder builder("AthenaCamera.mesh");

            builder.beginSharedVertices();

            // Box - Front part
            builder.position(Vector3(0.15f, 0.3f, 0.3f));       // 0
            builder.position(Vector3(-0.15f, 0.3f, 0.3f));
            builder.position(Vector3(-0.15f, -0.3f, 0.3f));
            builder.position(Vector3(0.15f, -0.3f, 0.3f));

            // Box - Back part
            builder.position(Vector3(0.15f, 0.3f, 1.0f));
            builder.position(Vector3(-0.15f, 0.3f, 1.0f));      // 5
            builder.position(Vector3(-0.15f, -0.3f, 1.0f));
            builder.position(Vector3(0.15f, -0.3f, 1.0f));

            // Objective - Part fixed on the box front part
            builder.position(Vector3(0.1f, 0.1f, 0.3f));
            builder.position(Vector3(-0.1f, 0.1f, 0.3f));
            builder.position(Vector3(-0.1f, -0.1f, 0.3f));      // 10
            builder.position(Vector3(0.1f, -0.1f, 0.3f));

            // Objective - Middle part
            builder.position(Vector3(0.1f, 0.1f, 0.15f));
            builder.position(Vector3(-0.1f, 0.1f, 0.15f));
            builder.position(Vector3(-0.1f, -0.1f, 0.15f));
            builder.position(Vector3(0.1f, -0.1f, 0.15f));      // 15

            // Objective - Biggest part
            builder.position(Vector3(0.1f, 0.25f, 0.0f));
            builder.position(Vector3(-0.1f, 0.25f, 0.0f));
            builder.position(Vector3(-0.1f, -0.25f, 0.0f));
            builder.position(Vector3(0.1f, -0.25f, 0.0f));      // 19

            builder.endSharedVertices();

            builder.begin("Solid", "Materials/DebugObject/Solid", RenderOperation::OT_TRIANGLE_LIST, true);

            builder.quad(3, 2, 1, 0);
            builder.quad(4, 5, 6, 7);

            builder.quad(0, 4, 7, 3);
            builder.quad(0, 1, 5, 4);
            builder.quad(1, 2, 6, 5);
            builder.quad(2, 3, 7, 6);

            builder.quad(12, 8, 11, 15);
            builder.quad(12, 13, 9, 8);
            builder.quad(13, 14, 10, 9);
            builder.quad(14, 15, 11, 10);

            builder.quad(16, 12, 15, 19);
            builder.quad(16, 17, 13, 12);
            builder.quad(17, 18, 14, 13);
            builder.quad(18, 19, 15, 14);

            builder.quad(19, 18, 17, 16);

            builder.end();

            builder.begin("Wireframe", "Materials/DebugObject/Wireframe", RenderOperation::OT_LINE_LIST, true);

            builder.line(0, 1);
            builder.line(1, 2);
            builder.line(2, 3);
            builder.line(3, 0);

            builder.line(4, 5);
            builder.line(5, 6);
            builder.line(6, 7);
            builder.line(7, 4);

            builder.line(0, 4);
            builder.line(1, 5);
            builder.line(2, 6);
            builder.line(3, 7);

            builder.line(8, 9);
            builder.line(9, 10);
            builder.line(10, 11);
            builder.line(11, 8);

            builder.line(12, 13);
            builder.line(13, 14);
            builder.line(14, 15);
            builder.line(15, 12);

            builder.line(16, 17);
            builder.line(17, 18);
            builder.line(18, 19);
            builder.line(19, 16);

            builder.line(8, 12);
            builder.line(9, 13);
            builder.line(10, 14);
            builder.line(11, 15);

            builder.line(12, 16);
            builder.line(13, 17);
            builder.line(14, 18);
            builder.line(15, 19);

            builder.end();

            mesh = builder.getMesh();
        }

        const string strBaseName = m_pList->getEntity()->getName() + ".Debug[" + getName() + "]";
        m_pEntity = getSceneManager()->createEntity(strBaseName + ".Mesh", mesh->getName());
        m_pSceneNode->attachObject(m_pEntity);
    }
}

//-----------------------------------------------------------------------

void Camera::hide()
{
    if (m_pEntity)
    {
        m_pSceneNode->detachObject(m_pEntity);
        getSceneManager()->destroyEntity(m_pEntity);
        m_pEntity = 0;
    }
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* Camera::getProperties() const
{
    // Call the base class implementation
    PropertiesList* pProperties = DebugComponent::getProperties();

    // Create the category belonging to this type
    pProperties->selectCategory(TYPE, false);

    // Returns the list
    return pProperties;
}
