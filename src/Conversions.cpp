/**	@file	Conversions.cpp
	@author	Philip Abbet

	Implementation of the conversion functions between Athena and Ogre types
*/

#include <Athena-Graphics/Conversions.h>


using namespace Athena;
using namespace std;


namespace Athena {
namespace Graphics {

//-----------------------------------------------------------------------

Ogre::Vector2 toOgre(const Math::Vector2& v)
{
    return Ogre::Vector2(v.x, v.y);
}

//-----------------------------------------------------------------------

Ogre::Vector3 toOgre(const Math::Vector3& v)
{
    return Ogre::Vector3(v.x, v.y, v.z);
}

//-----------------------------------------------------------------------

Ogre::Vector4 toOgre(const Math::Vector4& v)
{
    return Ogre::Vector4(v.x, v.y, v.z, v.w);
}

//-----------------------------------------------------------------------

Ogre::Quaternion toOgre(const Math::Quaternion& q)
{
    return Ogre::Quaternion(q.w, q.x, q.y, q.z);
}

//-----------------------------------------------------------------------

Ogre::ColourValue toOgre(const Math::Color& c)
{
    return Ogre::ColourValue(c.r, c.g, c.b, c.a);
}

//-----------------------------------------------------------------------

Ogre::AxisAlignedBox toOgre(const Math::AxisAlignedBox& b)
{
    return Ogre::AxisAlignedBox(toOgre(b.getMinimum()), toOgre(b.getMaximum()));
}

//-----------------------------------------------------------------------

Ogre::Matrix3 toOgre(const Math::Matrix3& m)
{
    return Ogre::Matrix3(m.m);
}

//-----------------------------------------------------------------------

Ogre::Matrix4 toOgre(const Math::Matrix4& m)
{
    return Ogre::Matrix4(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
                         m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
                         m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
                         m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
}

//-----------------------------------------------------------------------

Math::Vector2 fromOgre(const Ogre::Vector2& v)
{
    return Math::Vector2(v.x, v.y);
}

//-----------------------------------------------------------------------

Math::Vector3 fromOgre(const Ogre::Vector3& v)
{
    return Math::Vector3(v.x, v.y, v.z);
}

//-----------------------------------------------------------------------

Math::Vector4 fromOgre(const Ogre::Vector4& v)
{
    return Math::Vector4(v.x, v.y, v.z, v.w);
}

//-----------------------------------------------------------------------

Math::Quaternion fromOgre(const Ogre::Quaternion& q)
{
    return Math::Quaternion(q.w, q.x, q.y, q.z);
}

//-----------------------------------------------------------------------

Math::Color fromOgre(const Ogre::ColourValue& c)
{
    return Math::Color(c.r, c.g, c.b, c.a);
}

//-----------------------------------------------------------------------

Math::AxisAlignedBox fromOgre(const Ogre::AxisAlignedBox& b)
{
    return Math::AxisAlignedBox(fromOgre(b.getMinimum()), fromOgre(b.getMaximum()));
}

//-----------------------------------------------------------------------

Math::Matrix3 fromOgre(const Ogre::Matrix3& m)
{
    return Math::Matrix3(m[0][0], m[0][1], m[0][2],
                         m[1][0], m[1][1], m[1][2],
                         m[2][0], m[2][1], m[2][2]);
}

//-----------------------------------------------------------------------

Math::Matrix4 fromOgre(const Ogre::Matrix4& m)
{
    return Math::Matrix4(m[0][0], m[0][1], m[0][2], m[0][3],
                         m[1][0], m[1][1], m[1][2], m[1][3],
                         m[2][0], m[2][1], m[2][2], m[2][3],
                         m[3][0], m[3][1], m[3][2], m[3][3]);
}

}
}
