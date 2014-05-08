/** @file   MeshBuilder.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::MeshBuilder'
*/

// Athena's includes
#include <Athena-Graphics/MeshBuilder.h>
#include <Athena-Graphics/Conversions.h>

// Ogre's includes
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreHardwareBufferManager.h>
#include <Ogre/OgreSubMesh.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Math;
using namespace std;

using Ogre::MeshManager;
using Ogre::HardwareBuffer;
using Ogre::HardwareBufferManager;
using Ogre::HardwareIndexBuffer;
using Ogre::HardwareVertexBufferSharedPtr;
using Ogre::SubMesh;
using Ogre::VertexBoneAssignment;
using Ogre::VertexBufferBinding;
using Ogre::VertexData;
using Ogre::VertexElement;


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

MeshBuilder::MeshBuilder(const std::string& strMeshName, const std::string& strResourceGroup)
: m_bIsSharedVertices(false), m_bFirstVertex(true), m_bAutomaticDeclaration(true),
  m_bTempVertexPending(false), m_AABB(Vector3::ZERO, Vector3::ZERO), m_radius(0.0f)
{
    // Creation of the mesh
    m_mesh = MeshManager::getSingletonPtr()->createManual(strMeshName, strResourceGroup);

    m_currentVertex.position        = Vector3::ZERO;
    m_currentVertex.blendingDim     = 0;
    m_currentVertex.normal          = Vector3::ZERO;
    m_currentVertex.diffuseColour   = Color::Black;
    m_currentVertex.specularColour  = Color::Black;
    m_currentVertex.binormal        = Vector3::ZERO;
    m_currentVertex.tangent         = Vector3::ZERO;

    memset(m_currentVertex.blendingWeights, 0, sizeof(m_currentVertex.blendingWeights));
    memset(m_currentVertex.blendingIndices, 0, sizeof(m_currentVertex.blendingIndices));
    memset(m_currentVertex.texCoord, 0, sizeof(m_currentVertex.texCoord));
    memset(m_currentVertex.texCoordDims, 0, sizeof(m_currentVertex.texCoordDims));
}

//-----------------------------------------------------------------------

MeshBuilder::~MeshBuilder()
{
}


/************************************** METHODS ****************************************/

void MeshBuilder::setSkeletonName(const std::string& strSkeletonName)
{
    m_mesh->setSkeletonName(strSkeletonName);
}

//-----------------------------------------------------------------------

