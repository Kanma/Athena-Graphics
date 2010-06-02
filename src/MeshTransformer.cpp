/**	@file	MeshTransformer.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::MeshTransformer'
*/

// Athena's includes
#include <Athena-Graphics/MeshTransformer.h>
#include <Athena-Graphics/Conversions.h>

// Ogre's includes
#include <Ogre/OgreMeshManager.h>
#include <Ogre/OgreBone.h>
#include <Ogre/OgreHardwareBufferManager.h>
#include <Ogre/OgreMesh.h>
#include <Ogre/OgreSkeleton.h>
#include <Ogre/OgreSubMesh.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Math;
using namespace std;

using Ogre::Bone;
using Ogre::Mesh;
using Ogre::MeshManager;
using Ogre::Node;
using Ogre::Skeleton;
using Ogre::SkeletonPtr;
using Ogre::SubMesh;
using Ogre::HardwareBuffer;
using Ogre::HardwareVertexBufferSharedPtr;
using Ogre::VertexElement;


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

MeshTransformer::MeshTransformer(const std::string& strMeshName,
								 const std::string& strResourceGroup)
: m_mesh(0)
{
	m_mesh = MeshManager::getSingletonPtr()->load(strMeshName, strResourceGroup, HardwareBuffer::HBU_DYNAMIC);
	assert(!m_mesh.isNull());
}

//-----------------------------------------------------------------------

MeshTransformer::MeshTransformer(const Ogre::MeshPtr& mesh)
: m_mesh(mesh)
{
	assert(!m_mesh.isNull());
}

//-----------------------------------------------------------------------

MeshTransformer::~MeshTransformer()
{
}


/************************************** METHODS ****************************************/

void MeshTransformer::scale(Real fUniformScale)
{
	assert(fUniformScale > 0.0f);

	scale(fUniformScale, fUniformScale, fUniformScale);
}

//-----------------------------------------------------------------------

