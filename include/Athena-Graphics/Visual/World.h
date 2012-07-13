/** @file   World.h
    @author Philip Abbet

    Declaration of the class 'Athena::Graphics::Visual::World'
*/

#ifndef _ATHENA_GRAPHICS_VISUAL_WORLD_H_
#define _ATHENA_GRAPHICS_VISUAL_WORLD_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/VisualComponent.h>
#include <Athena-Entities/ComponentsList.h>
#include <Athena-Core/Signals/SignalsList.h>
#include <Athena-Core/Signals/Declarations.h>
#include <Ogre/OgreSceneManager.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief  Represents the visual world of a scene
///
/// The Ogre Scene Manager is managed by this component.
///
/// There can be only one visual world per scene, and it MUST be a component of the
/// scene itself (not of an entity). Additionally, the name of the world component will
/// always be equal to World::DEFAULT_NAME.
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL World: public VisualComponent
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    /// @param  strName     Name of the component
    //-----------------------------------------------------------------------------------
    World(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief  Create a new component (Component creation method)
    ///
    /// @param  strName Name of the component
    /// @param  pList   List to which the component must be added
    /// @return         The new component
    //-----------------------------------------------------------------------------------
    static World* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief  Cast a component to a World
    ///
    /// @param  pComponent  The component
    /// @return             The component, 0 if it isn't castable to a World
    //-----------------------------------------------------------------------------------
    static World* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~World();


    //_____ Implementation of VisualComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Returns the type of the component
    /// @return The type
    //-----------------------------------------------------------------------------------
    virtual const std::string getType() const { return TYPE; }


    //_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Create an Ogre Scene Manager instance of a given type
    ///
    /// @remarks    You can use this method to create a Scene Manager instance of a given
    ///             specific type. You may know this type already, or you may have
    ///             discovered it by looking at the results from
    ///             Ogre::Root::getMetaDataIterator().
    ///
    /// @param  typeName    String identifying a unique SceneManager type
    /// @return             The Scene Manager, 0 if the type name is unknown
    //-----------------------------------------------------------------------------------
    Ogre::SceneManager* createSceneManager(const std::string& typeName);

    //-----------------------------------------------------------------------------------
    /// @brief  Create an Ogre Scene Manager instance based on scene type support
    ///
    /// @remarks    Creates an instance of a Scene Manager which supports the scene types
    ///             identified in the parameter. If more than one type of Scene Manager
    ///             has been registered as handling that combination of scene types, an
    ///             instance of the last one registered is returned.
    ///
    /// @note       This method always succeeds, if a specific scene manager is not
    ///             found, the default implementation is always returned.
    ///
    /// @param  typeMask    A mask containing one or more SceneType flags
    //-----------------------------------------------------------------------------------
    Ogre::SceneManager* createSceneManager(Ogre::SceneTypeMask typeMask);

    //-----------------------------------------------------------------------------------
    /// @brief  Returns the scene manager
    //-----------------------------------------------------------------------------------
    virtual Ogre::SceneManager* getSceneManager() const
    {
        return m_pSceneManager;
    }

    //-----------------------------------------------------------------------------------
    /// @brief  Sets the ambient light level to be used for the scene
    ///
    /// @param  color   The ambient light color
    ///
    /// @remark This sets the colour and intensity of the ambient light in the scene, i.e.
    ///         the light which is 'sourceless' and illuminates all objects equally.
    ///         The colour of an object is affected by a combination of the light in the
    ///         scene, and the amount of light that object reflects (in this case based
    ///         on the Material::ambient property).
    //-----------------------------------------------------------------------------------
    void setAmbientLight(const Math::Color& color) const;

    //-----------------------------------------------------------------------------------
    /// @brief  Returns ambient light level to be used for the scene
    /// @return The ambient light color
    //-----------------------------------------------------------------------------------
    const Math::Color getAmbientLight() const;


    //_____ Management of the properties __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Returns a list containing the properties of the component
    ///
    /// Used in the serialization mecanism of the components
    /// @remark Must be overriden by each component type. Each implementation must first call
    ///         its base class one, and add a new category (named after the component's type)
    ///         AT THE BEGINNING of the obtained list, containing the properties related to
    ///         this type.
    /// @return The list of properties
    //-----------------------------------------------------------------------------------
    virtual Utils::PropertiesList* getProperties() const;

    //-----------------------------------------------------------------------------------
    /// @brief  Set the value of a property of the component
    ///
    /// Used in the deserialization mecanism of the parts
    /// @param  strCategory     The category of the property
    /// @param  strName         The name of the property
    /// @param  pValue          The value of the property
    /// @return                 'true' if the property was used, 'false' if a required object
    ///                         is missing
    /// @remark Must be overriden by each component type. Each implementation must test if the
    ///         property's category is the one of the component's type, and if so process the
    ///         property's value. Otherwise, it must call its base class implementation.
    //-----------------------------------------------------------------------------------
    virtual bool setProperty(const std::string& strCategory, const std::string& strName,
                             Utils::Variant* pValue);

    //-----------------------------------------------------------------------------------
    /// @brief  Set the value of a property of the component
    ///
    /// Used in the deserialization mecanism of the parts
    /// @param  strName     The name of the property
    /// @param  pValue      The value of the property
    /// @return             'true' if the property was used, 'false' if a required object
    ///                     is missing
    //-----------------------------------------------------------------------------------
    bool setProperty(const std::string& strName, Utils::Variant* pValue);


    //_____ Constants __________
public:
    static const std::string TYPE;  ///< Name of the type of component
    static const std::string DEFAULT_NAME;  ///< Default name of the world


    //_____ Attributes __________
protected:
    Ogre::SceneManager* m_pSceneManager;
};

}
}
}

#endif
