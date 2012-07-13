/** @file	PointLight.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::PointLight'
*/

#ifndef _ATHENA_GRAPHICS_POINTLIGHT_H_
#define _ATHENA_GRAPHICS_POINTLIGHT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/DirectionalLight.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	A visual component that manages a point light
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL PointLight: public DirectionalLight
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
    PointLight(const std::string& strName, Entities::ComponentsList* pList);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static PointLight* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a PointLight
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a PointLight
    //-----------------------------------------------------------------------------------
	static PointLight* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~PointLight();


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
    /// @brief	Sets the attenuation parameters of the light source ie how it diminishes
    ///			with distance
    /// @remark	Lights normally get fainter the further they are away. Also, each light
    ///			is given a maximum range beyond which it cannot affect any objects.
    ///			Light attentuation is not applicable to directional lights since they
    ///			have an infinite range and constant intensity.
    ///			This follows a standard attenuation approach - see any good 3D text for
    ///			the details of what they mean.
    /// @param	range		The absolute upper range of the light in world units  
    /// @param	constant	The constant factor in the attenuation formula: 1.0 means
    ///						never attenuate, 0.0 is complete attenuation  
    /// @param	linear		The linear factor in the attenuation formula: 1 means
    ///						attenuate evenly over the distance  
    /// @param	quadratic	The quadratic factor in the attenuation formula: adds a
    ///						curvature to the attenuation formula
    //-----------------------------------------------------------------------------------
	void setAttenuation(Math::Real range, Math::Real constant, Math::Real linear,
					    Math::Real quadratic);

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the absolute upper range of the light
    /// @return	The range
    //-----------------------------------------------------------------------------------
	Math::Real getAttenuationRange() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the constant factor in the attenuation formula
    /// @return	The constant factor
    //-----------------------------------------------------------------------------------
	Math::Real getAttenuationConstant() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the linear factor in the attenuation formula
    /// @return	The linear factor
    //-----------------------------------------------------------------------------------
	Math::Real getAttenuationLinear() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the quadric factor in the attenuation formula
    /// @return	The quadric factor
    //-----------------------------------------------------------------------------------
	Math::Real getAttenuationQuadric() const;


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
};

}
}
}

#endif