void MeshBuilder::beginSharedVertices()
{
    assert(!m_bIsSharedVertices && !m_mesh->sharedVertexData && "You cannot call beginSharedVertices() more than one time");
    assert(m_currentSubMesh.strName.empty() && "You cannot call beginSharedVertices() until after you call end()");

    m_bIsSharedVertices     = true;
    m_bFirstVertex          = true;
    m_bAutomaticDeclaration = true;
    m_bTempVertexPending    = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::begin(const std::string& strSubMeshName, const std::string& strMaterial,
                        Ogre::RenderOperation::OperationType opType, bool bUseSharedVertices)
{
    assert(!m_bIsSharedVertices && "You cannot call begin() until after you call endSharedVertices()");
    assert(m_currentSubMesh.strName.empty() && "You cannot call begin() again until after you call end()");
    assert(!strSubMeshName.empty() && "The name of the submesh can't be empty");
    assert(!bUseSharedVertices || m_mesh->sharedVertexData);

    m_currentSubMesh.strName            = strSubMeshName;
    m_currentSubMesh.strMaterial        = strMaterial;
    m_currentSubMesh.opType             = opType;
    m_currentSubMesh.bUseSharedVertices = bUseSharedVertices;

    m_bFirstVertex          = true;
    m_bAutomaticDeclaration = true;
    m_bTempVertexPending    = false;

    m_currentSubMesh.indexBufferInfo.usage              = HardwareBuffer::HBU_STATIC_WRITE_ONLY;
    m_currentSubMesh.indexBufferInfo.bUseShadowBuffer   = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareVertexBuffer(unsigned short usSource, Ogre::HardwareBuffer::Usage usage,
                                      bool bUseShadowBuffer)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareVertexBuffer()");

    m_currentSubMesh.vertexBufferInfos[usSource].usage              = usage;
    m_currentSubMesh.vertexBufferInfos[usSource].bUseShadowBuffer   = bUseShadowBuffer;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareIndexBuffer(Ogre::HardwareBuffer::Usage usage, bool bUseShadowBuffer)
{
    assert(!m_currentSubMesh.strName.empty() && "You must call begin() before you call declareIndexBuffer()");

    m_currentSubMesh.indexBufferInfo.usage              = usage;
    m_currentSubMesh.indexBufferInfo.bUseShadowBuffer   = bUseShadowBuffer;
}

//-----------------------------------------------------------------------

void MeshBuilder::declarePosition(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declarePosition()");

    tElement element;
    element.semantic    = Ogre::VES_POSITION;
    element.type        = Ogre::VET_FLOAT3;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareNormal(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareNormal()");

    tElement element;
    element.semantic    = Ogre::VES_NORMAL;
    element.type        = Ogre::VET_FLOAT3;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareDiffuseColor(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareDiffuseColour()");

    tElement element;
    element.semantic    = Ogre::VES_DIFFUSE;
    element.type        = Ogre::VET_COLOUR_ARGB;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareSpecularColor(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareSpecularColour()");

    tElement element;
    element.semantic    = Ogre::VES_SPECULAR;
    element.type        = Ogre::VET_COLOUR_ARGB;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareTextureCoordinates(unsigned short usSource, unsigned short size)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareTextureCoordinates()");

    tElement element;
    element.semantic = Ogre::VES_TEXTURE_COORDINATES;

    switch (size)
    {
    case 1:
        element.type = Ogre::VET_FLOAT1;
        break;

    case 2:
        element.type = Ogre::VET_FLOAT2;
        break;

    case 3:
        element.type = Ogre::VET_FLOAT3;
        break;
    }

    for (unsigned int i = 0; i < OGRE_MAX_TEXTURE_COORD_SETS; ++i)
    {
        if (m_currentVertex.texCoordDims[i] == 0)
        {
            m_currentVertex.texCoordDims[i] = size;
            element.usIndex                 = i;
            break;
        }
        else if (i == OGRE_MAX_TEXTURE_COORD_SETS - 1)
        {
            assert(false && "Too much texture coordinates set");
        }
    }

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareBinormal(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareBinormal()");

    tElement element;
    element.semantic    = Ogre::VES_BINORMAL;
    element.type        = Ogre::VET_FLOAT3;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::declareTangent(unsigned short usSource)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call declareTangent()");

    tElement element;
    element.semantic    = Ogre::VES_TANGENT;
    element.type        = Ogre::VET_FLOAT3;
    element.usIndex     = 0;

    m_currentSubMesh.verticesElements[usSource].push_back(element);

    m_bAutomaticDeclaration = false;
}

//-----------------------------------------------------------------------

void MeshBuilder::position(const Vector3& pos)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call position()");

    // If a temporary vertex is pending, add it to the list
    if (m_bTempVertexPending)
        copyTempVertexToBuffer();

    if (m_bAutomaticDeclaration)
    {
        if (m_bFirstVertex)
        {
            declarePosition();
            m_bAutomaticDeclaration = true;
            m_bFirstVertex = false;
        }
        else
        {
            m_bAutomaticDeclaration = false;
        }
    }

    m_currentVertex.position = pos;

    // Update bounds
    m_AABB.merge(pos);
    m_radius = std::max(m_radius, pos.length());

    // Reset current texture coord
    m_usTextureCoordsIndex = 0;

    m_bTempVertexPending = true;
}

//-----------------------------------------------------------------------

void MeshBuilder::position(Real x, Real y, Real z)
{
    position(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingWeights(Real w1, Real w2)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingWeights()");
    assert((m_currentVertex.blendingDim == 0) && "You can't call blendingWeights more than one time");

    m_currentVertex.blendingDim         = 2;
    m_currentVertex.blendingWeights[0]  = w1;
    m_currentVertex.blendingWeights[1]  = w2;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingWeights(Real w1, Real w2, Real w3)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingWeights()");
    assert((m_currentVertex.blendingDim == 0) && "You can't call blendingWeights more than one time");

    m_currentVertex.blendingDim         = 3;
    m_currentVertex.blendingWeights[0]  = w1;
    m_currentVertex.blendingWeights[1]  = w2;
    m_currentVertex.blendingWeights[2]  = w3;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingWeights(Real w1, Real w2, Real w3, Real w4)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingWeights()");
    assert((m_currentVertex.blendingDim == 0) && "You can't call blendingWeights more than one time");

    m_currentVertex.blendingDim         = 3;
    m_currentVertex.blendingWeights[0]  = w1;
    m_currentVertex.blendingWeights[1]  = w2;
    m_currentVertex.blendingWeights[2]  = w3;
    m_currentVertex.blendingWeights[3]  = w4;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingIndices(unsigned short index)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingIndices()");
    assert((m_currentVertex.blendingDim == 0) && "You can't call blendingIndices more than one time");

    m_currentVertex.blendingDim         = 1;
    m_currentVertex.blendingWeights[0]  = 1.0f;
    m_currentVertex.blendingIndices[0]  = index;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingIndices(unsigned short i1, unsigned short i2)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingIndices()");
    assert((m_currentVertex.blendingDim == 2) && "The number of blending indices is incorrect");

    m_currentVertex.blendingIndices[0] = i1;
    m_currentVertex.blendingIndices[1] = i2;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingIndices(unsigned short i1, unsigned short i2, unsigned short i3)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingIndices()");
    assert((m_currentVertex.blendingDim == 3) && "The number of blending indices is incorrect");

    m_currentVertex.blendingIndices[0] = i1;
    m_currentVertex.blendingIndices[1] = i2;
    m_currentVertex.blendingIndices[2] = i3;
}

//-----------------------------------------------------------------------

void MeshBuilder::blendingIndices(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call blendingIndices()");
    assert((m_currentVertex.blendingDim == 4) && "The number of blending indices is incorrect");

    m_currentVertex.blendingIndices[0] = i1;
    m_currentVertex.blendingIndices[1] = i2;
    m_currentVertex.blendingIndices[2] = i3;
    m_currentVertex.blendingIndices[3] = i4;
}

//-----------------------------------------------------------------------

void MeshBuilder::normal(const Vector3& normal)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call normal()");

    if (m_bAutomaticDeclaration)
    {
        declareNormal();
        m_bAutomaticDeclaration = true;
    }

    m_currentVertex.normal = normal;
}

//-----------------------------------------------------------------------

void MeshBuilder::normal(Real x, Real y, Real z)
{
    normal(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshBuilder::diffuseColor(const Color& col)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call diffuseColour()");

    if (m_bAutomaticDeclaration)
    {
        declareDiffuseColor();
        m_bAutomaticDeclaration = true;
    }

    m_currentVertex.diffuseColour = col;
}

//-----------------------------------------------------------------------

void MeshBuilder::diffuseColor(Real r, Real g, Real b, Real a)
{
    diffuseColor(Color(r, g, b, a));
}

//-----------------------------------------------------------------------

void MeshBuilder::specularColor(const Color& col)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call specularColour()");

    if (m_bAutomaticDeclaration)
    {
        declareSpecularColor();
        m_bAutomaticDeclaration = true;
    }

    m_currentVertex.specularColour = col;
}

//-----------------------------------------------------------------------

void MeshBuilder::specularColor(Real r, Real g, Real b, Real a)
{
    specularColor(Color(r, g, b, a));
}

//-----------------------------------------------------------------------

void MeshBuilder::textureCoord(Real u)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call textureCoord()");

    if (m_bAutomaticDeclaration)
    {
        declareTextureCoordinates(0, 1);
        m_bAutomaticDeclaration = true;

        m_currentVertex.texCoordDims[m_usTextureCoordsIndex] = 1;
    }

    m_currentVertex.texCoord[m_usTextureCoordsIndex].x = u;

    ++m_usTextureCoordsIndex;
}

//-----------------------------------------------------------------------

void MeshBuilder::textureCoord(Real u, Real v)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call textureCoord()");

    if (m_bAutomaticDeclaration)
    {
        declareTextureCoordinates(0, 2);
        m_bAutomaticDeclaration = true;

        m_currentVertex.texCoordDims[m_usTextureCoordsIndex] = 2;
    }

    m_currentVertex.texCoord[m_usTextureCoordsIndex].x = u;
    m_currentVertex.texCoord[m_usTextureCoordsIndex].y = v;

    ++m_usTextureCoordsIndex;
}

//-----------------------------------------------------------------------

void MeshBuilder::textureCoord(Real u, Real v, Real w)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call textureCoord()");

    if (m_bAutomaticDeclaration)
    {
        declareTextureCoordinates(0, 3);
        m_bAutomaticDeclaration = true;

        m_currentVertex.texCoordDims[m_usTextureCoordsIndex] = 3;
    }

    m_currentVertex.texCoord[m_usTextureCoordsIndex].x = u;
    m_currentVertex.texCoord[m_usTextureCoordsIndex].y = v;
    m_currentVertex.texCoord[m_usTextureCoordsIndex].z = w;

    ++m_usTextureCoordsIndex;
}

//-----------------------------------------------------------------------

void MeshBuilder::textureCoord(const Vector2& uv)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call textureCoord()");

    if (m_bAutomaticDeclaration)
    {
        declareTextureCoordinates(0, 2);
        m_bAutomaticDeclaration = true;

        m_currentVertex.texCoordDims[m_usTextureCoordsIndex] = 2;
    }

    m_currentVertex.texCoord[m_usTextureCoordsIndex].x = uv.x;
    m_currentVertex.texCoord[m_usTextureCoordsIndex].y = uv.y;

    ++m_usTextureCoordsIndex;
}

//-----------------------------------------------------------------------

void MeshBuilder::textureCoord(const Vector3& uvw)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call textureCoord()");

    if (m_bAutomaticDeclaration)
    {
        declareTextureCoordinates(0, 3);
        m_bAutomaticDeclaration = true;

        m_currentVertex.texCoordDims[m_usTextureCoordsIndex] = 3;
    }

    m_currentVertex.texCoord[m_usTextureCoordsIndex] = uvw;

    ++m_usTextureCoordsIndex;
}

