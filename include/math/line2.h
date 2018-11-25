#ifndef G3_MATH_LINE_2
#define G3_MATH_LINE_2

#include <math/vectorTraits.h>
#include <math/mathUtil.h>

namespace g3
{
    template <typename T>
    class Line2
    {
    public:
        using vector_type = Vector2Traits<T>::vector_type;
        using value_type = typename vector_type::value_type;
        using self_type = Line2<T>;

        // static values

        // static functions
        self_type fromPoints(const vector_type &p0, const vector_type &p1)
        { return self_type(p0, (p1 - p0).normalized()); }

        // constructors
        Line2(const vector_type &origin, const vector_type &direction) : _origin(origin), _direction(direction) {}

        // type conversion
        template <typename U>
        operator Line2<U>() const
        {
            return Line2<U>(static_cast<typename Line2<U>::vector_type>(_origin),
                            static_cast<typename Line2<U>::vector_type>(_direction));
        }

        // functions
        vector_type origin() const
        { return _origin; }
        vector_type direction() const
        { return _direction; }

        vector_type& origin()
        { return _origin; }
        vector_type& direction()
        { return _direction; }

        vector_type pointAt(value_type d) const
        { return _origin + _direction * d; }

        value_type project(const vector_type &p) const
        { return (p - _origin).dot(_direction); }

        value_type distanceSquared(const vector_type &p) const
        {
            auto proj = pointAt(project(p));
            return (proj - p).lengthSquared();
        }

        // Returns:
        //   +1, on right of line
        //   -1, on left of line
        //    0, on the line
        int whichSide(const vector_type &test, value_type tol = 0) const
        {
            auto v = test - _origin;
            auto det = v.x() * _direction.y() - v.y() * _direction.x();
            return (det > tol ? +1 : (det < -tol ? -1 : 0));
        }

        // Calculate intersection point between this line and another one.
        // Returns Vector2d.MaxValue if lines are parallel.
        vector_type intersectionPoint(const self_type &other, value_type dotThresh = mathUtil::getZeroTolerance<T>())
        {
            auto diff = other._origin - _origin;
            auto dotPerp = _direction.dotPerp(other._direction);
            if (std::abs(dotPerp) > dotThresh)
            {
                auto invDotPerp = ((value_type)1) / dotPerp;
                auto dotPerp2 = diff.dotPerp(other._direction);
                auto s = dotPerp2 * invDotPerp;
                return _origin + _direction * s;
            }
            return vector_type::maxValue;
        }

    private:
        vector_type _origin;
        vector_type _direction;
    };

    using Line2d = Line2<double>;
    using Line2f = Line2<float>;
}

#endif
