#include <Athena-Graphics/Visual/Plane.h>
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

#define GetPtr(HANDLE) GetObjectPtr<Visual::Plane>(HANDLE)


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

// Constructor
v8::Handle<Value> Plane_New(const Arguments& args)
{
    // New C++ component
    if ((args.Length() == 2) && args[0]->IsString() && args[1]->IsObject())
    {
        ComponentsList* pList = 0;
        GetObjectPtr(args[1], &pList);

        if (pList)
            return SetObjectPtr(args.This(), new Visual::Plane(*String::AsciiValue(args[0]->ToString()), pList),
                                &NoOpWeakCallback);
    }

    // Wrapper around an existing C++ component
    else if ((args.Length() == 1) && args[0]->IsExternal())
    {
        Visual::Plane* pComponent = static_cast<Visual::Plane*>(External::Unwrap(args[0]));
        return SetObjectPtr(args.This(), pComponent, &NoOpWeakCallback);
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\nPlane(name, components_list)\nPlane(<C++ plane>)"));
}


/**************************************** METHODS ***************************************/

v8::Handle<v8::Value> Camera_CreatePlane(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() >= 5) && (args.Length() <= 12))
    {
        std::string strMaterial;
        Vector3 normalVector;
        Real distance;
        Real width;
        Real height;
        int xSegments = 1;
        int ySegments = 1;
        bool bNormals = true;
        int iNbTexCoordSet = 1;
        Real uTile = 1.0f;
        Real vTile = 1.0f;
        Vector3 upVector = Vector3::UNIT_Y;

        if (!args[0]->IsString())
            goto bail;

        strMaterial = *String::AsciiValue(args[0]->ToString());


        if (!isJSVector3(args[1]))
            goto bail;

        normalVector = fromJSVector3Unsafe(args[1]);


        if (!args[2]->IsNumber())
            goto bail;

        distance = args[2]->ToNumber()->Value();


        if (!args[3]->IsNumber())
            goto bail;

        width = args[3]->ToNumber()->Value();


        if (!args[4]->IsNumber())
            goto bail;

        height = args[4]->ToNumber()->Value();


        if (args.Length() >= 6)
        {
            if (args[5]->IsInt32())
                xSegments = args[5]->ToInt32()->Value();
            else
                goto bail;
        }

        if (args.Length() >= 7)
        {
            if (args[6]->IsInt32())
                ySegments = args[6]->ToInt32()->Value();
            else
                goto bail;
        }

        if (args.Length() >= 8)
        {
            if (args[7]->IsBoolean())
                bNormals = args[7]->ToBoolean()->Value();
            else
                goto bail;
        }

        if (args.Length() >= 9)
        {
            if (args[8]->IsInt32())
                iNbTexCoordSet = args[8]->ToInt32()->Value();
            else
                goto bail;
        }

        if (args.Length() >= 10)
        {
            if (args[9]->IsNumber())
                uTile = args[9]->ToNumber()->Value();
            else
                goto bail;
        }

        if (args.Length() >= 11)
        {
            if (args[10]->IsNumber())
                vTile = args[10]->ToNumber()->Value();
            else
                goto bail;
        }

        if (args.Length() == 12)
        {
            if (isJSVector3(args[11]))
                upVector = fromJSVector3Unsafe(args[11]);
            else
                goto bail;
        }


        Visual::Plane* ptr = GetPtr(args.This());
        assert(ptr);

        return handle_scope.Close(v8::Boolean::New(ptr->createPlane(
                strMaterial, normalVector, distance, width, height, xSegments, ySegments,
                bNormals, iNbTexCoordSet, uTile, vTile, upVector
            )));
    }

bail:
    return ThrowException(String::New("Invalid parameters, valid syntax:\ncreatePlane(" \
                                      "material, normal, distance, width, height [, xSegments " \
                                      "[, ySegments [, bNormals [, bbTexCoordSet [, uTile " \
                                      "[, vTile [, upVector]]]]]]])"));
}


/************************************ BINDING FUNCTION **********************************/

bool bind_Visual_Plane(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    v8::Handle<FunctionTemplate> component = pManager->getClassTemplate("Athena.Graphics.Visual.Plane");

    if (component.IsEmpty())
    {
        assert(!pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent").IsEmpty());

        // Declaration of the class
        component = FunctionTemplate::New(Plane_New);
        component->InstanceTemplate()->SetInternalFieldCount(1);
        component->Inherit(pManager->getClassTemplate("Athena.Graphics.Visual.EntityComponent"));

        // Methods
        AddMethod(component, "createPlane", Camera_CreatePlane);

        pManager->declareClassTemplate("Athena.Graphics.Visual.Plane", component);

        parent->Set(String::New("Plane_TYPE"), String::New(Athena::Graphics::Visual::Plane::TYPE.c_str()));
    }

    // Add the class to the parent
    return parent->Set(String::New("Plane"), component->GetFunction());
}
