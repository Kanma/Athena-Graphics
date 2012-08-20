#include <Athena-Graphics/Line3D.h>
#include <Athena-Graphics/Conversions.h>
#include <Athena-Core/Utils/Describable.h>
#include <Ogre/OgrePolygon.h>

using namespace Athena;
using namespace Athena::Graphics;
using namespace Athena::Utils;


int main(int argc, char** argv)
{
    Math::Vector3 v(10.0, 20.0, 30.0);

    Ogre::Vector3 v2 = toOgre(v);

    Ogre::Polygon p;

    Describable d;

    return 0;
}
