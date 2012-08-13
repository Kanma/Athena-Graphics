#include <Athena-Graphics/Debug/Axes.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<Axes>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Axes_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Axes(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Axes* pComponent = static_cast<Axes*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nAxes(name, components_list)\nAxes(<C++ component>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> Axes_GetScale(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Axes* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getScale()));
}

//-----------------------------------------------------------------------

void Axes_SetScale(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Axes* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setScale(value->ToNumber()->Value());
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_Axes(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.Axes");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Axes_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        // Attributes
        AddAttribute(component, "scale", Axes_GetScale, Axes_SetScale);

        pManager->declareClassTemplate("Athena.Graphics.Debug.Axes", component);

        parent->Set(String::New("Axes_TYPE"), String::New(Athena::Graphics::Debug::Axes::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Axes"), component->GetFunction());
}
