#include <Athena-Graphics/Visual/VisualComponent.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<VisualComponent>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> VisualComponent_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new VisualComponent(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        VisualComponent* pComponent = static_cast<VisualComponent*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nVisualComponent(name, components_list)\nVisualComponent(<C++ component>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> VisualComponent_GetWorld(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    VisualComponent* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getWorld()));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_VisualComponent(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.VisualComponent");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Entities.Component").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(VisualComponent_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Entities.Component"));

        // Attributes
        AddAttribute(component, "world", VisualComponent_GetWorld, 0);

        pManager->declareClassTemplate("Athena.Graphics.Visual.VisualComponent", component);

        parent->Set(String::New("VisualComponent_TYPE"), String::New(Athena::Graphics::Visual::VisualComponent::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("VisualComponent"), component->GetFunction());
}
