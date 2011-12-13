/** @file	AudioSource.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Debug::AudioSource'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_AUDIOSOURCE_H_
#define _ATHENA_GRAPHICS_DEBUG_AUDIOSOURCE_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Debug/DebugComponent.h>


namespace Athena {
namespace Graphics {
namespace Debug {


//---------------------------------------------------------------------------------------
/// @brief	Debug component that display an audio source symbol
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL AudioSource: public DebugComponent
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	AudioSource(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static AudioSource* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to an AudioSource
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a Camera
    //-----------------------------------------------------------------------------------
	static AudioSource* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~AudioSource();


	//_____ Implementation of CDebugComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Show the audio source symbol
    //-----------------------------------------------------------------------------------
	virtual void show();

    //-----------------------------------------------------------------------------------
    /// @brief	Hide the audio source symbol
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


	//_____ Constants __________
public:
	static const std::string TYPE;	///< Name of the type of component


	//_____ Attributes __________
protected:
	std::vector<Line3D*> m_lines;	///< Lines used to represents the source
};

}
}
}

#endif
