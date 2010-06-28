/**	@file	module.cpp
	@author	Philip Abbet

	Implementation of the module-level functions
*/

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Graphics/Visual/Camera.h>
#include <Athena-Graphics/Visual/DirectionalLight.h>
#include <Athena-Graphics/Visual/Object.h>
#include <Athena-Graphics/Visual/Plane.h>
#include <Athena-Graphics/Visual/PointLight.h>
#include <Athena-Graphics/Visual/Spotlight.h>
#include <Athena-Graphics/Debug/AudioListener.h>
#include <Athena-Graphics/Debug/AudioSource.h>
#include <Athena-Graphics/Debug/Axes.h>
#include <Athena-Graphics/Debug/Camera.h>
#include <Athena-Graphics/Debug/DirectionalLight.h>
#include <Athena-Graphics/Debug/PointLight.h>
#include <Athena-Graphics/Debug/Skeleton.h>
#include <Athena-Graphics/Debug/Spotlight.h>
#include <Athena-Entities/ComponentsManager.h>
#include <Ogre/OgreRoot.h>

using namespace Athena::Entities;


namespace Athena {
namespace Graphics {


Ogre::Root* initialize(const std::string& strPluginFileName,
                       const std::string& strOgreConfigFileName,
		               const std::string& strOgreLogFileName)
{
    assert(ComponentsManager::getSingletonPtr());
    assert(!Ogre::Root::getSingletonPtr());
    
    ComponentsManager* pComponentsManager = ComponentsManager::getSingletonPtr();
    
    // Register the visual components
    pComponentsManager->registerType(Visual::Camera::TYPE,              (ComponentCreationMethod*) &Visual::Camera::create);
    pComponentsManager->registerType(Visual::DirectionalLight::TYPE,    (ComponentCreationMethod*) &Visual::DirectionalLight::create);
    pComponentsManager->registerType(Visual::Object::TYPE,              (ComponentCreationMethod*) &Visual::Object::create);
    pComponentsManager->registerType(Visual::Plane::TYPE,               (ComponentCreationMethod*) &Visual::Plane::create);
    pComponentsManager->registerType(Visual::PointLight::TYPE,          (ComponentCreationMethod*) &Visual::PointLight::create);
    pComponentsManager->registerType(Visual::Spotlight::TYPE,           (ComponentCreationMethod*) &Visual::Spotlight::create);
    pComponentsManager->registerType(Visual::EntityComponent::TYPE,     (ComponentCreationMethod*) &Visual::EntityComponent::create);

    // Register the debug components
    pComponentsManager->registerType(Debug::AudioListener::TYPE,        (ComponentCreationMethod*) &Debug::AudioListener::create);
    pComponentsManager->registerType(Debug::AudioSource::TYPE,          (ComponentCreationMethod*) &Debug::AudioSource::create);
    pComponentsManager->registerType(Debug::Axes::TYPE,                 (ComponentCreationMethod*) &Debug::Axes::create);
    pComponentsManager->registerType(Debug::Camera::TYPE,               (ComponentCreationMethod*) &Debug::Camera::create);
    pComponentsManager->registerType(Debug::DebugComponent::TYPE,       (ComponentCreationMethod*) &Debug::DebugComponent::create);
    pComponentsManager->registerType(Debug::DirectionalLight::TYPE,     (ComponentCreationMethod*) &Debug::DirectionalLight::create);
    pComponentsManager->registerType(Debug::PointLight::TYPE,           (ComponentCreationMethod*) &Debug::PointLight::create);
    pComponentsManager->registerType(Debug::Skeleton::TYPE,             (ComponentCreationMethod*) &Debug::Skeleton::create);
    pComponentsManager->registerType(Debug::Spotlight::TYPE,            (ComponentCreationMethod*) &Debug::Spotlight::create);

    return new Ogre::Root(strPluginFileName, strOgreConfigFileName, strOgreLogFileName);
}

}
}
