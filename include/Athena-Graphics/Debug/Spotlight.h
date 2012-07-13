/** @file	Spotlight.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Debug::Spotlight'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_SPOTLIGHT_H_
#define _ATHENA_GRAPHICS_DEBUG_SPOTLIGHT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Debug/DebugComponent.h>


namespace Athena {
namespace Graphics {
namespace Debug {


//---------------------------------------------------------------------------------------
/// @brief	Debug component that display a spotlight symbol
///
/// If a 'spotlight source' is assigned, this component will also displays the cones of the
/// spotlight. If none is supplied, the transforms origin (if any) is used (if it is a
/// spotlight).
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL Spotlight: public DebugComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	Spotlight(const std::string& strName, Entities::ComponentsList* pList);
	
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

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Spotlight();


	//_____ Methods __________
public:
	void setSpotlightSource(Visual::Spotlight* pSource);

	inline Visual::Spotlight* getSpotlightSource() const
	{
		return m_pSpotlightSource;
	}


	//_____ Implementation of DebugComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Show the light symbol
    //-----------------------------------------------------------------------------------
	virtual void show();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Hide the light symbol
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
	static const std::string TYPE;	///< Name of the type of component


	//_____ Attributes __________
protected:
	std::vector<Line3D*>    m_lines;			///< Lines used to represents the light
	Visual::Spotlight*		m_pSpotlightSource;	///< The spotlight source
};

}
}
}

#endif
