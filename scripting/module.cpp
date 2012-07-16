/** @file   module.cpp
    @author Philip Abbet

    Entry point of the Javascript module of Athena::Graphics
*/

#include <v8.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Graphics/Prerequisites.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;
using namespace Athena::Graphics;


/*********************************** EXTERNAL FUNCTIONS *********************************/

extern bool bind_Visual_VisualComponent(v8::Handle<Object> parent);
extern bool bind_Visual_World(v8::Handle<Object> parent);


/*************************************** FUNCTIONS *************************************/

bool init_visual_submodule(v8::Handle<Object> parent, const std::string& modulePath)
{
    HandleScope handle_scope;

    v8::Handle<Object> ns = Object::New();
    parent->Set(String::New("Visual"), ns);

    return bind_Visual_VisualComponent(ns) &&
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

        return init_visual_submodule(parent, modulePath);
    }
}
