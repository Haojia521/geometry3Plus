#include <math/vector2d.h>

#include <limits>

namespace g3
{
    // class vector2d

    const Vector2d Vector2d::zero     = Vector2d();
    const Vector2d Vector2d::one      = Vector2d(1.0, 1.0);
    const Vector2d Vector2d::axisX    = Vector2d(1.0, 0.0);
    const Vector2d Vector2d::axisY    = Vector2d(0.0, 1.0);
    const Vector2d Vector2d::maxValue = Vector2d(std::numeric_limits<Vector2d::value_type>::max(),
                                                 std::numeric_limits<Vector2d::value_type>::max());
    const Vector2d Vector2d::minValue = Vector2d(std::numeric_limits<Vector2d::value_type>::min(),
                                                 std::numeric_limits<Vector2d::value_type>::min());

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