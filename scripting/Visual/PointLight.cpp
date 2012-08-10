#include <Athena-Graphics/Visual/PointLight.h>
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

#define GetPtr(HANDLE) GetObjectPtr<Visual::PointLight>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> PointLight_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::PointLight(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::PointLight* pComponent = static_cast<Visual::PointLight*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nPointLight(name, components_list)\nPointLight(<C++ light>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> PointLight_GetAttenuationRange(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::PointLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getAttenuationRange()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> PointLight_GetAttenuationConstant(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::PointLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getAttenuationConstant()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> PointLight_GetAttenuationLinear(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::PointLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getAttenuationLinear()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> PointLight_GetAttenuationQuadric(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::PointLight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getAttenuationQuadric()));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> PointLight_SetAttenuation(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 4) && args[0]->IsNumber() && args[1]->IsNumber() &&
        args[2]->IsNumber() && args[3]->IsNumber())
    {
        Visual::PointLight* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->setAttenuation(args[0]->ToNumber()->Value(), args[1]->ToNumber()->Value(),
                            args[2]->ToNumber()->Value(), args[3]->ToNumber()->Value());

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nsetAttenuation(range, constant, linear, quadratic)"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_PointLight(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.PointLight");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.DirectionalLight").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(PointLight_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.DirectionalLight"));

        // Attributes
        AddAttribute(component, "attenuationRange",    PointLight_GetAttenuationRange, 0);
        AddAttribute(component, "attenuationConstant", PointLight_GetAttenuationConstant, 0);
        AddAttribute(component, "attenuationLinear",   PointLight_GetAttenuationLinear, 0);
        AddAttribute(component, "attenuationQuadric",  PointLight_GetAttenuationQuadric, 0);

        // Methods
        AddMethod(component, "setAttenuation", PointLight_SetAttenuation);

        pManager->declareClassTemplate("Athena.Graphics.Visual.PointLight", component);

        parent->Set(String::New("PointLight_TYPE"), String::New(Athena::Graphics::Visual::PointLight::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("PointLight"), component->GetFunction());
}
