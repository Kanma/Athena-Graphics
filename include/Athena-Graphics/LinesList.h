/** @file	LinesList.h
	@author	Philip Abbet

	Definition of the class 'Athena::Graphics::LinesList'
*/

#ifndef _ATHENA_GRAPHICS_LINESLIST_H_
#define _ATHENA_GRAPHICS_LINESLIST_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreSimpleRenderable.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief	Used to display some unconnected and simple (2 points) 3D-lines
///
/// This implementation is a static one: you should add all the lines first,
/// and then call the drawLines method. Once drawn, a list isn't modifiable anymore.
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL LinesList: public Ogre::SimpleRenderable 
{ 
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	pSceneNode	The scene node to which attach the lines
    //-----------------------------------------------------------------------------------
	LinesList(Ogre::SceneNode* pSceneNode);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
    virtual ~LinesList();

	
	//_____ Operations __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Add a line to the list
    ///
    /// @param	start	The start point
    /// @param	end		The end point
    //-----------------------------------------------------------------------------------
	void addLine(const Math::Vector3& start, const Math::Vector3& end);

    //-----------------------------------------------------------------------------------
    /// @brief	Returns a line of the list
    ///
    /// @param	index	The index of the line
    /// @retval	start	The start point
    /// @retval	end		The end point
    //-----------------------------------------------------------------------------------
    void getLine(unsigned int index, Math::Vector3 &start, Math::Vector3 &end) const;

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the number of lines int the list
    /// @return	The number of lines
    //-----------------------------------------------------------------------------------
	unsigned int getNbLines() const;

    //-----------------------------------------------------------------------------------
    /// @brief	Draw the lines
    ///
    /// @remark	Once drawn, a list of lines can't be modified
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
    /// @brief	Returns the bounding radius of the list of lines
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
	std::vector<Math::Vector3>	m_points;	///< The list of the points that compose the lines (always a start/end pair)
	bool						m_bDrawn;	///< Indicates if the lines were drawn
}; 

}
}

#endif
