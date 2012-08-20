#include <Athena-Graphics/Debug/DebugComponent.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<DebugComponent>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> DebugComponent_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new DebugComponent(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        DebugComponent* pComponent = static_cast<DebugComponent*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nDebugComponent(name, components_list)\nDebugComponent(<C++ component>)"));
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> DebugComponent_GetWorld(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    DebugComponent* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getWorld()));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> DebugComponent_Show(const Arguments& args)
{
    HandleScope handle_scope;

    DebugComponent* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->show();

    return v8::Handle<v8::Value>();
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> DebugComponent_Hide(const Arguments& args)
{
    HandleScope handle_scope;

    DebugComponent* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->hide();

    return v8::Handle<v8::Value>();
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_DebugComponent(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Entities.Component").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(DebugComponent_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Entities.Component"));

        // Attributes
        AddAttribute(component, "world", DebugComponent_GetWorld, 0);

        // Methods
        AddMethod(component, "show", DebugComponent_Show);
        AddMethod(component, "hide", DebugComponent_Hide);

        pManager->declareClassTemplate("Athena.Graphics.Debug.DebugComponent", component);

        parent->Set(String::New("DebugComponent_TYPE"), String::New(Athena::Graphics::Debug::DebugComponent::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("DebugComponent"), component->GetFunction());
}
