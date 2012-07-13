/** @file	MeshAnimation.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::MeshAnimation'
*/

#ifndef _ATHENA_GRAPHICS_MESHANIMATION_H_
#define _ATHENA_GRAPHICS_MESHANIMATION_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Entities/ComponentAnimation.h>
#include <Ogre/OgreAnimationState.h>


namespace Athena {
namespace Graphics {


//----------------------------------------------------------------------------------------
/// @brief	Contains all the infos about an animation of a mesh
//----------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL MeshAnimation: public Entities::ComponentAnimation
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    /// @param	pAnimationState		The animation state to be used by the mesh animation
    //-----------------------------------------------------------------------------------
	MeshAnimation(Ogre::AnimationState* pAnimationState);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~MeshAnimation();


	//_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
	///	@brief	Gets the Ogre animation state used by this mesh animation
	///	@return	The animation state
    //-----------------------------------------------------------------------------------
	inline Ogre::AnimationState* getAnimationState() const
	{
		return m_pAnimationState;
	}


	//----------------------------------------------------------------------------------
	///	@brief	Gets the Ogre animation state used by this mesh animation
	///	@return	The animation state
	//----------------------------------------------------------------------------------
 	inline const Ogre::String& getAnimationName() const
	{
		return m_pAnimationState->getAnimationName();
	}


	//_____ Implementation of ComponentAnimation __________
public:
    //-----------------------------------------------------------------------------------
	///	@brief	Sets the current time position of this component animation
    //-----------------------------------------------------------------------------------
	virtual void setTimePosition(float fTimePos)
	{
		m_pAnimationState->setTimePosition(fTimePos);
	}

	//-----------------------------------------------------------------------------------
	///	@brief	Returns the current time position of this component animation
    //-----------------------------------------------------------------------------------
	virtual float getTimePosition() const
	{
		return m_pAnimationState->getTimePosition();
	}
	
    //-----------------------------------------------------------------------------------
	///	@brief	Returns the length of this component animation
    //-----------------------------------------------------------------------------------
	virtual float getLength() const
	{
		return m_pAnimationState->getLength();
	}

    //-----------------------------------------------------------------------------------
	///	@brief	Sets the current weight (influence) of this component animation
    //-----------------------------------------------------------------------------------
	virtual void setCurrentWeight(float fWeight)
	{
		m_pAnimationState->setWeight(fWeight);
	}

    //-----------------------------------------------------------------------------------
	///	@brief	Returns the current weight (influence) of this component animation
    //-----------------------------------------------------------------------------------
	virtual float getCurrentWeight() const
	{
		return m_pAnimationState->getWeight();
	}

    //-----------------------------------------------------------------------------------
	///	@brief	Enables/Disables the component animation
    //-----------------------------------------------------------------------------------
	virtual void setEnabled(bool bEnabled)
	{
		m_pAnimationState->setEnabled(bEnabled);
	}

    //-----------------------------------------------------------------------------------
	///	@brief	Sets whether or not the component animation must loops at the start and end
	///         of the animation if the time continues to be altered
    //-----------------------------------------------------------------------------------
	virtual void setLoop(bool bLoop)
	{
		m_pAnimationState->setLoop(bLoop);
	}


	//_____ Attributes __________
private:
	Ogre::AnimationState*	m_pAnimationState;	///< Animation's state
};

}
}

#endif