void MeshTransformer::scale(Real x, Real y, Real z)
{
	assert(x > 0.0f);
	assert(y > 0.0f);
	assert(z > 0.0f);

	scale(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshTransformer::scale(const Vector3& scale)
{
	// Process the shared vertex data (if any)
	if (m_mesh->sharedVertexData)
		this->scale(m_mesh->sharedVertexData, scale);

	// Process the submeshes' vertex data
	Mesh::SubMeshIterator iter = m_mesh->getSubMeshIterator();
	while (iter.hasMoreElements())
	{
		SubMesh* pSubMesh = iter.getNext();

		if (pSubMesh->vertexData)
			this->scale(pSubMesh->vertexData, scale);
	}

	// Update the bounding informations
	AxisAlignedBox aabb(fromOgre(m_mesh->getBounds()));
	aabb.scale(scale);
	m_mesh->_setBounds(toOgre(aabb));
	m_mesh->_setBoundingSphereRadius(m_mesh->getBoundingSphereRadius() * std::max(scale.x, std::max(scale.y, scale.z)));

	SkeletonPtr pSkeleton = m_mesh->getSkeleton();
	if (!pSkeleton.isNull())
	{
		pSkeleton->reset();

		Skeleton::BoneIterator iter = pSkeleton->getBoneIterator();
        Ogre::Vector3 ogreScale = toOgre(scale);
		while (iter.hasMoreElements())
		{
			Bone* pBone = iter.getNext();
			pBone->setPosition(pBone->getPosition() * ogreScale);
			pBone->_update(false, false);
		}

		pSkeleton->setBindingPose();
	}
}

//-----------------------------------------------------------------------

void MeshTransformer::scale(Ogre::VertexData* pVertexData, const Vector3& scale)
{
	// Retrieve the declaration of the interesting elements of the vertices
	const VertexElement* pPositionVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
	const VertexElement* pNormalVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
	const VertexElement* pTangentVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_TANGENT);
	const VertexElement* pBinormalVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_BINORMAL);

	// Retrieve the buffer that contains the interesting elements
	HardwareVertexBufferSharedPtr bufferPositions =
		pVertexData->vertexBufferBinding->getBuffer(pPositionVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferNormals = !pNormalVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pNormalVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferTangents = !pTangentVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pTangentVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferBinormals = !pBinormalVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pBinormalVertexElement->getSource());

	// Update the elements of each vertex
	float buffer[3];
	size_t offsetPosition	= pVertexData->vertexStart * bufferPositions->getVertexSize() + pPositionVertexElement->getOffset();
	size_t offsetNormal		= !pNormalVertexElement ? 0 :
							  pVertexData->vertexStart * bufferNormals->getVertexSize() + pNormalVertexElement->getOffset();
	size_t offsetTangent	= !pTangentVertexElement ? 0 :
							  pVertexData->vertexStart * bufferTangents->getVertexSize() + pTangentVertexElement->getOffset();
	size_t offsetBinormal	= !pBinormalVertexElement ? 0 :
							  pVertexData->vertexStart * bufferBinormals->getVertexSize() + pBinormalVertexElement->getOffset();
	for (unsigned int i = 0; i < pVertexData->vertexCount; ++i)
	{
		// Position
		bufferPositions->readData(offsetPosition, pPositionVertexElement->getSize(), &buffer);
		
		Vector3 pos = scale * Vector3(buffer);

		buffer[0] = pos.x;
		buffer[1] = pos.y;
		buffer[2] = pos.z;

		bufferPositions->writeData(offsetPosition, pPositionVertexElement->getSize(), &buffer);

		offsetPosition += bufferPositions->getVertexSize();


		// Normal
		if (pNormalVertexElement)
		{
			bufferNormals->readData(offsetNormal, pNormalVertexElement->getSize(), &buffer);
			
			Vector3 normal = scale * Vector3(buffer);
			normal.normalise();

			buffer[0] = normal.x;
			buffer[1] = normal.y;
			buffer[2] = normal.z;

			bufferNormals->writeData(offsetNormal, pNormalVertexElement->getSize(), &buffer);

			offsetNormal += bufferNormals->getVertexSize();
		}


		// Tangent
		if (pTangentVertexElement)
		{
			bufferTangents->readData(offsetTangent, pTangentVertexElement->getSize(), &buffer);
			
			Vector3 tangent = scale * Vector3(buffer);
			tangent.normalise();

			buffer[0] = tangent.x;
			buffer[1] = tangent.y;
			buffer[2] = tangent.z;

			bufferTangents->writeData(offsetTangent, pTangentVertexElement->getSize(), &buffer);

			offsetTangent += bufferTangents->getVertexSize();
		}


		// Binormal
		if (pBinormalVertexElement)
		{
			bufferBinormals->readData(offsetBinormal, pBinormalVertexElement->getSize(), &buffer);
			
			Vector3 binormal = scale * Vector3(buffer);
			binormal.normalise();

			buffer[0] = binormal.x;
			buffer[1] = binormal.y;
			buffer[2] = binormal.z;

			bufferBinormals->writeData(offsetBinormal, pBinormalVertexElement->getSize(), &buffer);

			offsetBinormal += bufferBinormals->getVertexSize();
		}
	}
}

//-----------------------------------------------------------------------

void MeshTransformer::translateOrigin(Real x, Real y, Real z)
{
	translateOrigin(Vector3(x, y, z));
}

//-----------------------------------------------------------------------

