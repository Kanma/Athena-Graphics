#include <Athena-Graphics/Visual/DirectionalLight.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Math/Scripting.h>
#include <v8.h>

using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace Athena::Math;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<Visual::DirectionalLight>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> DirectionalLight_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::DirectionalLight(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::DirectionalLight* pComponent = static_cast<Visual::DirectionalLight*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nDirectionalLight(name, components_list)\nDirectionalLight(<C++ light>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> DirectionalLight_GetDiffuseColor(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::DirectionalLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getDiffuseColor()));
}

//-----------------------------------------------------------------------

void DirectionalLight_SetDiffuseColor(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::DirectionalLight* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setDiffuseColor(fromJSColor(value));
}

//-----------------------------------------------------------------------

v8::Handle<Value> DirectionalLight_GetSpecularColor(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::DirectionalLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getSpecularColor()));
}

//-----------------------------------------------------------------------

void DirectionalLight_SetSpecularColor(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::DirectionalLight* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setSpecularColor(fromJSColor(value));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_DirectionalLight(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.DirectionalLight");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(DirectionalLight_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent"));

        // Attributes
        AddAttribute(component, "diffuseColor",  DirectionalLight_GetDiffuseColor, DirectionalLight_SetDiffuseColor);
        AddAttribute(component, "specularColor", DirectionalLight_GetSpecularColor, DirectionalLight_SetSpecularColor);

        pManager->declareClassTemplate("Athena.Graphics.Visual.DirectionalLight", component);

        parent->Set(String::New("DirectionalLight_TYPE"), String::New(Athena::Graphics::Visual::DirectionalLight::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("DirectionalLight"), component->GetFunction());
}
