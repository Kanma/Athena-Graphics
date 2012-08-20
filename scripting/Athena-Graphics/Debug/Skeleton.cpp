#include <Athena-Graphics/Debug/Skeleton.h>
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

#define GetPtr(HANDLE) GetObjectPtr<Skeleton>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Debug_Skeleton_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Skeleton(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Skeleton* pComponent = static_cast<Skeleton*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nSkeleton(name, components_list)\nSkeleton(<C++ component>)"));
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> Skeleton_GetSkeletonSource(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Skeleton* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getSkeletonSource()));
}

//-----------------------------------------------------------------------

void Skeleton_SetSkeletonSource(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Skeleton* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setSkeletonSource(Visual::fromJSObject(value));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> Skeleton_SetBoneMaterial(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsString())
    {
        Skeleton* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->setBoneMaterial(*String::AsciiValue(args[0]->ToString()));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nsetBoneMaterial(material_name)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Skeleton_SetSelectedBoneMaterial(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsString())
    {
        Skeleton* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->setSelectedBoneMaterial(*String::AsciiValue(args[0]->ToString()));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nsetSelectedBoneMaterial(material_name)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Skeleton_SelectBone(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsString())
    {
        Skeleton* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->selectBone(*String::AsciiValue(args[0]->ToString()));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nselectBone(bone_name)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Skeleton_DeselectBone(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsString())
    {
        Skeleton* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->deselectBone(*String::AsciiValue(args[0]->ToString()));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\ndeselectBone(bone_name)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Skeleton_DeselectAllBones(const Arguments& args)
{
    HandleScope handle_scope;

    Skeleton* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->deselectAllBones();

    return v8::Handle<v8::Value>();
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_Skeleton(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.Skeleton");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Debug_Skeleton_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        // Attributes
        AddAttribute(component, "skeletonSource", Skeleton_GetSkeletonSource, Skeleton_SetSkeletonSource);

        // Methods
        AddMethod(component, "setBoneMaterial",         Skeleton_SetBoneMaterial);
        AddMethod(component, "setSelectedBoneMaterial", Skeleton_SetSelectedBoneMaterial);
        AddMethod(component, "selectBone",              Skeleton_SelectBone);
        AddMethod(component, "deselectBone",            Skeleton_DeselectBone);
        AddMethod(component, "deselectAllBones",        Skeleton_DeselectAllBones);

        pManager->declareClassTemplate("Athena.Graphics.Debug.Skeleton", component);

        parent->Set(String::New("Skeleton_TYPE"), String::New(Athena::Graphics::Debug::Skeleton::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Skeleton"), component->GetFunction());
}
