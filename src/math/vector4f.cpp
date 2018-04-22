#include <math/vector4f.h>

namespace g3
{
    // class vector4f

    const Vector4f Vector4f::zero = Vector4f();
    const Vector4f Vector4f::one  = Vector4f(1.0, 1.0, 1.0, 1.0);

    Vector4f::value_type Vector4f::normalize(value_type epsilon /* = mathUtil::epsilonf */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.f / len;
            _x *= invLen;
            _y *= invLen;
            _z *= invLen;
            _w *= invLen;
        }
        else
        {
            len = 0.0;
            _x = _y = _z = _w = 0.0;
        }

        return len;
    }

    Vector4f::self_type Vector4f::normalized() const
    {
        auto len = length();
        if (len > mathUtil::epsilonf)
        {
            auto invLen = 1.f / len;
            return Vector4f(_x * invLen, _y * invLen, _z * invLen, _w * invLen);
        }
        else return Vector4f::zero;
    }
}
