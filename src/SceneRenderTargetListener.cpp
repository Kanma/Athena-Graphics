/**	@file	SceneRenderTargetListener.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Graphics::SceneRenderTargetListener'
*/

#include <Athena-Graphics/SceneRenderTargetListener.h>
#include <Athena-Entities/Scene.h>
#include <Ogre/OgreRenderTarget.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace std;


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

SceneRenderTargetListener::SceneRenderTargetListener(Ogre::RenderTarget* pRenderTarget,
													 Scene* pScene)
: m_pRenderTarget(pRenderTarget), m_pScene(pScene)
{
	assert(m_pRenderTarget);
	assert(m_pScene);

	m_pRenderTarget->addListener(this);
}

//-----------------------------------------------------------------------

SceneRenderTargetListener::~SceneRenderTargetListener()
{
	m_pRenderTarget->removeListener(this);
}


/************************************* OPERATIONS **************************************/

void SceneRenderTargetListener::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) 
{
	m_pScene->show();
}

//-----------------------------------------------------------------------

void SceneRenderTargetListener::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) 
{
	m_pScene->hide();
}
