/** @file   module.cpp
    @author Philip Abbet

    Entry point of the Javascript module of Athena::Graphics
*/

#include <v8.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Ogre/OgreCommon.h>
#include <Ogre/OgreFrustum.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;


/*********************************** EXTERNAL FUNCTIONS *********************************/


/*************************************** FUNCTIONS *************************************/

bool bind_enumerations(v8::Handle<Object> parent)
{
    HandleScope handle_scope;

    parent->Set(String::New("VERSION"), String::New("OGRE_VERSION_MAJOR.OGRE_VERSION_MINOR.OGRE_VERSION_PATCH"));

    // PolygonMode
    parent->Set(String::New("PM_POINTS"),    Uint32::New(Ogre::PM_POINTS));
    parent->Set(String::New("PM_WIREFRAME"), Uint32::New(Ogre::PM_WIREFRAME));
    parent->Set(String::New("PM_SOLID"),     Uint32::New(Ogre::PM_SOLID));

    // FrustumPlane
    parent->Set(String::New("FRUSTUM_PLANE_NEAR"),   Uint32::New(Ogre::FRUSTUM_PLANE_NEAR));
    parent->Set(String::New("FRUSTUM_PLANE_FAR"),    Uint32::New(Ogre::FRUSTUM_PLANE_FAR));
    parent->Set(String::New("FRUSTUM_PLANE_LEFT"),   Uint32::New(Ogre::FRUSTUM_PLANE_LEFT));
    parent->Set(String::New("FRUSTUM_PLANE_RIGHT"),  Uint32::New(Ogre::FRUSTUM_PLANE_RIGHT));
    parent->Set(String::New("FRUSTUM_PLANE_TOP"),    Uint32::New(Ogre::FRUSTUM_PLANE_TOP));
    parent->Set(String::New("FRUSTUM_PLANE_BOTTOM"), Uint32::New(Ogre::FRUSTUM_PLANE_BOTTOM));

    // ProjectionType
    parent->Set(String::New("PT_ORTHOGRAPHIC"), Uint32::New(Ogre::PT_ORTHOGRAPHIC));
    parent->Set(String::New("PT_PERSPECTIVE"),  Uint32::New(Ogre::PT_PERSPECTIVE));

    return true;
}


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool MODULE_INITIALISATION_FUNCTION init_module(v8::Handle<Object> parent, const std::string& modulePath)
    {
        HandleScope handle_scope;

        parent->Set(String::New("VERSION"), String::New("OGRE_VERSION_MAJOR.OGRE_VERSION_MINOR.OGRE_VERSION_PATCH"));

        return bind_enumerations(parent);
    }
}
