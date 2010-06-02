/** @file	MeshBuilder.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::MeshBuilder'
*/

#ifndef _ATHENA_GRAPHICS_MESHBUILDER_H_
#define _ATHENA_GRAPHICS_MESHBUILDER_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Math/Vector3.h>
#include <Athena-Math/Vector2.h>
#include <Athena-Math/Quaternion.h>
#include <Athena-Math/Color.h>
#include <Athena-Math/AxisAlignedBox.h>
#include <Ogre/OgreMesh.h>
#include <Ogre/OgreResourceGroupManager.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief	Utility class used to simplify the creation of a manual mesh
///
/// This class is designed to be more powerfull than the Ogre::ManualObject one (which
///	doesn't support animated object for instance), but still easier to use than the raw
/// Hardware Buffers approch.
///
/// The design of the class is inspired by the one of Ogre::ManualObject.
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL MeshBuilder
{ 
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strMeshName			Name of the mesh
    /// @param	strResourceGroup	Name of the resource group in which the mesh is
    ///                             created
    //-----------------------------------------------------------------------------------
	MeshBuilder(const std::string& strMeshName, const std::string& strResourceGroup =
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
    ~MeshBuilder();

	
	//_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Set the name of the skeleton to assign to the mesh
    //-----------------------------------------------------------------------------------
	void setSkeletonName(const std::string& strSkeletonName);

    //-----------------------------------------------------------------------------------
    ///	@brief	Start defining the shared vertices of the mesh
    ///	@remark	Optional
    //-----------------------------------------------------------------------------------
	void beginSharedVertices();

    //-----------------------------------------------------------------------------------
    ///	@brief	Start defining a submesh of the mesh
    ///	@remark	Every mesh needs at least one submesh
    ///	@param	materialName		The name of the material used by the submesh
    ///	@param	opType				The type of render operation to use
    ///	@param	bUseSharedVertices	Indicates if the submesh use the shared vertices of
    ///								the mesh
    //-----------------------------------------------------------------------------------
	void begin(const std::string& strSubMeshName, const std::string& strMaterial,
			   Ogre::RenderOperation::OperationType opType = Ogre::RenderOperation::OT_TRIANGLE_LIST,
			   bool bUseSharedVertices = false);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare a vertex buffer for the current submesh
    ///	@remark	By default, the submesh has only one vertex buffer, with source = 0,
    ///			usage = HBU_STATIC_WRITE_ONLY and bUseShadowBuffer = false
    ///	@param	usage			One or more members of the HardwareBuffer::Usage enumeration;
    ///							you are strongly advised to use HBU_STATIC_WRITE_ONLY wherever
    ///							possible, if you need to update regularly, consider
    ///							HBU_DYNAMIC_WRITE_ONLY and useShadowBuffer=true.
    ///	@param	useShadowBuffer	If set to true, this buffer will be 'shadowed' by one stored in 
    ///							system memory rather than GPU or AGP memory. You should set
    ///							this flag if you intend to read data back from the vertex
    ///							buffer, because reading data from a buffer in the GPU or AGP
    ///							memory is very expensive, and is in fact impossible if you
    ///							specify HBU_WRITE_ONLY for the main buffer. If you use this
    ///							option, all reads and writes will be done to the shadow
    ///							buffer, and the shadow buffer will be synchronised with the
    ///							real buffer at an appropriate time.
    //-----------------------------------------------------------------------------------
	void declareVertexBuffer(unsigned short usSource, Ogre::HardwareBuffer::Usage usage,
	                         bool bUseShadowBuffer = false);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the index buffer for the current submesh
    ///	@remark	By default, the index buffer has usage = HBU_STATIC_WRITE_ONLY and
    ///			bUseShadowBuffer = false
    ///	@param	usage			One or more members of the HardwareBuffer::Usage enumeration;
    ///							you are strongly advised to use HBU_STATIC_WRITE_ONLY wherever
    ///							possible, if you need to update regularly, consider
    ///							HBU_DYNAMIC_WRITE_ONLY and useShadowBuffer=true.
    ///	@param	useShadowBuffer	If set to true, this buffer will be 'shadowed' by one stored in 
    ///							system memory rather than GPU or AGP memory. You should set
    ///							this flag if you intend to read data back from the vertex
    ///							buffer, because reading data from a buffer in the GPU or AGP
    ///							memory is very expensive, and is in fact impossible if you
    ///							specify HBU_WRITE_ONLY for the main buffer. If you use this
    ///							option, all reads and writes will be done to the shadow
    ///							buffer, and the shadow buffer will be synchronised with the
    ///							real buffer at an appropriate time.
    //-----------------------------------------------------------------------------------
	void declareIndexBuffer(Ogre::HardwareBuffer::Usage usage, bool bUseShadowBuffer = false);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the position of the vertices
    ///	@remark	By default, the positions are in the first vertex buffer (source = 0). If
    ///			you use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@param	usSource	Vertex buffer index
    //-----------------------------------------------------------------------------------
	void declarePosition(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the normals of the vertices
    ///	@remark	By default, the normals are in the first vertex buffer (source = 0). If
    ///			you use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@param	usSource	Vertex buffer index
    //-----------------------------------------------------------------------------------
	void declareNormal(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the diffuse colours of the vertices
    ///	@remark	By default, the colours are in the first vertex buffer (source = 0). If you
    ///			use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@param	usSource	Vertex buffer index
    //-----------------------------------------------------------------------------------
	void declareDiffuseColor(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the specular colours of the vertices
    ///	@remark	By default, the colours are in the first vertex buffer (source = 0). If you
    ///			use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@param	usSource	Vertex buffer index
    //-----------------------------------------------------------------------------------
	void declareSpecularColor(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the texture coordinates of the vertices
    ///	@remark	By default, the texture coordinates are in the first vertex buffer (source = 0).
    ///			If you use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@remark	A vertex can have more than one texture coordinates set.
    ///	@param	usSource	Vertex buffer index
    ///	@param	size		Number of texture coordinates in the set
    //-----------------------------------------------------------------------------------
	void declareTextureCoordinates(unsigned short usSource = 0, unsigned short size = 2);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the binormals of the vertices
    ///	@remark	By default, the binormals are in the first vertex buffer (source = 0).
    ///			If you use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@remark	A vertex can have more than one texture coordinates set.
    ///	@param	usSource	Vertex buffer index
    ///	@param	size		Number of texture coordinates in the set
    //-----------------------------------------------------------------------------------
	void declareBinormal(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Declare the vertex buffer that contains the tangents of the vertices
    ///	@remark	By default, the tangents are in the first vertex buffer (source = 0).
    ///			If you use one of the declare*() methods (beside declareVertexBuffer() and
    ///			declareIndexBuffer), you must fully declare your vertex structure.
    ///	@remark	A vertex can have more than one texture coordinates set.
    ///	@param	usSource	Vertex buffer index
    ///	@param	size		Number of texture coordinates in the set
    //-----------------------------------------------------------------------------------
	void declareTangent(unsigned short usSource = 0);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a vertex position, starting a new vertex at the same time
    ///	@remark	A vertex position is slightly special among the other vertex data methods
    ///			like normal() and textureCoord(), since calling it indicates the start of a
    ///			new vertex. All other vertex data methods you call after this are assumed to
    ///			be adding more information (like normals or texture coordinates) to the last
    ///			vertex started with position()
    /// @param	pos		The position of the vertex
    //-----------------------------------------------------------------------------------
	void position(const Math::Vector3& pos);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a vertex position, starting a new vertex at the same time
    ///	@remark	A vertex position is slightly special among the other vertex data methods
    ///			like normal() and textureCoord(), since calling it indicates the start of a
    ///			new vertex. All other vertex data methods you call after this are assumed to
    ///			be adding more information (like normals or texture coordinates) to the last
    ///			vertex started with position()
    /// @param	x	Position of the vertex on the X-axis
    /// @param	y	Position of the vertex on the Y-axis
    /// @param	z	Position of the vertex on the Z-axis
    //-----------------------------------------------------------------------------------
	void position(Math::Real x, Math::Real y, Math::Real z);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending weights to the current vertex
    /// @param	w1	The first weight
    /// @param	w2	The second weight
    //-----------------------------------------------------------------------------------
	void blendingWeights(Math::Real w1, Math::Real w2);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending weights to the current vertex
    /// @param	w1	The first weight
    /// @param	w2	The second weight
    /// @param	w3	The third weight
    //-----------------------------------------------------------------------------------
	void blendingWeights(Math::Real w1, Math::Real w2, Math::Real w3);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending weights to the current vertex
    /// @param	w1	The first weight
    /// @param	w2	The second weight
    /// @param	w3	The third weight
    /// @param	w4	The fourth weight
    //-----------------------------------------------------------------------------------
	void blendingWeights(Math::Real w1, Math::Real w2, Math::Real w3, Math::Real w4);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a blending index to the current vertex
    /// @param	index	The index
    //-----------------------------------------------------------------------------------
	void blendingIndices(unsigned short index);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending indices to the current vertex
    /// @param	i1	The first index
    /// @param	i2	The second index
    //-----------------------------------------------------------------------------------
	void blendingIndices(unsigned short i1, unsigned short i2);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending indices to the current vertex
    /// @param	i1	The first index
    /// @param	i2	The second index
    /// @param	i3	The third index
    //-----------------------------------------------------------------------------------
	void blendingIndices(unsigned short i1, unsigned short i2, unsigned short i3);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add some blending indices to the current vertex
    /// @param	i1	The first index
    /// @param	i2	The second index
    /// @param	i3	The third index
    /// @param	i4	The fourth index
    //-----------------------------------------------------------------------------------
	void blendingIndices(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a normal to the current vertex
    /// @param	normal	The normal
    //-----------------------------------------------------------------------------------
	void normal(const Math::Vector3& normal);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a normal to the current vertex
    /// @param	x	X-axis of the normal
    /// @param	y	Y-axis of the normal
    /// @param	z	Z-axis of the normal
    //-----------------------------------------------------------------------------------
	void normal(Math::Real x, Math::Real y, Math::Real z);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a diffuse color to the current vertex
    /// @param	col		The color
    //-----------------------------------------------------------------------------------
	void diffuseColor(const Math::Color& col);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a diffuse color to the current vertex
    /// @param	r	Red component of the color
    /// @param	g	Green component of the color
    /// @param	b	Blue component of the color
    /// @param	a	Alpha component of the color
    //-----------------------------------------------------------------------------------
	void diffuseColor(Math::Real r, Math::Real g, Math::Real b, Math::Real a = 1.0f);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a specular color to the current vertex
    /// @param	col		The color
    //-----------------------------------------------------------------------------------
	void specularColor(const Math::Color& col);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a specular color to the current vertex
    /// @param	r	Red component of the color
    /// @param	g	Green component of the color
    /// @param	b	Blue component of the color
    /// @param	a	Alpha component of the color
    //-----------------------------------------------------------------------------------
	void specularColor(Math::Real r, Math::Real g, Math::Real b, Math::Real a = 1.0f);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a texture coordinate to the current vertex.
    ///	@remark	You can call this method multiple times between position() calls to add
    ///			multiple texture coordinates to a vertex. Each one can have	between 1 and 3
    ///			dimensions, depending on your needs, although 2 is most common.
    ///	@param	u	U component of the texture coordinate
    //-----------------------------------------------------------------------------------
	void textureCoord(Math::Real u);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a texture coordinate to the current vertex.
    ///	@remark	You can call this method multiple times between position() calls to add
    ///			multiple texture coordinates to a vertex. Each one can have	between 1 and 3
    ///			dimensions, depending on your needs, although 2 is most common.
    ///	@param	u	U component of the texture coordinate
    ///	@param	v	V component of the texture coordinate
    //-----------------------------------------------------------------------------------
	void textureCoord(Math::Real u, Math::Real v);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a texture coordinate to the current vertex.
    ///	@remark	You can call this method multiple times between position() calls to add
    ///			multiple texture coordinates to a vertex. Each one can have	between 1 and 3
    ///			dimensions, depending on your needs, although 2 is most common.
    ///	@param	u	U component of the texture coordinate
    ///	@param	v	V component of the texture coordinate
    ///	@param	w	W component of the texture coordinate
    //-----------------------------------------------------------------------------------
	void textureCoord(Math::Real u, Math::Real v, Math::Real w);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a texture coordinate to the current vertex.
    ///	@remark	You can call this method multiple times between position() calls to add
    ///			multiple texture coordinates to a vertex. Each one can have	between 1 and 3
    ///			dimensions, depending on your needs, although 2 is most common.
    ///	@param	uv	UV components of the texture coordinate
    //-----------------------------------------------------------------------------------
	void textureCoord(const Math::Vector2& uv);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a texture coordinate to the current vertex.
    ///	@remark	You can call this method multiple times between position() calls to add
    ///			multiple texture coordinates to a vertex. Each one can have	between 1 and 3
    ///			dimensions, depending on your needs, although 2 is most common.
    ///	@param	uvw		The texture coordinate
    //-----------------------------------------------------------------------------------
	void textureCoord(const Math::Vector3& uvw);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a binormal to the current vertex
    /// @param	binormal	The binormal
    //-----------------------------------------------------------------------------------
	void binormal(const Math::Vector3& binormal);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a binormal to the current vertex
    /// @param	x	X-axis of the binormal
    /// @param	y	Y-axis of the binormal
    /// @param	z	Z-axis of the binormal
    //-----------------------------------------------------------------------------------
	void binormal(Math::Real x, Math::Real y, Math::Real z);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a tangent to the current vertex
    /// @param	tangent	The tangent
    //-----------------------------------------------------------------------------------
	void tangent(const Math::Vector3& tangent);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a tangent to the current vertex
    /// @param	x	X-axis of the tangent
    /// @param	y	Y-axis of the tangent
    /// @param	z	Z-axis of the tangent
    //-----------------------------------------------------------------------------------
	void tangent(Math::Real x, Math::Real y, Math::Real z);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a vertex index to construct faces/lines/points via indexing rather than
    ///			just by a simple list of vertices
    ///	@remark	You will have to call this 3 times for each face for a triangle list, or use
    ///			the alternative 3-parameter version. Other operation types require different
    ///			numbers of indexes, @see RenderOperation::OperationType.
    ///	@note	32-bit indexes are not supported on all cards which is why this class only
    ///			allows 16-bit indexes, for simplicity and ease of use
    ///	@param	idx		A vertex index from 0 to 65535
    //-----------------------------------------------------------------------------------
	void index(unsigned short index);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a set of 2 vertex indices to construct a line; this is a shortcut to
    ///			calling index() 2 times. It is only valid for line lists.
    ///	@note	32-bit indexes are not supported on all cards which is why this class only
    ///			allows 16-bit indexes, for simplicity and ease of use
    ///	@param	i1, i2, i3	3 vertex indices from 0 to 65535 defining a face
    //-----------------------------------------------------------------------------------
	void line(unsigned short i1, unsigned short i2);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a set of 3 vertex indices to construct a triangle; this is a shortcut to
    ///			calling index() 3 times. It is only valid for triangle lists.
    ///	@note	32-bit indexes are not supported on all cards which is why this class only
    ///			allows 16-bit indexes, for simplicity and ease of use
    ///	@param	i1, i2, i3	3 vertex indices from 0 to 65535 defining a face
    //-----------------------------------------------------------------------------------
	void triangle(unsigned short i1, unsigned short i2, unsigned short i3);

    //-----------------------------------------------------------------------------------
    ///	@brief	Add a set of 4 vertex indices to construct a quad (out of 2 triangles); this
    ///			is a shortcut to calling index() 6 times, or triangle() twice. It's only
    ///			valid for triangle list operations.
    ///	@note	32-bit indexes are not supported on all cards which is why this class only
    ///			allows 16-bit indexes, for simplicity and ease of use
    ///	@param	i1, i2, i3, i4	4 vertex indices from 0 to 65535 defining a quad
    //-----------------------------------------------------------------------------------
	void quad(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4);

    //-----------------------------------------------------------------------------------
    ///	@brief	Finish defining the submesh
    //-----------------------------------------------------------------------------------
	void end();

    //-----------------------------------------------------------------------------------
    ///	@brief	Finish defining the sharedVertices
    //-----------------------------------------------------------------------------------
	void endSharedVertices();

    //-----------------------------------------------------------------------------------
    ///	@brief	Returns the mesh
    ///	@return	The mesh
    //-----------------------------------------------------------------------------------
	Ogre::MeshPtr getMesh();

    //-----------------------------------------------------------------------------------
    ///	@brief	Returns the number of vertices in the current submesh
    ///	@return	The number of vertices
    //-----------------------------------------------------------------------------------
	unsigned short getNbVertices();

private:
	void copyTempVertexToBuffer();

	Ogre::VertexData* createVertexData();


	//_____ Internal types __________
private:
	struct tElement
	{
		Ogre::VertexElementSemantic	semantic;
		Ogre::VertexElementType		type;
		unsigned short				usIndex;
	};


	struct tVertex
	{
		Math::Vector3	position;
		unsigned short	blendingDim;
		Math::Real		blendingWeights[OGRE_MAX_BLEND_WEIGHTS];
		unsigned short	blendingIndices[OGRE_MAX_BLEND_WEIGHTS];
		Math::Vector3	normal;
		Math::Color	    diffuseColour;
		Math::Color     specularColour;
		Math::Vector3	texCoord[OGRE_MAX_TEXTURE_COORD_SETS];
		unsigned short	texCoordDims[OGRE_MAX_TEXTURE_COORD_SETS];
		Math::Vector3	binormal;
		Math::Vector3	tangent;
	};


	struct tHardwareBufferInfo
	{
		Ogre::HardwareBuffer::Usage	usage;
		bool						bUseShadowBuffer;
	};


	struct tSubMesh
	{
		std::string										    strName;
		std::string										    strMaterial;
		bool												bUseSharedVertices;
		Ogre::RenderOperation::OperationType				opType;
		std::map<unsigned short, std::vector<tElement> >	verticesElements;
		std::map<unsigned short, tHardwareBufferInfo>		vertexBufferInfos;
		tHardwareBufferInfo									indexBufferInfo;
		std::vector<tVertex>								vertices;
		std::vector<unsigned short>							indices;
	};


	//_____ Attributes __________
private:
	Ogre::MeshPtr				m_mesh;
	bool						m_bIsSharedVertices;
	tSubMesh					m_currentSubMesh;
	bool						m_bFirstVertex;
	bool						m_bAutomaticDeclaration;
	bool						m_bTempVertexPending;
	tVertex						m_currentVertex;
	Math::AxisAlignedBox		m_AABB;
	Math::Real					m_radius;
	unsigned short				m_usTextureCoordsIndex;
}; 

}
}

#endif
