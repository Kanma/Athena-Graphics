/** @file   MeshAnimation.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::MeshAnimation'
*/

// Athena's includes
#include <Athena-Graphics/MeshAnimation.h>


using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace std;


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

MeshAnimation::MeshAnimation(Ogre::AnimationState* pAnimationState)
: m_pAnimationState(pAnimationState)
{
    assert(pAnimationState);
}

//-----------------------------------------------------------------------

MeshAnimation::~MeshAnimation()
{
}
