#include <math/vector3d.h>

#include <limits>

namespace g3
{
    // class vector3d

    const Vector3d Vector3d::zero     = Vector3d();
    const Vector3d Vector3d::one      = Vector3d(1.0, 1.0, 1.0);
    const Vector3d Vector3d::oneNormalized = Vector3d::one.normalized();
    const Vector3d Vector3d::axisX    = Vector3d(1.0, 0.0, 0.0);
    const Vector3d Vector3d::axisY    = Vector3d(0.0, 1.0, 0.0);
    const Vector3d Vector3d::axisZ    = Vector3d(0.0, 0.0, 1.0);
    const Vector3d Vector3d::maxValue = Vector3d(std::numeric_limits<Vector3d::value_type>::max(),
                                                 std::numeric_limits<Vector3d::value_type>::max(),
                                                 std::numeric_limits<Vector3d::value_type>::max());
    const Vector3d Vector3d::minValue = Vector3d(std::numeric_limits<Vector3d::value_type>::min(),
                                                 std::numeric_limits<Vector3d::value_type>::min(),
                                                 std::numeric_limits<Vector3d::value_type>::min());
    const Vector3d Vector3d::invalid  = Vector3d::maxValue;

    Vector3d::value_type Vector3d::normalize(value_type epsilon /* = mathUtil::epsilon */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.0 / len;
            _x *= invLen;
            _y *= invLen;
            _z *= invLen;
        }
        else
        {
            len = 0.0;
            _x = _y = _z = 0.0;
        }

        return len;
    }

    Vector3d::self_type Vector3d::normalized() const
    {
        auto len = length();
        if (len > mathUtil::epsilon)
        {
            auto invLen = 1.0 / len;
            return Vector3d(_x * invLen, _y * invLen, _z * invLen);
        }
        else return Vector3d::zero;
    }
}
