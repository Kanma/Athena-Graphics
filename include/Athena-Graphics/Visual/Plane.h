/** @file   Plane.h
    @author Philip Abbet

    Declaration of the class 'Athena::Graphics::Visual::Plane'
*/

#ifndef _ATHENA_GRAPHICS_PLANE_H_
#define _ATHENA_GRAPHICS_PLANE_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Athena-Math/Vector3.h>
#include <Ogre/OgreEntity.h>


namespace Athena {
namespace Graphics {
namespace Visual {


//---------------------------------------------------------------------------------------
/// @brief  A visual component that manages a plane
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL Plane: public EntityComponent
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    /// @param  strName     Name of the component
    //-----------------------------------------------------------------------------------
    Plane(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief  Create a new component (Component creation method)
    ///
    /// @param  strName Name of the component
    /// @param  pList   List to which the component must be added
    /// @return         The new component
    //-----------------------------------------------------------------------------------
    static Plane* create(const std::string& strName, Entities::ComponentsList* pList);

    //-----------------------------------------------------------------------------------
    /// @brief  Cast a component to a Plane
    ///
    /// @param  pComponent  The component
    /// @return             The component, 0 if it isn't castable to a Plane
    //-----------------------------------------------------------------------------------
    static Plane* cast(Entities::Component* pComponent);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~Plane();


    //_____ Implementation of EntityComponent __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Returns the type of the component
    /// @return The type
    //-----------------------------------------------------------------------------------
    virtual const std::string getType() const
    {
        return TYPE;
    }


    //_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Returns the Ogre entity used by this component
    /// @return The Ogre entity
    //-----------------------------------------------------------------------------------
    inline Ogre::Entity* getOgreEntity()
    {
        return m_pEntity;
    }


    //-----------------------------------------------------------------------------------
    /// @brief  Setup the plane
    ///
    /// @param  strMaterial     Material to use
    /// @param  normalVector    Orientation of the plane
    /// @param  distance        Distance from the origin
    /// @param  width           The width of the plane in world coordinates
    /// @param  height          The height of the plane in world coordinates
    /// @param  xSegments       The number of segments of the plane in the x direction
    /// @param  ySegments       The number of segments of the plane in the y direction
    /// @param  bNormals        If true, normals are created perpendicular to the plane
    /// @param  iNbTexCoordSet  The number of 2D texture coordinate sets created - by
    ///                         default the corners are created to be the corner of the
    ///                         texture.
    /// @param  uTile           The number of times the texture should be repeated in the
    ///                         u direction
    /// @param  vTile           The number of times the texture should be repeated in the
    ///                         v direction
    /// @param  upVector        The 'Up' direction of the plane
    /// @return                 'true' if successful
    //-----------------------------------------------------------------------------------
    bool createPlane(const std::string& strMaterial, const Math::Vector3& normalVector,
                     Math::Real distance, Math::Real width, Math::Real height,
                     int xSegments = 1, int ySegments = 1, bool bNormals = true,
                     int iNbTexCoordSet = 1, Math::Real uTile = 1.0f, Math::Real vTile = 1.0f,
                     const Math::Vector3& upVector = Math::Vector3::UNIT_Y);

protected:
    //-----------------------------------------------------------------------------------
    /// @brief  Create the plane from the values of the attributes
    /// @return 'true' if successful
    //-----------------------------------------------------------------------------------
    bool createPlane();



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


    //_____ Attributes __________
protected:
    Ogre::Entity*   m_pEntity;
    std::string     m_strMaterial;
    Math::Vector3   m_normalVector;
    Math::Real      m_distance;
    Math::Real      m_width;
    Math::Real      m_height;
    int             m_xSegments;
    int             m_ySegments;
    bool            m_bNormals;
    int             m_iNbTexCoordSet;
    Math::Real      m_uTile;
    Math::Real      m_vTile;
    Math::Vector3   m_upVector;
};

}
}
}

#endif