void MeshTransformer::translateOrigin(const Vector3& d)
{
	AxisAlignedBox aabb = fromOgre(m_mesh->getBounds());
	Vector3 max = aabb.getCenter();

	// Process the shared vertex data (if any)
	if (m_mesh->sharedVertexData)
		translateOrigin(m_mesh->sharedVertexData, d, max);

	// Process the submeshes' vertex data
	Mesh::SubMeshIterator iter = m_mesh->getSubMeshIterator();
	while (iter.hasMoreElements())
	{
		SubMesh* pSubMesh = iter.getNext();

		if (pSubMesh->vertexData)
			translateOrigin(pSubMesh->vertexData, d, max);
	}

	// Update the bounding informations
	m_mesh->_setBounds(Ogre::AxisAlignedBox(toOgre(aabb.getMinimum() + d), toOgre(aabb.getMaximum() + d)));
	float fDelta = m_mesh->getBoundingSphereRadius() - max.length();
	max += d;
	m_mesh->_setBoundingSphereRadius(max.length() + fDelta);

	SkeletonPtr pSkeleton = m_mesh->getSkeleton();
	if (!pSkeleton.isNull())
	{
		pSkeleton->reset();

		Skeleton::BoneIterator iter = pSkeleton->getRootBoneIterator();
        Ogre::Vector3 d2 = toOgre(d);
		while (iter.hasMoreElements())
		{
			Bone* pBone = iter.getNext();
			pBone->translate(d2, Node::TS_PARENT);
			pBone->_update(false, false);
		}

		pSkeleton->setBindingPose();
	}
}

//-----------------------------------------------------------------------

void MeshTransformer::translateOrigin(Ogre::VertexData* pVertexData, const Vector3& d, Vector3& max)
{
	// Retrieve the declaration of the positions of the vertices
	const VertexElement* pVertexElement = pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

	// Retrieve the buffer that contains the positions
	HardwareVertexBufferSharedPtr buffer =
		pVertexData->vertexBufferBinding->getBuffer(pVertexElement->getSource());

	// Update the position of each vertex
	float pos[3];
	size_t offset = pVertexData->vertexStart * buffer->getVertexSize() + pVertexElement->getOffset();
	for (unsigned int i = 0; i < pVertexData->vertexCount; ++i)
	{
		buffer->readData(offset, pVertexElement->getSize(), &pos);
		
		max.x = std::max(pos[0], max.x);
		max.y = std::max(pos[1], max.y);
		max.z = std::max(pos[2], max.z);

		pos[0] += d.x;
		pos[1] += d.y;
		pos[2] += d.z;

		buffer->writeData(offset, pVertexElement->getSize(), &pos);

		offset += buffer->getVertexSize();
	}
}

//-----------------------------------------------------------------------

void MeshTransformer::rotate(const Quaternion& q)
{
	AxisAlignedBox aabb = fromOgre(m_mesh->getBounds());
	Vector3 max = aabb.getCenter();

	// Process the shared vertex data (if any)
	if (m_mesh->sharedVertexData)
		rotate(m_mesh->sharedVertexData, q, max);

	// Process the submeshes' vertex data
	Mesh::SubMeshIterator iter = m_mesh->getSubMeshIterator();
	while (iter.hasMoreElements())
	{
		SubMesh* pSubMesh = iter.getNext();

		if (pSubMesh->vertexData)
			rotate(pSubMesh->vertexData, q, max);
	}

	// Update the bounding informations
	m_mesh->_setBounds(Ogre::AxisAlignedBox(toOgre(q * aabb.getMinimum()), toOgre(q * aabb.getMaximum())));

	SkeletonPtr pSkeleton = m_mesh->getSkeleton();
	if (!pSkeleton.isNull())
	{
		pSkeleton->reset();

		Skeleton::BoneIterator iter = pSkeleton->getRootBoneIterator();
        Ogre::Quaternion q2 = toOgre(q);
		while (iter.hasMoreElements())
		{
			Bone* pBone = iter.getNext();
			pBone->setPosition(q2 * pBone->getPosition());
			pBone->rotate(q2, Node::TS_WORLD);
			pBone->_update(true, false);
		}

		pSkeleton->setBindingPose();
	}
}

//-----------------------------------------------------------------------

void MeshTransformer::rotate(const Vector3& axis, const Radian& angle)
{
	rotate(Quaternion(angle, axis));
}

