#include <math/vector4d.h>

namespace g3
{
    // class vector4d

    const Vector4d Vector4d::zero = Vector4d();
    const Vector4d Vector4d::one  = Vector4d(1.0, 1.0, 1.0, 1.0);

    Vector4d::value_type Vector4d::normalize(value_type epsilon /* = mathUtil::epsilon */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.0 / len;
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

    Vector4d::self_type Vector4d::normalized() const
    {
        auto len = length();
        if (len > mathUtil::epsilon)
        {
            auto invLen = 1.0 / len;
            return Vector4d(_x * invLen, _y * invLen, _z * invLen, _w * invLen);
        }
        else return Vector4d::zero;
    }
}
