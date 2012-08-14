#include <Athena-Graphics/Visual/Camera.h>
#include <Athena-Graphics/Scripting.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena-Math/Scripting.h>
#include <v8.h>

using namespace Athena::Graphics;
using namespace Athena::Entities;
using namespace Athena::Scripting;
using namespace Athena::Math;
using namespace v8;


/**************************************** MACROS ***************************************/

#define GetPtr(HANDLE) GetObjectPtr<Visual::Camera>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Camera_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::Camera(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::Camera* pComponent = static_cast<Visual::Camera*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    else
    {
        return ThrowException(String::New("Invalid parameters, valid syntax:\nCamera(name, components_list)\nCamera(<C++ camera>)"));
    }
}


/************************************** PROPERTIES *************************************/

v8::Handle<Value> Camera_GetPolygonMode(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Uint32::New(ptr->getPolygonMode()));
}

//-----------------------------------------------------------------------

void Camera_SetPolygonMode(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    uint32_t mode = value->ToUint32()->Value();
    if ((mode >= Ogre::PM_POINTS) && (mode <= Ogre::PM_SOLID))
        ptr->setPolygonMode((Ogre::PolygonMode) mode);
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetLodBias(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getLodBias()));
}

//-----------------------------------------------------------------------

void Camera_SetLodBias(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setLodBias(value->ToNumber()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetAutoAspectRatio(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Boolean::New(ptr->getAutoAspectRatio()));
}

//-----------------------------------------------------------------------

void Camera_SetAutoAspectRatio(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setAutoAspectRatio(value->ToBoolean()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetFOVy(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getFOVy().valueRadians()));
}

//-----------------------------------------------------------------------

void Camera_SetFOVy(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setFOVy(Radian(value->ToNumber()->Value()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetNearClipDistance(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getNearClipDistance()));
}

//-----------------------------------------------------------------------

void Camera_SetNearClipDistance(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setNearClipDistance(value->ToNumber()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetFarClipDistance(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getFarClipDistance()));
}

//-----------------------------------------------------------------------

void Camera_SetFarClipDistance(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setFarClipDistance(value->ToNumber()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetAspectRatio(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Number::New(ptr->getAspectRatio()));
}

//-----------------------------------------------------------------------

void Camera_SetAspectRatio(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    ptr->setAspectRatio(value->ToNumber()->Value());
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetProjectionType(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Uint32::New(ptr->getProjectionType()));
}

//-----------------------------------------------------------------------

void Camera_SetProjectionType(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    uint32_t type = value->ToUint32()->Value();
    if ((type >= Ogre::PT_ORTHOGRAPHIC) && (type <= Ogre::PT_PERSPECTIVE))
        ptr->setProjectionType((Ogre::ProjectionType) type);
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_IsReflected(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(v8::Boolean::New(ptr->isReflected()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetReflectionMatrix(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getReflectionMatrix()));
}

//-----------------------------------------------------------------------

v8::Handle<Value> Camera_GetReflectionPlane(Local<String> property, const AccessorInfo &info)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(info.This());
    assert(ptr);

    return handle_scope.Close(toJavaScript(ptr->getReflectionPlane()));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> Camera_GetFrustumPlane(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsUint32())
    {
        Visual::Camera* ptr = GetPtr(args.This());
        assert(ptr);

        uint32_t plane = args[0]->ToUint32()->Value();
        if ((plane >= Ogre::FRUSTUM_PLANE_NEAR) && (plane <= Ogre::FRUSTUM_PLANE_BOTTOM))
            return handle_scope.Close(toJavaScript(ptr->getFrustumPlane((Ogre::FrustumPlane) plane)));
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\ngetFrustumPlane(frustum_plane_number)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Camera_IsVisible(const Arguments& args)
{
    HandleScope handle_scope;

    if (args.Length() == 1)
    {
        Visual::Camera* ptr = GetPtr(args.This());
        assert(ptr);

        bool bVisible = true;
        Ogre::FrustumPlane culledBy;

        if (isJSAxisAlignedBox(args[0]))
            bVisible = ptr->isVisible(fromJSAxisAlignedBoxUnsafe(args[0]), &culledBy);
        else if (isJSSphere(args[0]))
            bVisible = ptr->isVisible(fromJSSphereUnsafe(args[0]), &culledBy);
        else if (isJSVector3(args[0]))
            bVisible = ptr->isVisible(fromJSVector3Unsafe(args[0]), &culledBy);
        else
            return ThrowException(String::New("Invalid parameters, valid syntax:\nisVisible(aab)\nisVisible(sphere)\nisVisible(vertex)"));

        if (bVisible)
            return handle_scope.Close(v8::Boolean::New(true));
        else
            return handle_scope.Close(v8::Uint32::New(culledBy));
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nisVisible(aab)\nisVisible(sphere)\nisVisible(vertex)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Camera_EnableReflection(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && isJSPlane(args[0]))
    {
        Visual::Camera* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->enableReflection(fromJSPlaneUnsafe(args[0]));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nenableReflection(plane)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Camera_DisableReflection(const Arguments& args)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->disableReflection();

    return v8::Handle<v8::Value>();
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Camera_EnableCustomNearClipPlane(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && isJSPlane(args[0]))
    {
        Visual::Camera* ptr = GetPtr(args.This());
        assert(ptr);

        ptr->enableCustomNearClipPlane(fromJSPlaneUnsafe(args[0]));

        return v8::Handle<v8::Value>();
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nenableCustomNearClipPlane(plane)"));
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> Camera_DisableCustomNearClipPlane(const Arguments& args)
{
    HandleScope handle_scope;

    Visual::Camera* ptr = GetPtr(args.This());
    assert(ptr);

    ptr->disableCustomNearClipPlane();

    return v8::Handle<v8::Value>();
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_Camera(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.Camera");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Camera_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent"));

        // Attributes
        AddAttribute(component, "polygonMode",      Camera_GetPolygonMode, Camera_SetPolygonMode);
        AddAttribute(component, "lodBias",          Camera_GetLodBias, Camera_SetLodBias);
        AddAttribute(component, "autoAspectRatio",  Camera_GetAutoAspectRatio, Camera_SetAutoAspectRatio);
        AddAttribute(component, "fov_y",            Camera_GetFOVy, Camera_SetFOVy);
        AddAttribute(component, "nearClipDistance", Camera_GetNearClipDistance, Camera_SetNearClipDistance);
        AddAttribute(component, "farClipDistance",  Camera_GetFarClipDistance, Camera_SetFarClipDistance);
        AddAttribute(component, "aspectRatio",      Camera_GetAspectRatio, Camera_SetAspectRatio);
        AddAttribute(component, "projectionType",   Camera_GetProjectionType, Camera_SetProjectionType);
        AddAttribute(component, "isReflected",      Camera_IsReflected, 0);
        AddAttribute(component, "reflectionMatrix", Camera_GetReflectionMatrix, 0);
        AddAttribute(component, "reflectionPlane",  Camera_GetReflectionPlane, 0);

        // Methods
        AddMethod(component, "getFrustumPlane",     Camera_GetFrustumPlane);
        AddMethod(component, "isVisible",           Camera_IsVisible);
        AddMethod(component, "enableReflection",    Camera_EnableReflection);
        AddMethod(component, "disableReflection",   Camera_DisableReflection);
        AddMethod(component, "enableReflection",    Camera_EnableCustomNearClipPlane);
        AddMethod(component, "disableReflection",   Camera_DisableCustomNearClipPlane);

        pManager->declareClassTemplate("Athena.Graphics.Visual.Camera", component);

        parent->Set(String::New("Camera_TYPE"), String::New(Athena::Graphics::Visual::Camera::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Camera"), component->GetFunction());
}
