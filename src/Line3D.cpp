/** @file   Line3D.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::Line3D'
*/

// Athena's includes
#include <Athena-Graphics/Line3D.h>
#include <Athena-Math/Vector3.h>

// Ogre's includes
#include <Ogre/OgreHardwareBufferManager.h>
#include <Ogre/OgreCamera.h>
#include <Ogre/OgreSceneNode.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Math;
using namespace std;


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

Line3D::Line3D(Ogre::SceneNode* pSceneNode)
{
    assert(pSceneNode);

    mRenderOp.vertexData = new Ogre::VertexData();
    m_bDrawn = false;

    setMaterial("BaseWhiteNoLighting");

    pSceneNode->attachObject(this);
}

//-----------------------------------------------------------------------

Line3D::~Line3D()
{
    delete mRenderOp.vertexData;
}


/************************************* OPERATIONS **************************************/

void Line3D::addPoint(const Vector3& p)
{
    m_points.push_back(p);
}

//-----------------------------------------------------------------------

const Vector3& Line3D::getPoint(unsigned int index) const
{
    assert(index < m_points.size());

    return m_points[index];
}

//-----------------------------------------------------------------------

unsigned int Line3D::getNbPoints() const
{
    return (unsigned int) m_points.size();
}

//-----------------------------------------------------------------------

void Line3D::updatePoint(unsigned int index, const Vector3& value)
{
    assert(index < m_points.size());

    m_points[index] = value;
}

//-----------------------------------------------------------------------

void Line3D::drawLine(const Vector3& start, const Vector3& end)
{
    if (!m_points.empty())
        m_points.clear();

    m_points.push_back(start);
    m_points.push_back(end);

    drawLines();
}

//-----------------------------------------------------------------------

void Line3D::drawLines()
{
    // Declarations
    Ogre::VertexDeclaration*            pDeclaration;
    Ogre::VertexBufferBinding*          pBinding;
    Ogre::HardwareVertexBufferSharedPtr vbuf;

    if (m_bDrawn)
        return;
    else
        m_bDrawn = true;

    // Initialization stuff
    mRenderOp.indexData                 = 0;
    mRenderOp.vertexData->vertexCount   = m_points.size();
    mRenderOp.vertexData->vertexStart   = 0;
    mRenderOp.operationType             = Ogre::RenderOperation::OT_LINE_STRIP;
    mRenderOp.useIndexes                = false;

    pDeclaration = mRenderOp.vertexData->vertexDeclaration;
    pBinding = mRenderOp.vertexData->vertexBufferBinding;

    pDeclaration->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

    vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                                    pDeclaration->getVertexSize(0),
                                    mRenderOp.vertexData->vertexCount,
                                    Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    pBinding->setBinding(0, vbuf);

    // Drawing stuff
    int size = (int) m_points.size();
    Vector3 vaabMin = m_points[0];
    Vector3 vaabMax = m_points[0];

    Real* prPos = static_cast<Real*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    for (int i = 0; i < size; ++i)
    {
        *prPos++ = m_points[i].x;
        *prPos++ = m_points[i].y;
        *prPos++ = m_points[i].z;

        if(m_points[i].x < vaabMin.x)
            vaabMin.x = m_points[i].x;
        if(m_points[i].y < vaabMin.y)
            vaabMin.y = m_points[i].y;
        if(m_points[i].z < vaabMin.z)
            vaabMin.z = m_points[i].z;

        if(m_points[i].x > vaabMax.x)
            vaabMax.x = m_points[i].x;
        if(m_points[i].y > vaabMax.y)
            vaabMax.y = m_points[i].y;
        if(m_points[i].z > vaabMax.z)
            vaabMax.z = m_points[i].z;
    }

    vbuf->unlock();

    mBox.setExtents(vaabMin.x, vaabMin.y, vaabMin.z, vaabMax.x, vaabMax.y, vaabMax.z);
}


/*************************** OVERRIDES FOR SIMPLERENDERABLE ****************************/

Ogre::Real Line3D::getSquaredViewDepth(const Ogre::Camera* pCamera) const
{
    // Declarations
    Ogre::Vector3 vMin, vMax, vMid, vDist;

    vMin = mBox.getMinimum();
    vMax = mBox.getMaximum();
    vMid = ((vMin - vMax) * 0.5) + vMin;
    vDist = pCamera->getDerivedPosition() - vMid;

    return vDist.squaredLength();
}

//-----------------------------------------------------------------------

Ogre::Real Line3D::getBoundingRadius() const
{
    return Ogre::Math::Sqrt(std::max(mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength()));
}

//-----------------------------------------------------------------------

const Ogre::Quaternion& Line3D::getWorldOrientation() const
{
    return Ogre::Quaternion::IDENTITY;
}

//-----------------------------------------------------------------------

const Ogre::Vector3& Line3D::getWorldPosition() const
{
    return Ogre::Vector3::ZERO;
}
