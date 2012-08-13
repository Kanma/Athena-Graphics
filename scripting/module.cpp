/** @file   module.cpp
    @author Philip Abbet

    Entry point of the Javascript module of Athena::Graphics
*/

#include <v8.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreCommon.h>
#include <Ogre/OgreFrustum.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;
using namespace Athena::Graphics;


/*********************************** EXTERNAL FUNCTIONS *********************************/

extern bool bind_Debug_Axes(v8::Handle<Object> parent);
extern bool bind_Debug_Camera(v8::Handle<Object> parent);
extern bool bind_Debug_DebugComponent(v8::Handle<Object> parent);
extern bool bind_Debug_DirectionalLight(v8::Handle<Object> parent);
extern bool bind_Debug_PointLight(v8::Handle<Object> parent);

extern bool bind_Visual_Camera(v8::Handle<Object> parent);
extern bool bind_Visual_DirectionalLight(v8::Handle<Object> parent);
extern bool bind_Visual_EntityComponent(v8::Handle<Object> parent);
extern bool bind_Visual_Object(v8::Handle<Object> parent);
extern bool bind_Visual_Plane(v8::Handle<Object> parent);
extern bool bind_Visual_PointLight(v8::Handle<Object> parent);
extern bool bind_Visual_Spotlight(v8::Handle<Object> parent);
extern bool bind_Visual_VisualComponent(v8::Handle<Object> parent);
extern bool bind_Visual_World(v8::Handle<Object> parent);


/*************************************** FUNCTIONS *************************************/

bool init_ogre_module(v8::Handle<Object> globals)
{
    HandleScope handle_scope;

    v8::Handle<Object> ns = Object::New();
    globals->Set(String::New("Ogre"), ns);

    ns->Set(String::New("VERSION"), String::New("OGRE_VERSION_MAJOR.OGRE_VERSION_MINOR.OGRE_VERSION_PATCH"));

    // PolygonMode
    ns->Set(String::New("PM_POINTS"),    Uint32::New(Ogre::PM_POINTS));
    ns->Set(String::New("PM_WIREFRAME"), Uint32::New(Ogre::PM_WIREFRAME));
    ns->Set(String::New("PM_SOLID"),     Uint32::New(Ogre::PM_SOLID));

    // FrustumPlane
    ns->Set(String::New("FRUSTUM_PLANE_NEAR"),   Uint32::New(Ogre::FRUSTUM_PLANE_NEAR));
    ns->Set(String::New("FRUSTUM_PLANE_FAR"),    Uint32::New(Ogre::FRUSTUM_PLANE_FAR));
    ns->Set(String::New("FRUSTUM_PLANE_LEFT"),   Uint32::New(Ogre::FRUSTUM_PLANE_LEFT));
    ns->Set(String::New("FRUSTUM_PLANE_RIGHT"),  Uint32::New(Ogre::FRUSTUM_PLANE_RIGHT));
    ns->Set(String::New("FRUSTUM_PLANE_TOP"),    Uint32::New(Ogre::FRUSTUM_PLANE_TOP));
    ns->Set(String::New("FRUSTUM_PLANE_BOTTOM"), Uint32::New(Ogre::FRUSTUM_PLANE_BOTTOM));

    // ProjectionType
    ns->Set(String::New("PT_ORTHOGRAPHIC"), Uint32::New(Ogre::PT_ORTHOGRAPHIC));
    ns->Set(String::New("PT_PERSPECTIVE"),  Uint32::New(Ogre::PT_PERSPECTIVE));

    return true;
}


bool init_debug_submodule(v8::Handle<Object> parent, const std::string& modulePath)
{
    HandleScope handle_scope;

    v8::Handle<Object> ns = Object::New();
    parent->Set(String::New("Debug"), ns);

    return bind_Debug_DebugComponent(ns) &&
           bind_Debug_Axes(ns) &&
           bind_Debug_Camera(ns) &&
           bind_Debug_DirectionalLight(ns) &&
           bind_Debug_PointLight(ns);
}


bool init_visual_submodule(v8::Handle<Object> parent, const std::string& modulePath)
{
    HandleScope handle_scope;

    v8::Handle<Object> ns = Object::New();
    parent->Set(String::New("Visual"), ns);

    return bind_Visual_VisualComponent(ns) &&
           bind_Visual_EntityComponent(ns) &&
           bind_Visual_Camera(ns) &&
           bind_Visual_DirectionalLight(ns) &&
           bind_Visual_Object(ns) &&
           bind_Visual_Plane(ns) &&
           bind_Visual_PointLight(ns) &&
           bind_Visual_Spotlight(ns) &&
           bind_Visual_World(ns);
}


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool MODULE_INITIALISATION_FUNCTION init_module(v8::Handle<Object> parent, const std::string& modulePath)
    {
        HandleScope handle_scope;

        v8::Handle<Context> context = parent->CreationContext();
        v8::Handle<Object> ns = context->Global()->Get(String::New("Athena"))->ToObject();

        if (ns->Get(String::New("Math"))->IsUndefined())
            ScriptingManager::getSingletonPtr()->import("Athena.Math", Context::GetCurrent());

        if (ns->Get(String::New("Core"))->IsUndefined())
            ScriptingManager::getSingletonPtr()->import("Athena.Core", Context::GetCurrent());

        if (ns->Get(String::New("Entities"))->IsUndefined())
            ScriptingManager::getSingletonPtr()->import("Athena.Entities", Context::GetCurrent());

        parent->Set(String::New("VERSION"), String::New(Athena::Graphics::VERSION));

        return init_ogre_module(context->Global()) &&
               init_debug_submodule(parent, modulePath) &&
               init_visual_submodule(parent, modulePath);
    }
}
