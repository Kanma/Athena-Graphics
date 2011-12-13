/** @file	Object.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::Object'
*/

#ifndef _ATHENA_GRAPHICS_OBJECT_H_
#define _ATHENA_GRAPHICS_OBJECT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Ogre/OgreEntity.h>
#include <Ogre/OgreResourceGroupManager.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	A visual component that contains a mesh
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Object: public EntityComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Object(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static Object* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a Object
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Object
    //-----------------------------------------------------------------------------------
	static Object* cast(Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Object();


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


	//_____ Methods __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the Ogre entity used by this component
	/// @return	The Ogre entity
	//-----------------------------------------------------------------------------------
	inline Ogre::Entity* getOgreEntity()
	{
		return m_pEntity;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Load a mesh
    ///
    /// @param	strMeshName		The name of the mesh
    /// @param	strGroupName	The name of the resource group
    /// @return					'true' if successful
    //-----------------------------------------------------------------------------------
	bool loadMesh(const std::string& strMeshName, const std::string& strGroupName =
				  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	
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
	static const std::string TYPE;  ///< Name of the type of component


	//_____ Attributes __________
protected:
	Ogre::Entity* m_pEntity;
};

}
}
}

#endif
