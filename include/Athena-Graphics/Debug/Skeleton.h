/** @file	Skeleton.h
	@author	Philip Abbet

	Definition of the class 'Athena::Graphics::Debug::Skeleton'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_SKELETON_H_
#define _ATHENA_GRAPHICS_DEBUG_SKELETON_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Debug/DebugComponent.h>


namespace Athena {
namespace Graphics {
namespace Debug {


//---------------------------------------------------------------------------------------
/// @brief	Debug component that displays the skeleton of a visual component
///
/// The skeleton is retrieved from the assigned 'skeleton source' component. If none is
/// supplied, the transforms origin (if any) is used (if it has a skeleton).
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL Skeleton: public DebugComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Skeleton(const std::string& strName, Entities::ComponentsList* pList);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static Skeleton* create(const std::string& strName, Entities::ComponentsList* pList);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a Skeleton
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Skeleton
    //-----------------------------------------------------------------------------------
	static Skeleton* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Skeleton();


	//_____ Methods __________
public:
	void setSkeletonSource(Visual::Object* pPart);

	inline Visual::Object* getSkeletonSource() const
	{
		return m_pSkeletonSource;
	}

	inline void setBoneMaterial(const std::string& strMaterial = "Athena/Materials/Bone")
	{
		assert(!strMaterial.empty());
		m_strBoneMaterial = strMaterial;
	}

	inline void setSelectedBoneMaterial(const std::string& strMaterial = "Athena/Materials/SelectedBone")
	{
		assert(!strMaterial.empty());
		m_strSelectedBoneMaterial = strMaterial;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Select a bone on the representation of the skeleton (if any)
    ///
    /// @param	strBone	Name of the bone
    //-----------------------------------------------------------------------------------
	void selectBone(const std::string& strBone);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Deselect a bone on the representation of the skeleton (if any)
    ///
    /// @param	strBone	Name of the bone
    //-----------------------------------------------------------------------------------
	void deselectBone(const std::string& strBone);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Deselect all bones on the representation of the skeleton (if any)
    //-----------------------------------------------------------------------------------
	void deselectAllBones();

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Utility function called to add a face the the mesh representing a bone
    ///
    /// @param	point1		First point of the face
    /// @param	point2		Second point of the face
    /// @param	point3		Third point of the face
    /// @param	pBone		The bone
    /// @param	pBuilder	The mesh builder used
    //-----------------------------------------------------------------------------------
	void _addFace(const Math::Vector3& point1, const Math::Vector3& point2,
				  const Math::Vector3& point3, Ogre::Bone* pBone,
				  Graphics::MeshBuilder* pBuilder);


	//_____ Implementation of DebugComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Show the skeleton of the 'skeleton source' (if any)
    //-----------------------------------------------------------------------------------
	virtual void show();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Hide the skeleton
    //-----------------------------------------------------------------------------------
	virtual void hide();

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the type of the component
	/// @return	The type
	//-----------------------------------------------------------------------------------
	virtual const std::string getType() const
	{
		return TYPE;
	}


    //_____ Links management __________
protected:
	//-----------------------------------------------------------------------------------
	/// @brief	Called when a component this one is linked to must be unlinked
	///
	/// @remark	If you override it in your component, don't forget to call the base class
	///			implementation!
	//-----------------------------------------------------------------------------------
	virtual void mustUnlinkComponent(Component* pComponent);


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
	static const std::string TYPE;	            ///< Name of the type of component


	//_____ Attributes __________
protected:
	Visual::Object*	m_pSkeletonSource;			///< The visual component from which the skeleton is retrieved
	Ogre::Entity*	m_pSkeletonEntity;			///< Entity used to display the skeleton
	std::string		m_strBoneMaterial;			///< Material used to display the bones
	std::string		m_strSelectedBoneMaterial;	///< Material used to display the selected bones
};

}
}
}

#endif