//-----------------------------------------------------------------------

void MeshBuilder::binormal(const Vector3& binormal)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call binormal()");

    if (m_bAutomaticDeclaration)
    {
        declareBinormal();
        m_bAutomaticDeclaration = true;
    }

    m_currentVertex.binormal = binormal;
}

//-----------------------------------------------------------------------

void MeshBuilder::binormal(Real x, Real y, Real z)
{
    binormal(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshBuilder::tangent(const Vector3& tangent)
{
    assert(m_bIsSharedVertices || !m_currentSubMesh.strName.empty() && "You must call begin() before you call tangent()");

    if (m_bAutomaticDeclaration)
    {
        declareTangent();
        m_bAutomaticDeclaration = true;
    }

    m_currentVertex.tangent = tangent;
}

//-----------------------------------------------------------------------

void MeshBuilder::tangent(Real x, Real y, Real z)
{
    tangent(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshBuilder::index(unsigned short index)
{
    assert(!m_bIsSharedVertices && !m_currentSubMesh.strName.empty() && "You must call begin() before you call index()");

    m_currentSubMesh.indices.push_back(index);
}

//-----------------------------------------------------------------------

void MeshBuilder::line(unsigned short i1, unsigned short i2)
{
    assert(!m_bIsSharedVertices && !m_currentSubMesh.strName.empty() && "You must call begin() before you call line()");

    m_currentSubMesh.indices.push_back(i1);
    m_currentSubMesh.indices.push_back(i2);
}

//-----------------------------------------------------------------------

void MeshBuilder::triangle(unsigned short i1, unsigned short i2, unsigned short i3)
{
    assert(!m_bIsSharedVertices && !m_currentSubMesh.strName.empty() && "You must call begin() before you call triangle()");

    m_currentSubMesh.indices.push_back(i1);
    m_currentSubMesh.indices.push_back(i2);
    m_currentSubMesh.indices.push_back(i3);
}

//-----------------------------------------------------------------------

void MeshBuilder::quad(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4)
{
    assert(!m_bIsSharedVertices && !m_currentSubMesh.strName.empty() && "You must call begin() before you call triangle()");

    triangle(i1, i2, i3);
    triangle(i3, i4, i1);
}

//-----------------------------------------------------------------------

void MeshBuilder::end()
{
    assert(!m_bIsSharedVertices && !m_currentSubMesh.strName.empty() && "You must call begin() before you call end()");
    assert(!m_currentSubMesh.bUseSharedVertices || m_mesh->sharedVertexData);

    // Declarations
    std::map<unsigned short, std::vector<tElement> >::iterator  iterSource, iterSourceEnd;
    std::vector<tVertex>::iterator                              iterVertex, iterVertexEnd;
    HardwareVertexBufferSharedPtr                               vbuffer;
    VertexData*                                                 pVertexData;

    // If a temporary vertex is pending, add it to the list
    if (m_bTempVertexPending)
        copyTempVertexToBuffer();

    m_bFirstVertex          = false;
    m_bAutomaticDeclaration = false;
    m_bIsSharedVertices     = false;

    // Create the submesh
    SubMesh* pSubMesh = m_mesh->createSubMesh(m_currentSubMesh.strName);
    pSubMesh->setMaterialName(m_currentSubMesh.strMaterial);
    pSubMesh->useSharedVertices = m_currentSubMesh.bUseSharedVertices;
    pSubMesh->operationType = m_currentSubMesh.opType;

    // Initializes the vertex declaration if necessary
    if (!m_currentSubMesh.bUseSharedVertices)
    {
        pSubMesh->vertexData = createVertexData();
        pVertexData = pSubMesh->vertexData;
    }
    else
    {
        pVertexData = m_mesh->sharedVertexData;
    }

    // Add the vertices into their buffers
    VertexBufferBinding::VertexBufferBindingMap bindings = pVertexData->vertexBufferBinding->getBindings();
    for (iterSource = m_currentSubMesh.verticesElements.begin(), iterSourceEnd = m_currentSubMesh.verticesElements.end();
        iterSource != iterSourceEnd; ++iterSource)
    {
        unsigned int vertexIndex = 0;

        for (iterVertex = m_currentSubMesh.vertices.begin(), iterVertexEnd = m_currentSubMesh.vertices.end();
            iterVertex != iterVertexEnd; ++iterVertex)
        {
            if ((iterVertex->blendingDim > 0) && !m_mesh->getSkeletonName().empty())
            {
                VertexBoneAssignment ass;
                ass.vertexIndex = vertexIndex;

                for (unsigned int i = 0; i < iterVertex->blendingDim; ++i)
                {
                    ass.boneIndex   = iterVertex->blendingIndices[i];
                    ass.weight      = iterVertex->blendingWeights[i];
                    pSubMesh->addBoneAssignment(ass);
                }
            }

            ++vertexIndex;
        }
    }


    // Add the indices into their buffer
    pSubMesh->indexData->indexCount = m_currentSubMesh.indices.size();
    pSubMesh->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(
                                                    HardwareIndexBuffer::IT_16BIT, m_currentSubMesh.indices.size(),
                                                    m_currentSubMesh.indexBufferInfo.usage,
                                                    m_currentSubMesh.indexBufferInfo.bUseShadowBuffer);
    pSubMesh->indexData->indexBuffer->writeData(0, m_currentSubMesh.indices.size() * sizeof(unsigned short),
                                                &m_currentSubMesh.indices[0]);


    // Update the AABB and the radius of the mesh
    m_mesh->_setBounds(toOgre(m_AABB));
    m_mesh->_setBoundingSphereRadius(m_radius);


    // Reset the internal state
    m_currentSubMesh.strName            = "";
    m_currentSubMesh.strMaterial        = "";
    m_currentSubMesh.bUseSharedVertices = false;

    m_currentSubMesh.indexBufferInfo.usage              = HardwareBuffer::HBU_STATIC_WRITE_ONLY;
    m_currentSubMesh.indexBufferInfo.bUseShadowBuffer   = false;

    m_currentSubMesh.verticesElements.clear();
    m_currentSubMesh.vertexBufferInfos.clear();
    m_currentSubMesh.vertices.clear();
    m_currentSubMesh.indices.clear();
}

//-----------------------------------------------------------------------

void MeshBuilder::endSharedVertices()
{
    assert(m_bIsSharedVertices && "You must call beginSharedVertices() before you call endSharedVertices()");

    // If a temporary vertex is pending, add it to the list
    if (m_bTempVertexPending)
        copyTempVertexToBuffer();

    m_bFirstVertex          = false;
    m_bAutomaticDeclaration = false;
    m_bIsSharedVertices     = false;

    // Create the vertex data
    m_mesh->sharedVertexData = createVertexData();

    // Update the AABB and the radius of the mesh
    m_mesh->_setBounds(toOgre(m_AABB));
    m_mesh->_setBoundingSphereRadius(m_radius);

    // Reset the internal state
    m_currentSubMesh.strName            = "";
    m_currentSubMesh.strMaterial        = "";
    m_currentSubMesh.strMaterial        = "";
    m_currentSubMesh.bUseSharedVertices = false;

    m_currentSubMesh.indexBufferInfo.usage              = HardwareBuffer::HBU_STATIC_WRITE_ONLY;
    m_currentSubMesh.indexBufferInfo.bUseShadowBuffer   = false;

    m_currentSubMesh.verticesElements.clear();
    m_currentSubMesh.vertexBufferInfos.clear();
    m_currentSubMesh.vertices.clear();
    m_currentSubMesh.indices.clear();
}

//-----------------------------------------------------------------------

Ogre::VertexData* MeshBuilder::createVertexData()
{
    // Declarations
    std::map<unsigned short, std::vector<tElement> >::iterator  iterSource, iterSourceEnd;
    std::vector<tVertex>::iterator                              iterVertex, iterVertexEnd;
    HardwareVertexBufferSharedPtr                               vbuffer;
    float                                                       fBuffer[4];


    // Create the vertex data
    VertexData* pVertexData = new VertexData();
    pVertexData->vertexStart = 0;
    pVertexData->vertexCount = m_currentSubMesh.vertices.size();


    // Initializes the vertex declaration
    for (iterSource = m_currentSubMesh.verticesElements.begin(), iterSourceEnd = m_currentSubMesh.verticesElements.end();
         iterSource != iterSourceEnd; ++iterSource)
    {
        size_t offset = 0;

        std::vector<tElement>::iterator iter, iterEnd;
        for (iter = iterSource->second.begin(), iterEnd = iterSource->second.end();
             iter != iterEnd; ++iter)
        {
            pVertexData->vertexDeclaration->addElement(iterSource->first, offset, iter->type, iter->semantic, iter->usIndex);
            offset += VertexElement::getTypeSize(iter->type);
        }

        vbuffer = HardwareBufferManager::getSingleton().createVertexBuffer(offset, m_currentSubMesh.vertices.size(),
                                            m_currentSubMesh.vertexBufferInfos[iterSource->first].usage,
                                            m_currentSubMesh.vertexBufferInfos[iterSource->first].bUseShadowBuffer);

        pVertexData->vertexBufferBinding->setBinding(iterSource->first, vbuffer);
    }


    // Add the vertices into their buffers
    VertexBufferBinding::VertexBufferBindingMap bindings = pVertexData->vertexBufferBinding->getBindings();
    for (iterSource = m_currentSubMesh.verticesElements.begin(), iterSourceEnd = m_currentSubMesh.verticesElements.end();
        iterSource != iterSourceEnd; ++iterSource)
    {
        vbuffer = bindings[iterSource->first];

        size_t          offset = 0;
        unsigned int    vertexIndex = 0;

        for (iterVertex = m_currentSubMesh.vertices.begin(), iterVertexEnd = m_currentSubMesh.vertices.end();
            iterVertex != iterVertexEnd; ++iterVertex)
        {
            std::vector<tElement>::iterator iter, iterEnd;
            for (iter = iterSource->second.begin(), iterEnd = iterSource->second.end();
                iter != iterEnd; ++iter)
            {
                switch (iter->semantic)
                {
                case Ogre::VES_POSITION:
                    fBuffer[0] = iterVertex->position.x;
                    fBuffer[1] = iterVertex->position.y;
                    fBuffer[2] = iterVertex->position.z;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_NORMAL:
                    fBuffer[0] = iterVertex->normal.x;
                    fBuffer[1] = iterVertex->normal.y;
                    fBuffer[2] = iterVertex->normal.z;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_BINORMAL:
                    fBuffer[0] = iterVertex->binormal.x;
                    fBuffer[1] = iterVertex->binormal.y;
                    fBuffer[2] = iterVertex->binormal.z;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_TANGENT:
                    fBuffer[0] = iterVertex->tangent.x;
                    fBuffer[1] = iterVertex->tangent.y;
                    fBuffer[2] = iterVertex->tangent.z;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_DIFFUSE:
                    fBuffer[0] = iterVertex->diffuseColour.a;
                    fBuffer[1] = iterVertex->diffuseColour.r;
                    fBuffer[2] = iterVertex->diffuseColour.g;
                    fBuffer[3] = iterVertex->diffuseColour.b;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_SPECULAR:
                    fBuffer[0] = iterVertex->specularColour.a;
                    fBuffer[1] = iterVertex->specularColour.r;
                    fBuffer[2] = iterVertex->specularColour.g;
                    fBuffer[3] = iterVertex->specularColour.b;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_TEXTURE_COORDINATES:
                    fBuffer[0] = iterVertex->texCoord[iter->usIndex].x;
                    fBuffer[1] = iterVertex->texCoord[iter->usIndex].y;
                    fBuffer[2] = iterVertex->texCoord[iter->usIndex].z;
                    vbuffer->writeData(offset, VertexElement::getTypeSize(iter->type), fBuffer);
                    break;

                case Ogre::VES_BLEND_WEIGHTS:
                case Ogre::VES_BLEND_INDICES:
                    // Nothing to do, but the compiler complains if not present
                    break;
                }

                offset += VertexElement::getTypeSize(iter->type);
            }

            ++vertexIndex;
        }
    }

    return pVertexData;
}

//-----------------------------------------------------------------------

void MeshBuilder::copyTempVertexToBuffer()
{
    assert(m_bTempVertexPending);

    m_currentSubMesh.vertices.push_back(m_currentVertex);

    m_currentVertex.position        = Vector3::ZERO;
    m_currentVertex.blendingDim     = 0;
    m_currentVertex.normal          = Vector3::ZERO;
    m_currentVertex.diffuseColour   = Color::Black;
    m_currentVertex.specularColour  = Color::Black;
    m_currentVertex.binormal        = Vector3::ZERO;
    m_currentVertex.tangent         = Vector3::ZERO;

    memset(m_currentVertex.blendingWeights, 0, sizeof(m_currentVertex.blendingWeights));
    memset(m_currentVertex.blendingIndices, 0, sizeof(m_currentVertex.blendingIndices));
    memset(m_currentVertex.texCoord, 0, sizeof(m_currentVertex.texCoord));
    memset(m_currentVertex.texCoordDims, 0, sizeof(m_currentVertex.texCoordDims));

    m_bTempVertexPending = false;
}

//-----------------------------------------------------------------------

Ogre::MeshPtr MeshBuilder::getMesh()
{
    assert(m_currentSubMesh.strName.empty() && "You must call end() before you call getMesh()");
    assert((m_mesh->getNumSubMeshes() > 0) && "You must create at least one submesh before you call getMesh()");

    if (!m_mesh->isLoaded())
        m_mesh->load();

    return m_mesh;
}

//-----------------------------------------------------------------------

unsigned short MeshBuilder::getNbVertices()
{
    assert(!m_currentSubMesh.strName.empty() && "You must call begin() before you call getNbVertices()");

    return (unsigned short) m_currentSubMesh.vertices.size() + (m_bTempVertexPending ? 1 : 0);
}
