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
    switch (lml)
    {
        case Ogre::LML_TRIVIAL:  LogManager::Log(LOG_COMMENT, "Ogre", message, "", "", 0); break;
        case Ogre::LML_NORMAL:   LogManager::Log(LOG_EVENT, "Ogre", message, "", "", 0); break;
        case Ogre::LML_CRITICAL: LogManager::Log(LOG_ERROR, "Ogre", message, "", "", 0); break;
    }
}
