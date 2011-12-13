/** @file	DirectionalLight.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::DirectionalLight'
*/

#ifndef _ATHENA_GRAPHICS_DIRECTIONALLIGHT_H_
#define _ATHENA_GRAPHICS_DIRECTIONALLIGHT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Ogre/OgreLight.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	A visual component that manages a directional light
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL DirectionalLight: public EntityComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	DirectionalLight(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static DirectionalLight* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a DirectionalLight
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a DirectionalLight
    //-----------------------------------------------------------------------------------
	static DirectionalLight* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~DirectionalLight();


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


	//_____ Management of the Light __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the Ogre light used by this component
	/// @return	The Ogre light
	//-----------------------------------------------------------------------------------
	inline Ogre::Light* getOgreLight()
	{
		return m_pLight;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Sets the color of the diffuse light given off by this source
    /// @param	color	The diffuse color
    /// @remark	Material objects have ambient, diffuse and specular values which indicate
    ///			how much of each type of light an object reflects. This value denotes the
    ///			amount and colour of this type of light the light exudes into the scene.
    ///			The actual appearance of objects is a combination of the two.
    ///			Diffuse light simulates the typical light emanating from light sources and
    ///			affects the base colour of objects together with ambient light. 
    //-----------------------------------------------------------------------------------
	void setDiffuseColor(const Math::Color& color) const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the colour of the diffuse light given off by this light source
    ///			(see setDiffuseColor for more info)
    /// @return	The diffuse color
    //-----------------------------------------------------------------------------------
	const Math::Color getDiffuseColor() const;
	
    //-----------------------------------------------------------------------------------
    /// @brief	Sets the color of the specular light given off by this source
    /// @param	color	The specular color
    /// @remark	Material objects have ambient, diffuse and specular values which indicate
    ///			how much of each type of light an object reflects. This value denotes the
    ///			amount and colour of this type of light the light exudes into the scene.
    ///			The actual appearance of objects is a combination of the two.
    ///			Specular light affects the appearance of shiny highlights on objects, and
    ///			is also dependent on the 'shininess' Material value.
    //-----------------------------------------------------------------------------------
	void setSpecularColor(const Math::Color& color) const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the colour of the specular light given off by this light source
    ///			(see setSpecularColor for more info)
    /// @return	The specular color
    //-----------------------------------------------------------------------------------
	const Math::Color getSpecularColor() const;


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
	Ogre::Light* m_pLight;			///< The Ogre light
};

}
}
}

#endif
