/** @file   OgreLogListener.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::OgreLogListener'
*/

#include <Athena-Graphics/OgreLogListener.h>
#include <Athena-Core/Log/LogManager.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Log;
using namespace std;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char* __CONTEXT__ = "Ogre";


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

OgreLogListener::OgreLogListener()
{
}

//-----------------------------------------------------------------------

OgreLogListener::~OgreLogListener()
{
}


/************************* IMPLEMENTATION OF Ogre::LogListener *************************/

void OgreLogListener::messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml,
                                    bool maskDebug, const Ogre::String& logName,
                                    bool &skipThisMessage)
{
    ATHENA_LOG_EVENT(message);
}