//-----------------------------------------------------------------------

void MeshTransformer::rotate(Ogre::VertexData* pVertexData, const Quaternion& q, Vector3& max)
{
	// Retrieve the declaration of the interesting elements of the vertices
	const VertexElement* pPositionVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
	const VertexElement* pNormalVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
	const VertexElement* pTangentVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_TANGENT);
	const VertexElement* pBinormalVertexElement	= pVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_BINORMAL);

	// Retrieve the buffer that contains the interesting elements
	HardwareVertexBufferSharedPtr bufferPositions =
		pVertexData->vertexBufferBinding->getBuffer(pPositionVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferNormals = !pNormalVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pNormalVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferTangents = !pTangentVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pTangentVertexElement->getSource());
	HardwareVertexBufferSharedPtr bufferBinormals = !pBinormalVertexElement ? HardwareVertexBufferSharedPtr(0) :
		pVertexData->vertexBufferBinding->getBuffer(pBinormalVertexElement->getSource());

	// Update the elements of each vertex
	float buffer[3];
	size_t offsetPosition	= pVertexData->vertexStart * bufferPositions->getVertexSize() + pPositionVertexElement->getOffset();
	size_t offsetNormal		= !pNormalVertexElement ? 0 :
							  pVertexData->vertexStart * bufferNormals->getVertexSize() + pNormalVertexElement->getOffset();
	size_t offsetTangent	= !pTangentVertexElement ? 0 :
							  pVertexData->vertexStart * bufferTangents->getVertexSize() + pTangentVertexElement->getOffset();
	size_t offsetBinormal	= !pBinormalVertexElement ? 0 :
							  pVertexData->vertexStart * bufferBinormals->getVertexSize() + pBinormalVertexElement->getOffset();
	for (unsigned int i = 0; i < pVertexData->vertexCount; ++i)
	{
		// Position
		bufferPositions->readData(offsetPosition, pPositionVertexElement->getSize(), &buffer);
		
		max.x = std::max(buffer[0], max.x);
		max.y = std::max(buffer[1], max.y);
		max.z = std::max(buffer[2], max.z);

		Vector3 pos = q * Vector3(buffer);

		buffer[0] = pos.x;
		buffer[1] = pos.y;
		buffer[2] = pos.z;

		bufferPositions->writeData(offsetPosition, pPositionVertexElement->getSize(), &buffer);

		offsetPosition += bufferPositions->getVertexSize();


		// Normal
		if (pNormalVertexElement)
		{
			bufferNormals->readData(offsetNormal, pNormalVertexElement->getSize(), &buffer);
			
			Vector3 normal = q * Vector3(buffer);

			buffer[0] = normal.x;
			buffer[1] = normal.y;
			buffer[2] = normal.z;

			bufferNormals->writeData(offsetNormal, pNormalVertexElement->getSize(), &buffer);

			offsetNormal += bufferNormals->getVertexSize();
		}


		// Tangent
		if (pTangentVertexElement)
		{
			bufferTangents->readData(offsetTangent, pTangentVertexElement->getSize(), &buffer);
			
			Vector3 tangent = q * Vector3(buffer);

			buffer[0] = tangent.x;
			buffer[1] = tangent.y;
			buffer[2] = tangent.z;

			bufferTangents->writeData(offsetTangent, pTangentVertexElement->getSize(), &buffer);

			offsetTangent += bufferTangents->getVertexSize();
		}


		// Binormal
		if (pBinormalVertexElement)
		{
			bufferBinormals->readData(offsetBinormal, pBinormalVertexElement->getSize(), &buffer);
			
			Vector3 binormal = q * Vector3(buffer);

			buffer[0] = binormal.x;
			buffer[1] = binormal.y;
			buffer[2] = binormal.z;

			bufferBinormals->writeData(offsetBinormal, pBinormalVertexElement->getSize(), &buffer);

			offsetBinormal += bufferBinormals->getVertexSize();
		}
	}
}
