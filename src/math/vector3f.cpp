#include <math/vector3f.h>

#include <limits>

namespace g3
{
    // class vector3f

    const Vector3f Vector3f::zero     = Vector3f();
    const Vector3f Vector3f::one      = Vector3f(1.f, 1.f, 1.f);
    const Vector3f Vector3f::oneNormalized = Vector3f::one.normalized();
    const Vector3f Vector3f::axisX    = Vector3f(1.f, 0.f, 0.f);
    const Vector3f Vector3f::axisY    = Vector3f(0.f, 1.f, 0.f);
    const Vector3f Vector3f::axisZ    = Vector3f(0.f, 0.f, 1.f);
    const Vector3f Vector3f::maxValue = Vector3f(std::numeric_limits<Vector3f::value_type>::max(),
                                                 std::numeric_limits<Vector3f::value_type>::max(),
                                                 std::numeric_limits<Vector3f::value_type>::max());
    const Vector3f Vector3f::minValue = Vector3f(std::numeric_limits<Vector3f::value_type>::min(),
                                                 std::numeric_limits<Vector3f::value_type>::min(),
                                                 std::numeric_limits<Vector3f::value_type>::min());
    const Vector3f Vector3f::invalid  = Vector3f::maxValue;

    Vector3f::value_type Vector3f::normalize(value_type epsilon /* = mathUtil::epsilonf */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.f / len;
            _x *= invLen;
            _y *= invLen;
            _z *= invLen;
        }
        else
        {
            len = 0.f;
            _x = _y = _z = 0.f;
        }

        return len;
    }

    Vector3f::self_type Vector3f::normalized() const
    {
        auto len = length();
        if (len > mathUtil::getEpsilon<value_type>())
        {
            auto invLen = 1.f / len;
            return Vector3f(_x * invLen, _y * invLen, _z * invLen);
        }
        else return Vector3f::zero;
    }
}
