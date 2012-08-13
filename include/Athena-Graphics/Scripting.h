/** @file   Scripting.h
    @author Philip Abbet

    Scripting-related declarations for the Athena-Graphics module
*/

#ifndef _ATHENA_GRAPHICS_SCRIPTING_H_
#define _ATHENA_GRAPHICS_SCRIPTING_H_

#include <v8.h>
#include <Athena-Graphics/Prerequisites.h>


namespace Athena {
namespace Graphics {


    namespace Debug {

        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ AudioListener wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL AudioListener* fromJSAudioListener(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript AudioListener (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSAudioListener();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript AudioListener around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(AudioListener* pAudioListener);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ AudioSource wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL AudioSource* fromJSAudioSource(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript AudioSource (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSAudioSource();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript AudioSource around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(AudioSource* pAudioSource);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Axes wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Axes* fromJSAxes(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Axes (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSAxes();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Axes around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Axes* pAxes);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Camera wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Camera* fromJSCamera(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Camera (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSCamera();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Camera around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Camera* pCamera);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ DebugComponent wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL DebugComponent* fromJSDebugComponent(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript DebugComponent (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSDebugComponent();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript DebugComponent around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(DebugComponent* pDebugComponent);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ DirectionalLight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL DirectionalLight* fromJSDirectionalLight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript DirectionalLight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSDirectionalLight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript DirectionalLight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(DirectionalLight* pDirectionalLight);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ PointLight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL PointLight* fromJSPointLight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript PointLight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSPointLight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript PointLight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(PointLight* pPointLight);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Spotlight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Spotlight* fromJSSpotlight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Spotlight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSSpotlight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Spotlight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Spotlight* pSpotlight);
    }


    namespace Visual {

        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Camera wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Camera* fromJSCamera(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Camera (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSCamera();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Camera around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Camera* pCamera);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ DirectionalLight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL DirectionalLight* fromJSDirectionalLight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript DirectionalLight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSDirectionalLight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript DirectionalLight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(DirectionalLight* pDirectionalLight);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ EntityComponent wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL EntityComponent* fromJSEntityComponent(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript EntityComponent (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSEntityComponent();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript EntityComponent around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(EntityComponent* pEntityComponent);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Object wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Object* fromJSObject(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Object (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSObject();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Object around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Object* pObject);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Plane wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Plane* fromJSPlane(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Plane (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSPlane();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Plane around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Plane* pPlane);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ PointLight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL PointLight* fromJSPointLight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript PointLight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSPointLight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript PointLight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(PointLight* pPointLight);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ Spotlight wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL Spotlight* fromJSSpotlight(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript Spotlight (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSSpotlight();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript Spotlight around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(Spotlight* pSpotlight);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ VisualComponent wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL VisualComponent* fromJSVisualComponent(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript VisualComponent (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSVisualComponent();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript VisualComponent around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(VisualComponent* pVisualComponent);


        //------------------------------------------------------------------------------------
        /// @brief  Retrieve the C++ World wrapped by a JavaScript one
        //------------------------------------------------------------------------------------
        ATHENA_GRAPHICS_SYMBOL World* fromJSWorld(v8::Handle<v8::Value> value);

        //------------------------------------------------------------------------------------
        /// @brief  Create a new JavaScript World (wrapping a new C++ one)
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Object> ATHENA_GRAPHICS_SYMBOL createJSWorld();

        //------------------------------------------------------------------------------------
        /// @brief  Wrap a new JavaScript World around a C++ one
        //------------------------------------------------------------------------------------
        v8::Handle<v8::Value> ATHENA_GRAPHICS_SYMBOL toJavaScript(World* pWorld);

    }

}
}

#endif
