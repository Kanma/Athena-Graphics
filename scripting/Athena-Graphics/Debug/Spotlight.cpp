#include <Athena-Graphics/Debug/Spotlight.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<Spotlight>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Debug_Spotlight_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Spotlight(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Spotlight* pComponent = static_cast<Spotlight*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nSpotlight(name, components_list)\nSpotlight(<C++ component>)"));
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> Spotlight_GetSpotlightSource(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Spotlight* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getSpotlightSource()));
}

//-----------------------------------------------------------------------

void Spotlight_SetSpotlightSource(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Spotlight* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setSpotlightSource(Visual::fromJSSpotlight(value));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_Spotlight(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.Spotlight");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Debug_Spotlight_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        // Attributes
        AddAttribute(component, "spotlightSource", Spotlight_GetSpotlightSource, Spotlight_SetSpotlightSource);

        pManager->declareClassTemplate("Athena.Graphics.Debug.Spotlight", component);

        parent->Set(String::New("Spotlight_TYPE"), String::New(Athena::Graphics::Debug::Spotlight::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Spotlight"), component->GetFunction());
}
