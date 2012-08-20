#include <Athena-Graphics/Debug/PointLight.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<PointLight>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Debug_PointLight_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new PointLight(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        PointLight* pComponent = static_cast<PointLight*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nPointLight(name, components_list)\nPointLight(<C++ component>)"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_PointLight(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.PointLight");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Debug_PointLight_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        pManager->declareClassTemplate("Athena.Graphics.Debug.PointLight", component);

        parent->Set(String::New("PointLight_TYPE"), String::New(Athena::Graphics::Debug::PointLight::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("PointLight"), component->GetFunction());
}
