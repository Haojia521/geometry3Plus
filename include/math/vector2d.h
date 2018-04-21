#ifndef G3_MATH_VECTOR_2_D
#define G3_MATH_VECTOR_2_D

#include <math.h>

#include <math/mathUtil.h>

namespace g3
{
    class Vector2d
    {
    public:
        typedef double   value_type;
        typedef Vector2d self_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type axisX;
        static const self_type axisY;
        static const self_type maxValue;
        static const self_type minValue;

        // static functions
        static inline self_type fromAngleRed(value_type angle) { return self_type(cos(angle), sin(angle)); }
        static inline self_type fromAngleDeg(value_type angle)
        { angle *= mathUtil::deg2rad; return fromAngleRed(angle); }

        static inline value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static inline value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        static inline self_type lerp(const self_type &a, const self_type &b, value_type t)
        { value_type s = 1 - t; return self_type(s * a.x() + t * b.x(), s * a.y() + t * b.y()); }

        // constructors
        Vector2d() { _x = _y = 0.0; }
        Vector2d(value_type x, value_type y) { _x = x; _y = y; }
        Vector2d(value_type values[]) { _x = values[0]; _y = values[1]; }
        // copy-constructors
        Vector2d(const self_type &copy) { _x = copy._x; _y = copy._y; }

        // functions
        inline value_type& operator [] (int i) { if (i == 0) return _x; else return _y; }
        inline value_type  operator [] (int i) const { if (i == 0) return _x; else return _y; }

        inline value_type& x() { return _x; }
        inline value_type& y() { return _y; }
        inline value_type  x() const { return _x; }
        inline value_type  y() const { return _y; }

        inline value_type lengthSquared() const { return _x * _x + _y * _y; }
        inline value_type length() const { return sqrt(_x * _x + _y * _y); }

        value_type normalize(value_type epsilon = mathUtil::epsilon);
        self_type normalized() const;

        inline bool isNormalized() const
        { return abs((_x * _x + _y * _y) - 1.0) < mathUtil::zeroTolerance; }

        // TODO: realize fucntion 'vector2d::round()'
        inline void round(int decimals)
        { }

        inline value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y; }

        inline value_type dotPerp(const self_type &v) const { return cross(v); }

        inline value_type cross(const self_type &v) const
        { return _x * v._y - _y * v._y; }

        inline self_type perp() const { return self_type(_y, -_x); }
        inline self_type unitPerp() const { return perp().normalized(); }

        inline value_type angleD(const self_type &v) const
        {
            double fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return acos(fDot) * mathUtil::rad2deg;
        }

        inline value_type angleR(const self_type &v) const
        {
            double fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return acos(fDot);
        }

        inline value_type distanceSquared(const self_type &v) const
        {
            value_type dx = _x - v._x, dy = _y - v._y;
            return dx * dx + dy * dy;
        }

        inline value_type distance(const self_type &v) const
        { return sqrt(distanceSquared(v)); }

        inline void set(const self_type &v) { _x = v._x; _y = v._y; }
        inline void set(value_type x, value_type y) { _x = x; _y = y; }

        inline void add(const self_type &v) { _x += v._x; _y += v._y; }
        inline void subtract(const self_type &v) { _x -= v._x; _y -= v._y; }

        inline bool equals(const self_type &v) const
        { return (*this) == v; }
        inline bool epsilonEqual(const self_type &v, value_type eps) const
        { return abs(_x - v._x) <= eps && abs(_y - v._y) <= eps; }

        // operator functions
        inline self_type operator - () const { return self_type(-_x, -_y); }

        inline self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y); }
        inline self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d); }

        inline self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y); }
        inline self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d); }
        friend self_type operator + (value_type d, const self_type &v);

        inline self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y); }

        inline self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d); }
        friend self_type operator * (value_type d, const self_type &v);

        inline self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y); }

        inline self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d); }
        friend self_type operator / (value_type d, const self_type &v);

        inline bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y; }
        inline bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y;
    };

    inline Vector2d operator + (Vector2d::value_type d, const Vector2d &v)
    { return v + d; }

    inline Vector2d operator * (Vector2d::value_type d, const Vector2d &v)
    { return v * d; }

    inline Vector2d operator / (Vector2d::value_type d, const Vector2d &v)
    { return Vector2d(d / v.x(), d / v.y()); }
}

#endif
