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

    namespace Visual {

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
