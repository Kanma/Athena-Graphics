/** @file   PointLight.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Graphics::Visual::PointLight'
*/

#include <Athena-Graphics/Visual/PointLight.h>
#include <Athena-Core/Log/LogManager.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;
using namespace Athena::Signals;
using namespace Athena::Utils;
using namespace Athena::Math;
using namespace Athena::Log;
using namespace std;

using Ogre::Light;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*  __CONTEXT__         = "Visual/PointLight";

///< Name of the type of entity
const std::string   PointLight::TYPE    = "Athena/Visual/PointLight";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

PointLight::PointLight(const std::string& strName, ComponentsList* pList)
: DirectionalLight(strName, pList)
{
    assert(getSceneManager() && "There isn't an Scene manager's instance");
    assert(m_pSceneNode);
    assert(m_pLight);

    m_pLight->setType(Light::LT_POINT);
}

//-----------------------------------------------------------------------

PointLight::~PointLight()
{
}

//-----------------------------------------------------------------------

PointLight* PointLight::create(const std::string& strName, ComponentsList* pList)
{
    return new PointLight(strName, pList);
}

//-----------------------------------------------------------------------

PointLight* PointLight::cast(Component* pComponent)
{
    return dynamic_cast<PointLight*>(pComponent);
}

/****************************** MANAGEMENT OF THE LIGHT ********************************/

void PointLight::setAttenuation(Math::Real range, Math::Real constant,
                                 Math::Real linear, Math::Real quadratic)
{
    m_pLight->setAttenuation(range, constant, linear, quadratic);
}

//-----------------------------------------------------------------------

Real PointLight::getAttenuationRange() const
{
    return m_pLight->getAttenuationRange();
}

//-----------------------------------------------------------------------

Real PointLight::getAttenuationConstant() const
{
    return m_pLight->getAttenuationConstant();
}

//-----------------------------------------------------------------------

Real PointLight::getAttenuationLinear() const
{
    return m_pLight->getAttenuationLinear();
}

//-----------------------------------------------------------------------

Real PointLight::getAttenuationQuadric() const
{
    return m_pLight->getAttenuationQuadric();
}


/***************************** MANAGEMENT OF THE PROPERTIES ****************************/

Utils::PropertiesList* PointLight::getProperties() const
{
    // Call the base class implementation
    PropertiesList* pProperties = DirectionalLight::getProperties();

    // Create the category belonging to this type
    pProperties->selectCategory(TYPE, false);

    // Attenuation range
    pProperties->set("attenuationRange", new Variant(getAttenuationRange()));

    // Attenuation constant factor
    pProperties->set("attenuationConstant", new Variant(getAttenuationConstant()));

    // Attenuation linear factor
    pProperties->set("attenuationLinear", new Variant(getAttenuationLinear()));

    // Attenuation quadratric factor
    pProperties->set("attenuationQuadratic", new Variant(getAttenuationQuadric()));

    // Returns the list
    return pProperties;
}

//-----------------------------------------------------------------------

bool PointLight::setProperty(const std::string& strCategory, const std::string& strName,
                              Utils::Variant* pValue)
{
    assert(!strCategory.empty());
    assert(!strName.empty());
    assert(pValue);

    if (strCategory == TYPE)
        return PointLight::setProperty(strName, pValue);

    return DirectionalLight::setProperty(strCategory, strName, pValue);
}

//-----------------------------------------------------------------------

bool PointLight::setProperty(const std::string& strName, Utils::Variant* pValue)
{
    // Assertions
    assert(!strName.empty());
    assert(pValue);

    // Attenuation range
    if (strName == "attenuationRange")
    {
        setAttenuation(pValue->toFloat(), getAttenuationConstant(),
                       getAttenuationLinear(), getAttenuationQuadric());
    }

    // Attenuation constant factor
    else if (strName == "attenuationConstant")
    {
        setAttenuation(getAttenuationRange(), pValue->toFloat(),
                       getAttenuationLinear(), getAttenuationQuadric());
    }

    // Attenuation linear factor
    else if (strName == "attenuationLinear")
    {
        setAttenuation(getAttenuationRange(), getAttenuationConstant(),
                       pValue->toFloat(), getAttenuationQuadric());
    }

    // Attenuation quadratric factor
    else if (strName == "attenuationQuadratic")
    {
        setAttenuation(getAttenuationRange(), getAttenuationConstant(),
                       getAttenuationLinear(), pValue->toFloat());
    }

    // Destroy the value
    delete pValue;

    return true;
}
