/** @file   AudioSource.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::Debug::AudioSource'
*/

#include <Athena-Graphics/Debug/AudioSource.h>
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
static const char*  __CONTEXT__         = "Debug/AudioSource";

///< Name of the type of entity
const std::string   AudioSource::TYPE   = "Athena/Debug/AudioSource";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

AudioSource::AudioSource(const std::string& strName, Entities::ComponentsList* pList)
: DebugComponent(strName, pList)
{
}

//-----------------------------------------------------------------------

AudioSource::~AudioSource()
{
    hide();
}

//-----------------------------------------------------------------------

AudioSource* AudioSource::create(const std::string& strName, ComponentsList* pList)
{
    return new AudioSource(strName, pList);
}

//-----------------------------------------------------------------------

AudioSource* AudioSource::cast(Component* pComponent)
{
    return dynamic_cast<AudioSource*>(pComponent);
}


/*************************************** METHODS ***************************************/

void AudioSource::show()
{
    // Declarations
    const Real  cos30   = MathUtils::Cos(Degree(30));
    const Real  cos60   = MathUtils::Cos(Degree(60));
    const Real  sin30   = MathUtils::Sin(Degree(30));
    const Real  sin60   = MathUtils::Sin(Degree(60));
    Line3D* pLine;

    if (m_lines.empty())
    {
        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(1.0f, 0, 0));
        pLine->addPoint(Vector3(1.0f * cos30, 1.0f * sin30, 0));
        pLine->addPoint(Vector3(1.0f * cos60, 1.0f * sin60, 0));
        pLine->addPoint(Vector3(0, 1.0f, 0));
        pLine->addPoint(Vector3(-1.0f * cos60, 1.0f * sin60, 0));
        pLine->addPoint(Vector3(-1.0f * cos30, 1.0f * sin30, 0));
        pLine->addPoint(Vector3(-1.0f, 0, 0));
        pLine->addPoint(Vector3(-1.0f * cos30, -1.0f * sin30, 0));
        pLine->addPoint(Vector3(-1.0f * cos60, -1.0f * sin60, 0));
        pLine->addPoint(Vector3(0, -1.0f, 0));
        pLine->addPoint(Vector3(1.0f * cos60, -1.0f * sin60, 0));
        pLine->addPoint(Vector3(1.0f * cos30, -1.0f * sin30, 0));
        pLine->addPoint(Vector3(1.0f, 0, 0));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(0.5f, 0, -0.5f));
        pLine->addPoint(Vector3(0.5f * cos30, 0.5f * sin30, -0.5f));
        pLine->addPoint(Vector3(0.5f * cos60, 0.5f * sin60, -0.5f));
        pLine->addPoint(Vector3(0, 0.5f, -0.5f));
        pLine->addPoint(Vector3(-0.5f * cos60, 0.5f * sin60, -0.5f));
        pLine->addPoint(Vector3(-0.5f * cos30, 0.5f * sin30, -0.5f));
        pLine->addPoint(Vector3(-0.5f, 0, -0.5f));
        pLine->addPoint(Vector3(-0.5f * cos30, -0.5f * sin30, -0.5f));
        pLine->addPoint(Vector3(-0.5f * cos60, -0.5f * sin60, -0.5f));
        pLine->addPoint(Vector3(0, -0.5f, -0.5f));
        pLine->addPoint(Vector3(0.5f * cos60, -0.5f * sin60, -0.5f));
        pLine->addPoint(Vector3(0.5f * cos30, -0.5f * sin30, -0.5f));
        pLine->addPoint(Vector3(0.5f, 0, -0.5f));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(0.5f, 0, -0.8f));
        pLine->addPoint(Vector3(0.5f * cos30, 0.5f * sin30, -0.8f));
        pLine->addPoint(Vector3(0.5f * cos60, 0.5f * sin60, -0.8f));
        pLine->addPoint(Vector3(0, 0.5f, -0.8f));
        pLine->addPoint(Vector3(-0.5f * cos60, 0.5f * sin60, -0.8f));
        pLine->addPoint(Vector3(-0.5f * cos30, 0.5f * sin30, -0.8f));
        pLine->addPoint(Vector3(-0.5f, 0, -0.8f));
        pLine->addPoint(Vector3(-0.5f * cos30, -0.5f * sin30, -0.8f));
        pLine->addPoint(Vector3(-0.5f * cos60, -0.5f * sin60, -0.8f));
        pLine->addPoint(Vector3(0, -0.5f, -0.8f));
        pLine->addPoint(Vector3(0.5f * cos60, -0.5f * sin60, -0.8f));
        pLine->addPoint(Vector3(0.5f * cos30, -0.5f * sin30, -0.8f));
        pLine->addPoint(Vector3(0.5f, 0, -0.8f));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(0.0f, 0.5f, -0.8f));
        pLine->addPoint(Vector3(0.0f, 0.5f, -0.5f));
        pLine->addPoint(Vector3(0.0f, 1.0f, 0.0f));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(0.0f, -0.5f, -0.8f));
        pLine->addPoint(Vector3(0.0f, -0.5f, -0.5f));
        pLine->addPoint(Vector3(0.0f, -1.0f, 0.0f));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(-0.5f, 0.0f, -0.8f));
        pLine->addPoint(Vector3(-0.5f, 0.0f, -0.5f));
        pLine->addPoint(Vector3(-1.0f, 0.0f, 0.0f));
        pLine->drawLines();
        m_lines.push_back(pLine);

        pLine = new Line3D(m_pSceneNode);
        pLine->addPoint(Vector3(0.5f, 0.0f, -0.8f));
        pLine->addPoint(Vector3(0.5f, 0.0f, -0.5f));
        pLine->addPoint(Vector3(1.0f, 0.0f, 0.0f));
        pLine->drawLines();
        m_lines.push_back(pLine);


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

void AudioSource::hide()
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


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* AudioSource::getProperties() const
{
    // Call the base class implementation
    PropertiesList* pProperties = DebugComponent::getProperties();

    // Create the category belonging to this type
    pProperties->selectCategory(TYPE, false);

    // Returns the list
    return pProperties;
}
