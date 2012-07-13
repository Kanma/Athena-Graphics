/** @file	Camera.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::Camera'
*/

#ifndef _ATHENA_GRAPHICS_CAMERA_H_
#define _ATHENA_GRAPHICS_CAMERA_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Athena-Graphics/Conversions.h>
#include <Ogre/OgreRenderTarget.h>
#include <Ogre/OgreCamera.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	A visual component that manages a camera
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL Camera: public EntityComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Camera(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static Camera* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a Camera
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Camera
    //-----------------------------------------------------------------------------------
	static Camera* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Camera();


	//_____ Implementation of EntityComponent __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the type of the component
	/// @return	The type
	//-----------------------------------------------------------------------------------
	virtual const std::string getType() const
	{
		return TYPE;
	}


	//_____ Management of the camera __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the Ogre camera used by this component
	/// @return	The Ogre camera
	//-----------------------------------------------------------------------------------
	inline Ogre::Camera* getOgreCamera()
	{
		return m_pCamera;
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Create a viewport for this camera on the specified render target
	/// @param	pRenderTarget	The render target
	///	@param	iZOrder			The relative order of the viewport with others on the
	///							target (allows overlapping viewports i.e. picture-in-picture).
	///							Higher ZOrders are on top of lower ones. The actual number
    ///							is irrelevant, only the relative ZOrder matters (you can
	///							leave gaps in the numbering)
	///	@param	fLeft			The relative position of the left of the viewport on the
	///							target, as a value between 0 and 1
    ///	@param	fTop			The relative position of the top of the viewport on the
	///							target, as a value between 0 and 1
	///	@param	fWidth			The relative width of the viewport on the target, as a
	///							value between 0 and 1
	///	@param	fHeight			The relative height of the viewport on the target, as a
	///							value between 0 and 1
	/// @return					The viewport
	//-----------------------------------------------------------------------------------
	inline Ogre::Viewport* createViewport(Ogre::RenderTarget* pRenderTarget, int iZOrder = 0,  
										  float fLeft = 0.0f, float fTop = 0.0f,
										  float fWidth = 1.0f, float fHeight = 1.0f)
	{
		return pRenderTarget->addViewport(m_pCamera, iZOrder, fLeft, fTop, fWidth, fHeight);
	}


	//_____ Wrappers to the Ogre::Camera methods __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Sets the polygon mode required from this camera
	/// @param	mode	The polygon mode
	//-----------------------------------------------------------------------------------
	inline void setPolygonMode(Ogre::PolygonMode mode)
	{
		m_pCamera->setPolygonMode(mode);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Retrieves the polygon mode that the camera will render
	/// @return	The polygon mode
	//-----------------------------------------------------------------------------------
	inline Ogre::PolygonMode getPolygonMode() const
	{
		return m_pCamera->getPolygonMode();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the level-of-detail factor for this camera
	///
	/// This method can be used to influence the overall level of detail of the scenes 
	/// rendered using this camera. Various elements of the scene have level-of-detail
	/// reductions to improve rendering speed at distance; this method allows you 
	/// to hint to those elements that you would like to adjust the level of detail that
	/// they would normally use (up or down). 
	/// @par
	/// The most common use for this method is to reduce the overall level of detail used
	/// for a secondary camera used for sub viewports like rear-view mirrors etc.
	/// Note that scene elements are at liberty to ignore this setting if they choose,
	/// this is merely a hint.
	/// @param	factor	The factor to apply to the usual level of detail calculation.
	///					Higher values increase the detail, so 2.0 doubles the normal
	///					detail and 0.5 halves it
	//-----------------------------------------------------------------------------------
	inline void setLodBias(Math::Real factor = 1.0f)
	{
		m_pCamera->setLodBias(factor);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the level-of-detail bias factor currently applied to this camera
	/// @return	The factor
	//-----------------------------------------------------------------------------------
	inline Math::Real getLodBias() const
	{
		return m_pCamera->getLodBias();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Gets a world space ray as cast from the camera through a viewport position
	///
	/// @param	fScreenX, fScreenY	The x and y position at which the ray should intersect
	///								the viewport, in normalised screen coordinates [0,1]
	/// @return						The ray
	//-----------------------------------------------------------------------------------
	inline Ogre::Ray getCameraToViewportRay(Math::Real fScreenX, Math::Real fScreenY) const
	{
		return m_pCamera->getCameraToViewportRay(fScreenX, fScreenY);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Get the last viewport which was attached to this camera
	/// @note	This is not guaranteed to be the only viewport which is using this camera,
	///			just the last one which was created referring to it
	/// @return	The viewport
	//-----------------------------------------------------------------------------------
	inline Ogre::Viewport* getViewport() const
	{
		return m_pCamera->getViewport();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	If set to true a viewport that owns this frustum will be able to 
	///			recalculate the aspect ratio whenever the frustum is resized
	/// @remarks	You should set this to true only if the frustum / camera is used by 
	///				one viewport at the same time. Otherwise the aspect ratio for other 
	///				viewports may be wrong.
	/// @param	bAuto	Indicates if AutoAspectRatio is set or not
	//-----------------------------------------------------------------------------------
	inline void setAutoAspectRatio(bool bAuto)
	{
		m_pCamera->setAutoAspectRatio(bAuto);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates if AutoAspectRatio is currently set or not
	/// @return	'true' if it is set
	//-----------------------------------------------------------------------------------
	inline bool getAutoAspectRatio() const
	{
		return m_pCamera->getAutoAspectRatio();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the Y-dimension Field Of View (FOV) of the camera
	/// @remark	Field Of View (FOV) is the angle made between the frustum's position, and
	///			the edges of the 'screen' onto which the scene is projected. High values
	///			(90+ degrees) result in a wide-angle, fish-eye kind of view, low values
	///			(30- degrees) in a stretched, telescopic kind of view. Typical values are
	///			between 45 and 60 degrees.
	/// @par	This value represents the VERTICAL field-of-view. The horizontal field of
	///			view is calculated from this depending on the dimensions of the viewport
	///			(they will only be the same if the viewport is square).
	/// @param	fFOVy	The Y-dimension Field Of View
	//-----------------------------------------------------------------------------------
	inline void setFOVy(const Math::Radian& fFOVy)
	{
		m_pCamera->setFOVy(toOgre(fFOVy));
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Retrieves the camera's Y-dimension Field Of View (FOV)
	/// @return	The Y-dimension Field Of View
	//-----------------------------------------------------------------------------------
	inline const Math::Radian getFOVy() const
	{
		return fromOgre(m_pCamera->getFOVy());
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the position of the near clipping plane
	/// @remark	The position of the near clipping plane is the distance from the camera
	///			position to the screen on which the world is projected. The near plane
	///			distance, combined with the field-of-view and the aspect ratio, determines
	///			the size of the viewport through which the world is viewed (in world
	///			coordinates). Note that this world viewport is different to a screen
	///			viewport, which has it's dimensions expressed in pixels. The cameras
	///			viewport should have the same aspect ratio as the screen viewport it
	///			renders into to avoid distortion.
	/// @param	fNearDist	The position of the near clipping plane
	//-----------------------------------------------------------------------------------
	inline void setNearClipDistance(Math::Real fNearDist)
	{
		m_pCamera->setNearClipDistance(fNearDist);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the position of the near clipping plane
	/// @return	The position of the near clipping plane
	//-----------------------------------------------------------------------------------
	inline Math::Real getNearClipDistance() const
	{
		return m_pCamera->getNearClipDistance();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the distance to the far clipping plane
	/// @remark	The view frustrum is a pyramid created from the frustum position and the
	///			edges of the viewport. This method sets the distance for the far end of
	///			that pyramid. Different applications need different values: e.g. a flight
	///			sim needs a much further far clipping plane than a first-person shooter.
	///			An important point here is that the larger the ratio between near and far
	///			clipping planes, the lower the accuracy of the Z-buffer used to depth-cue
	///			pixels. This is because the Z-range is limited to the size of the Z buffer
	///			(16 or 32-bit) and the max values must be spread over the gap between near
	///			and far clip planes. As it happens, you can affect the accuracy far more
	///			by altering the near distance rather than the far distance, but keep this
	///			in mind.
	/// @param	fFarDist	The distance to the far clipping plane from the frustum in
	///						world coordinates.If you specify 0, this means an infinite view
	///						distance which is useful especially when projecting shadows,
	///						but be careful not to use a near distance too close
	//-----------------------------------------------------------------------------------
	inline void setFarClipDistance(Math::Real fFarDist)
	{
		m_pCamera->setFarClipDistance(fFarDist);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the distance from the frustum to the far clipping plane
	/// @return	The distance from the frustum to the far clipping plane
	//-----------------------------------------------------------------------------------
	inline Math::Real getFarClipDistance() const
	{
		return m_pCamera->getFarClipDistance();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the aspect ratio for the camera viewport
	/// @remark	The ratio between the x and y dimensions of the rectangular area visible
	///			through the frustum is known as aspect ratio: ratio = width / height
	/// @param	fRatio	The default for most fullscreen windows is 1.3333 - this is also
	///			assumed by Ogre unless you use this method to state otherwise
	//-----------------------------------------------------------------------------------
	inline void setAspectRatio(Math::Real fRatio)
	{
		m_pCamera->setAspectRatio(fRatio);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Retrieves the current aspect ratio
	/// @return	The aspect ratio
	//-----------------------------------------------------------------------------------
	inline Math::Real getAspectRatio() const
	{
		return m_pCamera->getAspectRatio();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Retrieves a specified plane of the frustum
	/// @param	plane	Number of the plane
	/// @return			The plane
	//-----------------------------------------------------------------------------------
	inline const Math::Plane getFrustumPlane(Ogre::FrustumPlane plane) const
	{
		return fromOgre(m_pCamera->getFrustumPlane(plane));
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given container is visible in the Frustum
	/// @param	bound		Bounding box to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the box if the result was false
	/// @return				If the box was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Math::AxisAlignedBox& bound, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(toOgre(bound), pCulledBy);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given container is visible in the Frustum
	/// @param	bound		Bounding box to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the box if the result was false
	/// @return				If the box was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Ogre::AxisAlignedBox& bound, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(bound, pCulledBy);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given container is visible in the Frustum
	/// @param	bound		Bounding sphere to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the sphere if the result was false
	/// @return				If the sphere was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Math::Sphere& bound, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(toOgre(bound), pCulledBy);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given container is visible in the Frustum
	/// @param	bound		Bounding sphere to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the sphere if the result was false
	/// @return				If the sphere was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Ogre::Sphere& bound, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(bound, pCulledBy);
	}

 	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given vertex is visible in the Frustum
	/// @param	vert		Vertex to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the vertex if the result was false
	/// @return				If the vertex was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Math::Vector3& vert, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(toOgre(vert), pCulledBy);
	}

 	//-----------------------------------------------------------------------------------
	/// @brief	Tests whether the given vertex is visible in the Frustum
	/// @param	vert		Vertex to be checked
	/// @retval	pCulledBy	Optional pointer which will be filled by the plane number
	///						which culled the vertex if the result was false
	/// @return				If the vertex was visible, true is returned
	//-----------------------------------------------------------------------------------
	inline bool isVisible(const Ogre::Vector3& vert, Ogre::FrustumPlane* pCulledBy = 0) const
	{
		return m_pCamera->isVisible(vert, pCulledBy);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the world space corners of the frustum
	///	@remark	The corners are ordered as follows: top-right near, top-left near,
	///			bottom-left near, bottom-right near, top-right far, top-left far,
	///			bottom-left far, bottom-right far
	/// @return	The corners
	//-----------------------------------------------------------------------------------
	inline const Ogre::Vector3* getWorldSpaceCorners() const
	{
		return m_pCamera->getWorldSpaceCorners();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Sets the type of projection to use (orthographic or perspective).
	///			Default is perspective
	///
	/// @param	pt	The type of projection
	//-----------------------------------------------------------------------------------
	inline void setProjectionType(Ogre::ProjectionType pt)
	{
		m_pCamera->setProjectionType(pt);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the type of projection used (orthographic or perspective)
	/// @return	The type of projection
	//-----------------------------------------------------------------------------------
	inline Ogre::ProjectionType getProjectionType() const
	{
		return m_pCamera->getProjectionType();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Modifies the camera so it always renders from the reflection of itself
	///			through the plane specified
	///	@remark	This is obviously useful for performing planar reflections
	/// @param	plane	The plane
	//-----------------------------------------------------------------------------------
	inline void enableReflection(const Math::Plane& plane)
	{
		m_pCamera->enableReflection(toOgre(plane));
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Modifies the camera so it always renders from the reflection of itself
	///			through the plane specified
	///	@remark	This is obviously useful for performing planar reflections
	/// @param	plane	The plane
	//-----------------------------------------------------------------------------------
	inline void enableReflection(const Ogre::Plane& plane)
	{
		m_pCamera->enableReflection(plane);
	}

 	//-----------------------------------------------------------------------------------
	/// @brief	Modifies the camera so it always renders from the reflection of itself
	///			through the plane specified
	/// @note	This version of the method links to a plane so that changes to it are
	///			picked up automatically. It is important that this plane continues to
	///			exist whilst this object does; do not destroy the plane before the frustum.
	///	@remark	This is obviously useful for performing planar reflections
	/// @param	plane	The plane
	//-----------------------------------------------------------------------------------
	inline void enableReflection(const Ogre::MovablePlane* plane)
	{
		m_pCamera->enableReflection(plane);
	}

 	//-------------------------------------------------------------------------------
	/// @brief	Disables reflection modification previously turned on
	//-------------------------------------------------------------------------------
	inline void disableReflection()
	{
		m_pCamera->disableReflection();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates whether the camera is being reflected
	/// @return	'true' if the camera is being reflected
	//-----------------------------------------------------------------------------------
	inline bool isReflected() const
	{
		return m_pCamera->isReflected();
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the reflection matrix of the camera if appropriate
	/// @return	The reflection matrix
	//-----------------------------------------------------------------------------------
	inline const Math::Matrix4 getReflectionMatrix() const
	{
		return fromOgre(m_pCamera->getReflectionMatrix());
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the reflection plane of the camera if appropriate
	/// @return	The reflection plane
	//-----------------------------------------------------------------------------------
	inline const Math::Plane getReflectionPlane() const
	{
		return fromOgre(m_pCamera->getReflectionPlane());
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Project a sphere onto the near plane and get the bounding rectangle
	/// @param	sphere	The world-space sphere to project
	/// @param	pLeft, pTop, pRight, pBottom	Pointers to destination values, these
	///											will be completed with the normalised
	///											device coordinates (in the range {-1,1})
	/// @return	'true' if the sphere was projected to a subset of the near plane,
	///			'false' if the entire near plane was contained
	//-----------------------------------------------------------------------------------
	inline bool projectSphere(const Math::Sphere& sphere, Math::Real* pLeft, Math::Real* pTop,
							  Math::Real* pRight, Math::Real* pBottom) const
	{
		return m_pCamera->projectSphere(toOgre(sphere), pLeft, pTop, pRight, pBottom);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Links the frustum to a custom near clip plane, which can be used to clip
	///			geometry in a custom manner without using user clip planes
	/// @remark	There are several applications for clipping a scene arbitrarily by a
	///			single plane; the most common is when rendering a reflection to a texture,
	///			and you only want to render geometry that is above the water plane (to do
	///			otherwise results in artefacts). Whilst it is possible to use user clip
	///			planes, they are not supported on all cards, and sometimes are not
	///			hardware accelerated when they are available. Instead, where a single
	///			clip plane is involved, this technique uses a 'fudging' of the near clip
	///			plane, which is available and fast on all hardware, to perform as the
	///			arbitrary clip plane. This does change the shape of the frustum, leading
	///			to some depth buffer loss of precision, but for many of the uses of this
	///			technique that is not an issue.
	/// @par 	This version of the method links to a plane, rather than requiring a
	///			by-value plane definition, and therefore you can make changes to the plane
	///			(e.g. by moving / rotating the node it is attached to) and they will
	///			automatically affect this object.
	///	@note	This technique only works for perspective projection.
	/// @param	pPlane	The plane to link to to perform the clipping. This plane must
	///					continue to exist while the camera is linked to it; do not destroy
	///					it before the camera
	//-----------------------------------------------------------------------------------
	inline void enableCustomNearClipPlane(const Ogre::MovablePlane* pPlane)
	{
		m_pCamera->enableCustomNearClipPlane(pPlane);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Links the frustum to a custom near clip plane, which can be used to clip
	///			geometry in a custom manner without using user clip planes
	/// @remark	There are several applications for clipping a scene arbitrarily by a
	///			single plane; the most common is when rendering a reflection to a texture,
	///			and you only want to render geometry that is above the water plane (to do
	///			otherwise results in artefacts). Whilst it is possible to use user clip
	///			planes, they are not supported on all cards, and sometimes are not
	///			hardware accelerated when they are available. Instead, where a single
	///			clip plane is involved, this technique uses a 'fudging' of the near clip
	///			plane, which is available and fast on all hardware, to perform as the
	///			arbitrary clip plane. This does change the shape of the frustum, leading
	///			to some depth buffer loss of precision, but for many of the uses of this
	///			technique that is not an issue.
	///	@note	This technique only works for perspective projection.
	/// @param	plane	The plane to link to to perform the clipping
	//-----------------------------------------------------------------------------------
	inline void enableCustomNearClipPlane(const Math::Plane& plane)
	{
		m_pCamera->enableCustomNearClipPlane(toOgre(plane));
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Disables any custom near clip plane
	//-----------------------------------------------------------------------------------
	inline void disableCustomNearClipPlane()
	{
		m_pCamera->disableCustomNearClipPlane();
	}


	//_____ Management of the properties __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Returns a list containing the properties of the component
    ///
    /// Used in the serialization mecanism of the components
    /// @remark	Must be overriden by each component type. Each implementation must first call
    ///			its base class one, and add a new category (named after the component's type)
    ///			AT THE BEGINNING of the obtained list, containing the properties related to
    ///			this type.
    /// @return	The list of properties
    //-----------------------------------------------------------------------------------
	virtual Utils::PropertiesList* getProperties() const;
	
    //-----------------------------------------------------------------------------------
    /// @brief	Set the value of a property of the component
    ///
    /// Used in the deserialization mecanism of the parts
    ///	@param	strCategory		The category of the property
    ///	@param	strName			The name of the property
    ///	@param	pValue			The value of the property
    ///	@return					'true' if the property was used, 'false' if a required object
    ///							is missing
    /// @remark	Must be overriden by each component type. Each implementation must test if the
    ///			property's category is the one of the component's type, and if so process the
    ///			property's value. Otherwise, it must call its base class implementation.
    //-----------------------------------------------------------------------------------
	virtual bool setProperty(const std::string& strCategory, const std::string& strName,
							 Utils::Variant* pValue);

    //-----------------------------------------------------------------------------------
    /// @brief	Set the value of a property of the component
    ///
    /// Used in the deserialization mecanism of the parts
    ///	@param	strName		The name of the property
    ///	@param	pValue		The value of the property
    ///	@return				'true' if the property was used, 'false' if a required object
    ///						is missing
    //-----------------------------------------------------------------------------------
	bool setProperty(const std::string& strName, Utils::Variant* pValue);



	//_____ Constants __________
public:
	static const std::string TYPE;	///< Name of the type of component


	//_____ Attributes __________
protected:
	Ogre::Camera* m_pCamera;		///< The Ogre camera
};

}
}
}

#endif
