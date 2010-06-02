/** @file	Line3D.h
	@author	Trep (of the Ogre forum)
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::Line3D'
*/

#ifndef _ATHENA_GRAPHICS_LINE3D_H_
#define _ATHENA_GRAPHICS_LINE3D_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreSimpleRenderable.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief	Used to display a 3D-line
///
/// This implementation is a static one: you should add all the points of the line first,
/// and then call the drawLines() method. Once drawn, a line isn't modifiable anymore.
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Line3D: public Ogre::SimpleRenderable 
{ 
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	pSceneNode	The scene node to which attach the line
    //-----------------------------------------------------------------------------------
	Line3D(Ogre::SceneNode* pSceneNode);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
    virtual ~Line3D();

	
	//_____ Operations __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Add a point to the line
    ///
    /// @param	p	The point
    //-----------------------------------------------------------------------------------
	void addPoint(const Math::Vector3& p);

    //-----------------------------------------------------------------------------------
    /// @brief	Returns a point a the line
    ///
    /// @param	index	The index of the point
    /// @return			The point
    //-----------------------------------------------------------------------------------
	const Math::Vector3& getPoint(unsigned int index) const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the number of points of the line
    /// @return	The number of points
    //-----------------------------------------------------------------------------------
	unsigned int getNbPoints() const;
	
    //-----------------------------------------------------------------------------------
    /// @brief	Modify a point of the line
    ///
    /// @param	index	The index of the point
    /// @param	value	The new point
    //-----------------------------------------------------------------------------------
	void updatePoint(unsigned int index, const Math::Vector3& value);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Draw a line from a point to another one
    ///
    /// @remark	Once drawn, a line can't be modified
    /// @param	start	Start point
    /// @param	end		End point
    //-----------------------------------------------------------------------------------
	void drawLine(const Math::Vector3& start, const Math::Vector3& end);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Draw the line(s)
    ///
    /// @remark	Once drawn, a line can't be modified
    //-----------------------------------------------------------------------------------
	void drawLines(); 


	//_____ Overrides for SimpleRenderable __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Returns the camera-relative squared depth of this renderable
    /// @param	pCamera	The camera
    /// @return			The camera-relative squared depth
    //-----------------------------------------------------------------------------------
	Ogre::Real getSquaredViewDepth(const Ogre::Camera* pCamera) const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the bounding radius of the line
    /// @return	The bounding radius
    //-----------------------------------------------------------------------------------
	Ogre::Real getBoundingRadius() const;

protected:
    //-----------------------------------------------------------------------------------
    /// @brief	Returns the world orientation
    /// @remark	Returns always the identity quaternion
    /// @return	The world orientation
    //-----------------------------------------------------------------------------------
    const Ogre::Quaternion& getWorldOrientation() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the world position
    /// @remark	Returns always a zero vector
    /// @return	The world position
    //-----------------------------------------------------------------------------------
    const Ogre::Vector3& getWorldPosition() const;


	//_____ Attributes __________
private:
	std::vector<Math::Vector3>	m_points;	///< The list of the points that compose the line
	bool						m_bDrawn;	///< Indicates if the line was drawn
}; 

}
}

#endif
