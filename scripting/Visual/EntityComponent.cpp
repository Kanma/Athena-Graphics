#include <Athena-Graphics/Visual/EntityComponent.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<EntityComponent>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> EntityComponent_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new EntityComponent(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        EntityComponent* pComponent = static_cast<EntityComponent*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nEntityComponent(name, components_list)\nEntityComponent(<C++ component>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> EntityComponent_MustCastShadows(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    EntityComponent* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Boolean::New(ptr->mustCastShadows()));
}

//-----------------------------------------------------------------------

void EntityComponent_SetCastShadows(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    EntityComponent* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setCastShadows(value->ToBoolean()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> EntityComponent_IsVisible(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    EntityComponent* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Boolean::New(ptr->isVisible()));
}

//-----------------------------------------------------------------------

void EntityComponent_SetVisible(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    EntityComponent* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setVisible(value->ToBoolean()->Value());
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> EntityComponent_FlipVisibility(const Arguments& args)
{
    HandleScope handle_scope;

    EntityComponent* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->flipVisibility();

    return v8::Handle<v8::Value>();
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_EntityComponent(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(EntityComponent_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.VisualComponent"));

        // Attributes
        AddAttribute(component, "mustCastShadows", EntityComponent_MustCastShadows, EntityComponent_SetCastShadows);
        AddAttribute(component, "visible",         EntityComponent_IsVisible, EntityComponent_SetVisible);

        // Methods
        AddMethod(component, "flipVisibility",     EntityComponent_FlipVisibility);

        pManager->declareClassTemplate("Athena.Graphics.Visual.EntityComponent", component);

        parent->Set(String::New("EntityComponent_TYPE"), String::New(Athena::Graphics::Visual::EntityComponent::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("EntityComponent"), component->GetFunction());
}
