/** @file	VisualComponent.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Visual::VisualComponent'
*/

#ifndef _ATHENA_GRAPHICS_VISUALCOMPONENT_H_
#define _ATHENA_GRAPHICS_VISUALCOMPONENT_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Entities/ComponentsList.h>
#include <Athena-Entities/Entity.h>
#include <Athena-Core/Signals/SignalsList.h>
#include <Athena-Core/Signals/Declarations.h>
#include <Ogre/OgreMovableObject.h>
#include <Ogre/OgreSceneNode.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief	Base class for all the visual components of an entity
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL VisualComponent: public Entities::Component
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	strName		Name of the component
    //-----------------------------------------------------------------------------------
	VisualComponent(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~VisualComponent();

    //-----------------------------------------------------------------------------------
    /// @brief	Create a new component (Component creation method)
    ///
    /// @param	strName	Name of the component
    /// @param	pList	List to which the component must be added
    /// @return			The new component
    //-----------------------------------------------------------------------------------
	static VisualComponent* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief	Cast a component to a VisualComponent
    ///
    /// @param	pComponent	The component
    /// @return				The component, 0 if it isn't castable to a VisualComponent
    //-----------------------------------------------------------------------------------
	static VisualComponent* cast(Entities::Component* pComponent);


	//_____ Implementation of CComponent __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Returns the type of the component
	/// @return	The type
	//-----------------------------------------------------------------------------------
	virtual const std::string getType() const { return TYPE; }


	//_____ Methods __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Set if the movable object of the visual component (if any) must cast
	///         shadows
	///
	/// @param	bCastShadows	Indicates if the movable object must cast shadows
	//-----------------------------------------------------------------------------------
	void setCastShadows(bool bCastShadows);

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates if the movable object of the visual component (if any)  must cast
	///			shadows
	///
	/// @return	'true' if this movable object must cast shadows
	//-----------------------------------------------------------------------------------
	inline bool mustCastShadows() const
	{
		return m_bCastShadows;
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Returns the scene node used by the component
	/// @return	The scene node
	//-----------------------------------------------------------------------------------
	virtual Ogre::SceneNode* getSceneNode() const
	{
		return m_pSceneNode;
	}

protected:
	void attachObject(Ogre::MovableObject* pObject);

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the transforms affecting this component have changed
	///
	/// Can be called when the component isn't affected by any transforms anymore
	/// (getTransforms() returns 0).
	//-----------------------------------------------------------------------------------
	virtual void onTransformsChanged();


	//_____ Visibility __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Makes all objects attached to this component become visible / invisible
	/// @remark	This is a shortcut to calling setVisible() on the objects attached to this
	///			component
	/// @param	bVisible	Whether the objects are to be made visible or invisible
	//-----------------------------------------------------------------------------------
	inline void setVisible(bool bVisible)
	{
		m_pSceneNode->setVisible(bVisible, false);
		m_bVisible = bVisible;
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Inverts the visibility of all objects attached to this component
	/// @remark	This is a shortcut to calling setVisible(!isVisible()) on the objects
	///			attached to this component
	//-----------------------------------------------------------------------------------
	void flipVisibility()
	{
		setVisible(!m_bVisible);
	}

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates if the component is visible or hidden
	/// @return	'true' if the component is visible
	//-----------------------------------------------------------------------------------
	inline bool isVisible() const
	{
		return m_bVisible;
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
	bool				m_bVisible;
	bool				m_bCastShadows;
	Ogre::SceneNode*	m_pSceneNode;
};

}
}
}

#endif
