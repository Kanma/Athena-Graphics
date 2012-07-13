/** @file	DebugComponent.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Debug::DebugComponent'
*/

#ifndef _ATHENA_GRAPHICS_DEBUG_DEBUGCOMPONENT_H_
#define _ATHENA_GRAPHICS_DEBUG_DEBUGCOMPONENT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/World.h>
#include <Athena-Entities/ComponentsList.h>
#include <Athena-Entities/Entity.h>
#include <Athena-Entities/Scene.h>
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
class ATHENA_GRAPHICS_SYMBOL DebugComponent: public Entities::Component
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	DebugComponent(const std::string& strName, Entities::ComponentsList* pList);

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

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~DebugComponent();


	//_____ Implementation of Component __________
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

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the transforms affecting this component have changed
	///
	/// Can be called when the component isn't affected by any transforms anymore
	/// (getTransforms() returns 0).
	//-----------------------------------------------------------------------------------
	virtual void onTransformsChanged();

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the visual world of the scene
	//-----------------------------------------------------------------------------------
	inline Visual::World* getWorld() const
	{
	    if (m_pList->getScene())
            return dynamic_cast<Visual::World*>(m_pList->getScene()->getMainComponent(Entities::COMP_VISUAL));
	    else if (m_pList->getEntity())
            return dynamic_cast<Visual::World*>(m_pList->getEntity()->getScene()->getMainComponent(Entities::COMP_VISUAL));
	
        return 0;
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the scene node used by the component
	/// @return	The scene node
	//-----------------------------------------------------------------------------------
	inline Ogre::SceneManager* getSceneManager() const
	{
        Visual::World* pWorld = getWorld();
        if (pWorld)
            return pWorld->getSceneManager();
        
        return 0;
	}


	//_____ Slots __________
protected:
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
