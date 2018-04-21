#include <math/vector2f.h>

#include <limits>

namespace g3
{
    // class vector2f

    const Vector2f Vector2f::zero = Vector2f();
    const Vector2f Vector2f::one = Vector2f(1.f, 1.f);
    const Vector2f Vector2f::axisX = Vector2f(1.f, 0.f);
    const Vector2f Vector2f::axisY = Vector2f(0.f, 1.f);
    const Vector2f Vector2f::maxValue = Vector2f(std::numeric_limits<Vector2f::value_type>::max(),
                                                 std::numeric_limits<Vector2f::value_type>::max());
    const Vector2f Vector2f::minValue = Vector2f(std::numeric_limits<Vector2f::value_type>::min(),
                                                 std::numeric_limits<Vector2f::value_type>::min());

    Vector2f::value_type Vector2f::normalize(value_type epsilon /* = mathUtil::epsilon */)
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

    Vector2f::self_type Vector2f::normalized() const
    {
        double len = length();
        if (len > mathUtil::epsilon)
        {
            double invLen = 1.0 / len;
            return Vector2f(_x * invLen, _y * invLen);
        }
        else return Vector2f::zero;
    }
}