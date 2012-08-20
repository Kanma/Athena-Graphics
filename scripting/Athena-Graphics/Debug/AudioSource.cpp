#include <Athena-Graphics/Debug/AudioSource.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena::Graphics::Debug;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<AudioSource>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Debug_AudioSource_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new AudioSource(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        AudioSource* pComponent = static_cast<AudioSource*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nAudioSource(name, components_list)\nAudioSource(<C++ component>)"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Debug_AudioSource(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Debug.AudioSource");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Debug_AudioSource_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Debug.DebugComponent"));

        pManager->declareClassTemplate("Athena.Graphics.Debug.AudioSource", component);

        parent->Set(String::New("AudioSource_TYPE"), String::New(Athena::Graphics::Debug::AudioSource::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("AudioSource"), component->GetFunction());
}
