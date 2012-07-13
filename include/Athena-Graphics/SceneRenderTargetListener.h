/** @file	SceneRenderTargetListener.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Graphics::SceneRenderTargetListener'
*/

#ifndef _ATHENA_GRAPHICS_SCENERENDERTARGETLISTENER_H_
#define _ATHENA_GRAPHICS_SCENERENDERTARGETLISTENER_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreRenderTargetListener.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief	Represents a RenderTargetListener specialized in the managment of a Scene in
///			only one RenderTarget
///
/// The purpose of this class is to manage the visibility of a scene in an application
/// that uses more than one RenderTarget, and where only one RenderTarget must display
/// the scene.
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL SceneRenderTargetListener: public Ogre::RenderTargetListener
{ 
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    ///
    /// @param  pRenderTarget   The render target
    /// @param  pScene          The scene that must be shown in the render target
    //-----------------------------------------------------------------------------------
	SceneRenderTargetListener(Ogre::RenderTarget* pRenderTarget, Entities::Scene* pScene);

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~SceneRenderTargetListener();

	
	//_____ Overrides for SimpleRenderable __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Called just before the RenderTarget is about to be rendered into
    ///
    /// @param	evt	Event
    //-----------------------------------------------------------------------------------
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

    //-----------------------------------------------------------------------------------
    /// @brief	Called just after the RenderTarget has been rendered to
    ///
    /// @param	evt	Event
    //-----------------------------------------------------------------------------------
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);


	//_____ Attributes __________
private:
	Ogre::RenderTarget*	m_pRenderTarget;	///< The RenderTarget which must render the scene
	Entities::Scene*	m_pScene;			///< The scene
}; 

}
}

#endif
