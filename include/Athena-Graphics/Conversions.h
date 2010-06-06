/** @file	Conversions.h
	@author	Philip Abbet

	Declaration of some conversion functions between Athena and Ogre types
*/

#ifndef _ATHENA_GRAPHICS_CONVERSIONS_H_
#define _ATHENA_GRAPHICS_CONVERSIONS_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Math/AxisAlignedBox.h>
#include <Athena-Math/Color.h>
#include <Athena-Math/Matrix3.h>
#include <Athena-Math/Matrix4.h>
#include <Athena-Math/Plane.h>
#include <Athena-Math/Quaternion.h>
#include <Athena-Math/Sphere.h>
#include <Athena-Math/Vector2.h>
#include <Athena-Math/Vector3.h>
#include <Athena-Math/Vector4.h>
#include <Ogre/OgreAxisAlignedBox.h>
#include <Ogre/OgreColourValue.h>
#include <Ogre/OgreMatrix3.h>
#include <Ogre/OgreMatrix4.h>
#include <Ogre/OgrePlane.h>
#include <Ogre/OgreQuaternion.h>
#include <Ogre/OgreSphere.h>
#include <Ogre/OgreVector2.h>
#include <Ogre/OgreVector3.h>
#include <Ogre/OgreVector4.h>


namespace Athena {
namespace Graphics {

Ogre::Vector2 toOgre(const Math::Vector2& v);
Ogre::Vector3 toOgre(const Math::Vector3& v);
Ogre::Vector4 toOgre(const Math::Vector4& v);

Ogre::Quaternion toOgre(const Math::Quaternion& q);
Ogre::ColourValue toOgre(const Math::Color& c);
Ogre::AxisAlignedBox toOgre(const Math::AxisAlignedBox& b);

Ogre::Matrix3 toOgre(const Math::Matrix3& m);
Ogre::Matrix4 toOgre(const Math::Matrix4& m);

Ogre::Radian toOgre(const Math::Radian& a);
Ogre::Degree toOgre(const Math::Degree& a);

Ogre::Plane toOgre(const Math::Plane& p);
Ogre::Sphere toOgre(const Math::Sphere& s);


Math::Vector2 fromOgre(const Ogre::Vector2& v);
Math::Vector3 fromOgre(const Ogre::Vector3& v);
Math::Vector4 fromOgre(const Ogre::Vector4& v);

Math::Quaternion fromOgre(const Ogre::Quaternion& q);
Math::Color fromOgre(const Ogre::ColourValue& c);
Math::AxisAlignedBox fromOgre(const Ogre::AxisAlignedBox& b);

Math::Matrix3 fromOgre(const Ogre::Matrix3& m);
Math::Matrix4 fromOgre(const Ogre::Matrix4& m);

Math::Radian fromOgre(const Ogre::Radian& a);
Math::Degree fromOgre(const Ogre::Degree& a);

Math::Plane fromOgre(const Ogre::Plane& p);
Math::Sphere fromOgre(const Ogre::Sphere& s);

}
}

#endif
