#include <Athena-Graphics/Visual/Spotlight.h>
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

#define GetPtr(HANDLE) GetObjectPtr<Visual::Spotlight>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Spotlight_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::Spotlight(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::Spotlight* pComponent = static_cast<Visual::Spotlight*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nSpotlight(name, components_list)\nSpotlight(<C++ light>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> Spotlight_GetInnerAngle(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Spotlight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getInnerAngle().valueRadians()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> Spotlight_GetOuterAngle(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Spotlight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getOuterAngle().valueRadians()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> Spotlight_GetFalloff(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Spotlight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getFalloff()));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> Spotlight_SetRange(const Arguments& args)
{
    HandleScope handle_scope;

    if (((args.Length() == 2) || (args.Length() == 3)) && args[0]->IsNumber() && args[1]->IsNumber())
    {
        Visual::Spotlight* ptr = GetPtr(args.This());
        assert(ptr);

        Real falloff = 1.0f;
        if ((args.Length() == 3) && args[2]->IsNumber())
            falloff = args[2]->ToNumber()->Value();

        ptr->setRange(Radian(args[0]->ToNumber()->Value()),
                      Radian(args[1]->ToNumber()->Value()),
                      falloff);

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nsetRange(innerAngle, outerAngle [, falloff])"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_Spotlight(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.Spotlight");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.PointLight").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Spotlight_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.PointLight"));

        // Attributes
        AddAttribute(component, "innerAngle",   Spotlight_GetInnerAngle, 0);
        AddAttribute(component, "outerAngle",   Spotlight_GetOuterAngle, 0);
        AddAttribute(component, "falloff",      Spotlight_GetFalloff, 0);

        // Methods
        AddMethod(component, "setRange", Spotlight_SetRange);

        pManager->declareClassTemplate("Athena.Graphics.Visual.Spotlight", component);

        parent->Set(String::New("Spotlight_TYPE"), String::New(Athena::Graphics::Visual::Spotlight::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Spotlight"), component->GetFunction());
}
