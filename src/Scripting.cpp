/** @file   Scripting.cpp
    @author Philip Abbet

    Implementation of the scripting-related functions of the Athena-Graphics module
*/

#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Scripting/Utils.h>
#include <string>

using namespace Athena::Graphics;
using namespace Athena::Scripting;


#define FROM_JS(CLASS_NAME)                                                                \
CLASS_NAME* fromJS##CLASS_NAME(v8::Handle<v8::Value> value)                                \
{                                                                                          \
    if (value->IsObject())                                                                 \
    {                                                                                      \
        CLASS_NAME* pObject = 0;                                                           \
        GetObjectPtr(value, &pObject);                                                     \
        return pObject;                                                                    \
    }                                                                                      \
                                                                                           \
    return 0;                                                                              \
}


#define CREATE_JS(CLASS_NAME)                                                              \
v8::Handle<v8::Object> createJS##CLASS_NAME()                                              \
{                                                                                          \
    v8::HandleScope handle_scope;                                                          \
                                                                                           \
    v8::Handle<v8::FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate( \
                                                        "Athena.Graphics." #CLASS_NAME);   \
                                                                                           \
    v8::Handle<v8::Object> jsObject = func->GetFunction()->NewInstance();                  \
                                                                                           \
    return handle_scope.Close(jsObject);                                                   \
}


#define TO_JS(CLASS_NAME)                                                                  \
v8::Handle<v8::Value> toJavaScript(CLASS_NAME* pObject)                                    \
{                                                                                          \
    v8::HandleScope handle_scope;                                                          \
                                                                                           \
    if (!pObject)                                                                          \
        return v8::Handle<v8::Value>();                                                    \
                                                                                           \
    v8::Handle<v8::FunctionTemplate> func = ScriptingManager::getSingletonPtr()->getClassTemplate( \
                                                        "Athena.Graphics." #CLASS_NAME);   \
                                                                                           \
    v8::Handle<v8::Value> argv[1];                                                         \
    argv[0] = v8::External::New(pObject);                                                  \
                                                                                           \
    v8::Handle<v8::Object> jsObject = func->GetFunction()->NewInstance(1, argv);           \
                                                                                           \
    return handle_scope.Close(jsObject);                                                   \
}


#define IMPLEMENT_CONVERSIONS(CLASS_NAME)                                                  \
    FROM_JS(CLASS_NAME);                                                                   \
    CREATE_JS(CLASS_NAME);                                                                 \
    TO_JS(CLASS_NAME);



namespace Athena {
namespace Graphics {

    namespace Visual {

        IMPLEMENT_CONVERSIONS(VisualComponent)
        IMPLEMENT_CONVERSIONS(World)

    }

}
}
