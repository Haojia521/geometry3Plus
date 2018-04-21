#include <math/vector2d.h>

namespace g3
{
    // class vector2d

    Vector2d::value_type Vector2d::normalize(value_type epsilon /* = mathUtil::epsilon */)
    {
        double len = length();
        if (len > epsilon)
        {
            double invLen = 1.0 / len;
            _x *= invLen;
            _y *= invLen;
        }
        else
        {
            len = 0.0;
            _x = _y = 0.0;
        }

        return len;
    }

    Vector2d::self_type Vector2d::normalized() const
    {
        double len = length();
        if (len > mathUtil::epsilon)
        {
            double invLen = 1.0 / len;
            return Vector2d(_x * invLen, _y * invLen);
        }
        else return Vector2d::zero;
    }
}