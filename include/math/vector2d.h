#ifndef G3_MATH_VECTOR_2_D
#define G3_MATH_VECTOR_2_D

#include <math/vector2f.h>

#include <limits>

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
        static self_type fromAngleRed(value_type angle) { return self_type(std::cos(angle), std::sin(angle)); }
        static self_type fromAngleDeg(value_type angle)
        { angle *= mathUtil::deg2rad; return fromAngleRed(angle); }

        static value_type dot(const self_type &v1, const self_type &v2)
        { return v1.dot(v2); }
        static value_type cross(const self_type &v1, const self_type &v2)
        { return v1.cross(v2); }

        static value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        static self_type lerp(const self_type &a, const self_type &b, value_type t)
        { auto s = 1.0 - t; return self_type(s * a.x() + t * b.x(), s * a.y() + t * b.y()); }

        // constructors
        Vector2d() { _x = _y = 0.0; }
        Vector2d(value_type x, value_type y) { _x = x; _y = y; }
        Vector2d(value_type values[]) { _x = values[0]; _y = values[1]; }
        
        // copy-constructors
        Vector2d(const self_type &copy) { _x = copy._x; _y = copy._y; }

        // type conversion
        Vector2d(const Vector2i &v2i)              // Vector2i -> Vector2d
        {
            _x = static_cast<value_type>(v2i.x());
            _y = static_cast<value_type>(v2i.y());
        }
        Vector2d(const Vector2f &v2f)              // Vector2f -> Vector2d
        {
            _x = static_cast<value_type>(v2f.x());
            _y = static_cast<value_type>(v2f.y());
        }

        operator Vector2f() const           // Vector2d -> Vector2f
        {
            return Vector2f(static_cast<Vector2f::value_type>(_x), static_cast<Vector2f::value_type>(_y));
        }

        // functions
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }

        value_type lengthSquared() const { return _x * _x + _y * _y; }
        value_type length() const { return std::sqrt(_x * _x + _y * _y); }

        value_type normalize(value_type epsilon = mathUtil::epsilon);
        self_type normalized() const;

        bool isNormalized() const
        { return std::abs((_x * _x + _y * _y) - 1.0) < mathUtil::zeroTolerance; }

        // TODO: realize function 'vector2d::round()'
        void round(int decimals)
        { }

        value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y; }

        value_type dotPerp(const self_type &v) const { return cross(v); }

        value_type cross(const self_type &v) const
        { return _x * v._y - _y * v._y; }

        self_type perp() const { return self_type(_y, -_x); }
        self_type unitPerp() const { return perp().normalized(); }

        value_type angleD(const self_type &v) const
        {
            auto fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return std::acos(fDot) * mathUtil::rad2deg;
        }

        value_type angleR(const self_type &v) const
        {
            auto fDot = mathUtil::clamp(dot(v), -1.0, 1.0);
            return std::acos(fDot);
        }

        value_type distanceSquared(const self_type &v) const
        {
            auto dx = _x - v._x, dy = _y - v._y;
            return dx * dx + dy * dy;
        }

        value_type distance(const self_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        void set(const self_type &v) { _x = v._x; _y = v._y; }
        void set(value_type x, value_type y) { _x = x; _y = y; }

        void add(const self_type &v) { _x += v._x; _y += v._y; }
        void subtract(const self_type &v) { _x -= v._x; _y -= v._y; }

        bool equals(const self_type &v) const
        { return (*this) == v; }
        bool epsilonEqual(const self_type &v, value_type eps) const
        { return std::abs(_x - v._x) <= eps && std::abs(_y - v._y) <= eps; }

        // operator functions
        value_type& operator [] (int i) { if (i == 0) return _x; else return _y; }
        value_type  operator [] (int i) const { if (i == 0) return _x; else return _y; }

        self_type operator - () const { return self_type(-_x, -_y); }

        self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y); }
        self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y); }
        self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d); }
        friend self_type operator + (value_type d, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y); }

        self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d); }
        friend self_type operator * (value_type d, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y); }

        self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d); }
        friend self_type operator / (value_type d, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y;
    };

    const Vector2d Vector2d::zero = Vector2d();
    const Vector2d Vector2d::one = Vector2d(1.0, 1.0);
    const Vector2d Vector2d::axisX = Vector2d(1.0, 0.0);
    const Vector2d Vector2d::axisY = Vector2d(0.0, 1.0);
    const Vector2d Vector2d::maxValue = Vector2d(std::numeric_limits<Vector2d::value_type>::max(),
                                                 std::numeric_limits<Vector2d::value_type>::max());
    const Vector2d Vector2d::minValue = Vector2d(std::numeric_limits<Vector2d::value_type>::min(),
                                                 std::numeric_limits<Vector2d::value_type>::min());

    Vector2d::value_type Vector2d::normalize(value_type epsilon /* = mathUtil::epsilon */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.0 / len;
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

    Vector2d Vector2d::normalized() const
    {
        auto len = length();
        if (len > mathUtil::epsilon)
        {
            auto invLen = 1.0 / len;
            return Vector2d(_x * invLen, _y * invLen);
        }
        else return Vector2d::zero;
    }

    Vector2d operator + (Vector2d::value_type d, const Vector2d &v)
    { return v + d; }

    Vector2d operator * (Vector2d::value_type d, const Vector2d &v)
    { return v * d; }

    Vector2d operator / (Vector2d::value_type d, const Vector2d &v)
    { return Vector2d(d / v.x(), d / v.y()); }
}

#endif
