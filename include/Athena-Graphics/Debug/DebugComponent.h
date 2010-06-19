/** @file	DebugComponent.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Debug::DebugComponent'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_DEBUGCOMPONENT_H_
#define _ATHENA_GRAPHICS_DEBUG_DEBUGCOMPONENT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Entities/ComponentsList.h>
#include <Athena-Entities/Entity.h>
#include <Athena-Core/Signals/SignalsList.h>
#include <Athena-Core/Signals/Declarations.h>
#include <Ogre/OgreMovableObject.h>
#include <Ogre/OgreSceneNode.h>


namespace Athena {
namespace Graphics {
namespace Debug {


//---------------------------------------------------------------------------------------
/// @brief	Base class for all the debug components of an entity
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL DebugComponent: public Entities::Component
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	DebugComponent(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~DebugComponent();

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static DebugComponent* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a DebugComponent
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a DebugComponent
    //-----------------------------------------------------------------------------------
	static DebugComponent* cast(Entities::Component* pComponent);


	//_____ Implementation of CRepresentationPart __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the type of the component
	/// @return	The type
	//-----------------------------------------------------------------------------------
	virtual const std::string getType() const { return TYPE; }


	//_____ Methods __________
public:
	virtual void show() {};
	virtual void hide() {};


	//_____ Slots __________
protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Called when the parent transforms of the component is changed
    ///
    /// @param	pValue	 Contains the ID of the new parent transforms
    ///
    /// @remark	When this method is called, the previous transforms is still available
    //-----------------------------------------------------------------------------------
	void onParentTransformsChanged(Utils::Variant* pValue);

    //-----------------------------------------------------------------------------------
    /// @brief	Called when the transforms to apply to the component have changed
    ///
    /// @param	pValue	 Not used
    //-----------------------------------------------------------------------------------
	void onTransformsChanged(Utils::Variant* pValue = 0);

	void onSceneShown(Utils::Variant* pValue);
	void onSceneHidden(Utils::Variant* pValue);
	void onEntityEnabled(Utils::Variant* pValue);
	void onEntityDisabled(Utils::Variant* pValue);
	

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
	static const std::string TYPE;		///< Name of the type of component


	//_____ Attributes __________
protected:
	Ogre::SceneNode* m_pSceneNode;
};

}
}
}

#endif
