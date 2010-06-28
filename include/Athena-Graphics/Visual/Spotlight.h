/** @file	Athena_Graphics_Spotlight.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::Spotlight'
*/

#ifndef _ATHENA_GRAPHICS_SPOTLIGHT_H_
#define _ATHENA_GRAPHICS_SPOTLIGHT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/PointLight.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	A visual component that manages a spotlight
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Spotlight: public PointLight
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Spotlight(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Spotlight();

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static Spotlight* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a Spotlight
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Spotlight
    //-----------------------------------------------------------------------------------
	static Spotlight* cast(Entities::Component* pComponent);


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
    /// @brief	Sets the range of a spotlight, i.e. the angle of the inner and outer
    ///			cones and the rate of falloff between them
    /// @param	innerAngle	Angle covered by the bright inner cone  
    /// @param	outerAngle	Angle covered by the outer cone  
    /// @param	falloff		The rate of falloff between the inner and outer cones. 1.0
    ///						means a linear falloff, less means slower falloff, higher
    ///						means faster falloff. 
    //-----------------------------------------------------------------------------------
	void setRange(const Math::Radian &innerAngle, const Math::Radian &outerAngle,
				  Math::Real falloff = 1.0);

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the angle covered by the spotlights inner cone
    /// @return	The angle
    //-----------------------------------------------------------------------------------
	const Math::Radian getInnerAngle() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the angle covered by the spotlights outer cone
    /// @return	The angle
    //-----------------------------------------------------------------------------------
	const Math::Radian getOuterAngle() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the falloff between the inner and outer cones of the spotlight
    /// @return	The fallof
    //-----------------------------------------------------------------------------------
	Math::Real getFalloff() const;


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
