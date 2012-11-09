/** @file   OgreLogListener.h
    @author Philip Abbet

    Declaration of the class 'Athena::Graphics::OgreLogListener'
*/

#ifndef _ATHENA_GRAPHICS_OGRELOGLISTENER_H_
#define _ATHENA_GRAPHICS_OGRELOGLISTENER_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Ogre/OgreLogManager.h>


namespace Athena {
namespace Graphics {

//---------------------------------------------------------------------------------------
/// @brief  Listener for the log system of Ogre, that redirects the log messages from
///         Ogre to the Athena log system
//---------------------------------------------------------------------------------------
class ATHENA_GRAPHICS_SYMBOL OgreLogListener: public Ogre::LogListener
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    //-----------------------------------------------------------------------------------
    OgreLogListener();

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~OgreLogListener();


    //_____ Implementation of Ogre::LogListener __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Overriden from Ogre::LogListener
    ///
    /// Called by the Ogre's LogManager each time a message is logged by it
    /// @param  name            Name of the log
    /// @param  message         Message to log
    /// @param  lml             Log message level
    /// @param  maskDebug       If we are printing to the console or not
    /// @param logName          The name of this log (so you can have several listeners
    ///                         for different logs, and identify them)
    /// @retval skipThisMessage If set to true by the messageLogged() implementation,
    ///                         the message will not be logged
    //-----------------------------------------------------------------------------------
    virtual void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml,
                               bool maskDebug, const Ogre::String& logName,
                               bool &skipThisMessage);
};

}
}

#endif
