#include <Athena-Graphics/Visual/Object.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace Athena::Math;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<Visual::Object>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Object_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::Object(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::Object* pComponent = static_cast<Visual::Object*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nObject(name, components_list)\nObject(<C++ object>)"));
    }
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> Object_LoadMesh(const Arguments& args)
{
    HandleScope handle_scope;

    if (((args.Length() == 1) || (args.Length() == 2)) && args[0]->IsString())
    {
        Visual::Object* ptr = GetPtr(args.This());
        assert(ptr);

        std::string strGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
        if ((args.Length() == 2) && args[1]->IsString())
            strGroupName = *String::AsciiValue(args[1]->ToString());

        bool result = ptr->loadMesh(*String::AsciiValue(args[0]->ToString()), strGroupName);

        return handle_scope.Close(v8::Boolean::New(result));
    }


    return ThrowException(String::New("Invalid parameters, valid syntax:\nloadMesh(mesh_name, group_name)"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_Object(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.Object");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Object_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent"));

        // Methods
        AddMethod(component, "loadMesh", Object_LoadMesh);

        pManager->declareClassTemplate("Athena.Graphics.Visual.Object", component);

        parent->Set(String::New("Object_TYPE"), String::New(Athena::Graphics::Visual::Object::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Object"), component->GetFunction());
}
