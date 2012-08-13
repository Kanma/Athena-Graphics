#include <Athena-Graphics/Debug/AudioListener.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<AudioListener>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Debug_AudioListener_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new AudioListener(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        AudioListener* pComponent = static_cast<AudioListener*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nAudioListener(name, components_list)\nAudioListener(<C++ component>)"));
    }
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_AudioListener(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.AudioListener");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Debug_AudioListener_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        pManager->declareClassTemplate("Athena.Graphics.Debug.AudioListener", component);

        parent->Set(String::New("AudioListener_TYPE"), String::New(Athena::Graphics::Debug::AudioListener::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("AudioListener"), component->GetFunction());
}
