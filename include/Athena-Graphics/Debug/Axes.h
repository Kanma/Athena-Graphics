/** @file	Axes.h
	@author	Philip Abbet

	Definition of the class 'Athena::Graphics::Debug::Axes'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_AXES_H_
#define _ATHENA_GRAPHICS_DEBUG_AXES_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Debug/DebugComponent.h>


namespace Athena {
namespace Graphics {
namespace Debug {


//---------------------------------------------------------------------------------------
/// @brief	Debug component that display the local axes of the entity
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Axes: public DebugComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Axes(const std::string& strName, Entities::ComponentsList* pList);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static Axes* create(const std::string& strName, Entities::ComponentsList* pList);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a Axes
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Axes
    //-----------------------------------------------------------------------------------
	static Axes* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Axes();


	//_____ Methods __________
public:
	inline void setScale(float fScale)
	{
		m_fScale = fScale;
	}


	//_____ Implementation of DebugComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Show the local axes of the entity
    //-----------------------------------------------------------------------------------
	virtual void show();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Hide the local axes of the entity
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
	Line3D*	m_pAxes[3];		        ///< The 3D lines used to render the local axes
	float	m_fScale;
};

}
}
}

#endif
