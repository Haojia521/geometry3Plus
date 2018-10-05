#ifndef G3_MATH_VECTOR_2_F
#define G3_MATH_VECTOR_2_F

#include <cmath>

#include <math/mathUtil.h>
#include <math/vector2i.h>

namespace g3
{
    class Vector2f
    {
    public:
        typedef float    value_type;
        typedef Vector2f self_type;

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
        { angle *= mathUtil::getDeg2Rad<value_type>(); return fromAngleRed(angle); }

        static value_type dot(const self_type &v1, const self_type &v2)
        { return v1.dot(v2); }
        static value_type cross(const self_type &v1, const self_type &v2)
        { return v1.cross(v2); }

        static value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        static self_type lerp(const self_type &a, const self_type &b, value_type t)
        { auto s = 1.f - t; return self_type(s * a.x() + t * b.x(), s * a.y() + t * b.y()); }

        // constructors
        Vector2f() { _x = _y = 0.f; }
        Vector2f(value_type x, value_type y) { _x = x; _y = y; }
        Vector2f(value_type values[]) { _x = values[0]; _y = values[1]; }
        
        // copy-constructors
        Vector2f(const self_type &copy) { _x = copy._x; _y = copy._y; }

        // type conversion
        Vector2f(const Vector2i &v2i)              // Vector2i -> Vector2f
        {
            _x = static_cast<value_type>(v2i.x());
            _y = static_cast<value_type>(v2i.y());
        }

        // functions
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }

        value_type lengthSquared() const { return _x * _x + _y * _y; }
        value_type length() const { return std::sqrt(_x * _x + _y * _y); }

        value_type normalize(value_type epsilon = mathUtil::getEpsilon<value_type>());
        self_type normalized() const;

        bool isNormalized() const
        { return std::abs((_x * _x + _y * _y) - 1.f) < mathUtil::getZeroTolerance<value_type>(); }

        // TODO: realize function 'vector2f::round()'
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
            auto fDot = mathUtil::clamp(dot(v), -1.f, 1.f);
            return std::acos(fDot) * mathUtil::getRad2Deg<value_type>();
        }

        value_type angleR(const self_type &v) const
        {
            auto fDot = mathUtil::clamp(dot(v), -1.f, 1.f);
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
        self_type operator - (value_type f) const
        { return self_type(_x - f, _y - f); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y); }
        self_type operator + (value_type f) const
        { return self_type(_x + f, _y + f); }
        friend self_type operator + (value_type f, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y); }

        self_type operator * (value_type f) const
        { return self_type(_x * f, _y * f); }
        friend self_type operator * (value_type f, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y); }

        self_type operator / (value_type f) const
        { return self_type(_x / f, _y / f); }
        friend self_type operator / (value_type f, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y;
    };

    const Vector2f Vector2f::zero = Vector2f();
    const Vector2f Vector2f::one = Vector2f(1.f, 1.f);
    const Vector2f Vector2f::axisX = Vector2f(1.f, 0.f);
    const Vector2f Vector2f::axisY = Vector2f(0.f, 1.f);
    const Vector2f Vector2f::maxValue = Vector2f(std::numeric_limits<Vector2f::value_type>::max(),
                                                 std::numeric_limits<Vector2f::value_type>::max());
    const Vector2f Vector2f::minValue = Vector2f(std::numeric_limits<Vector2f::value_type>::min(),
                                                 std::numeric_limits<Vector2f::value_type>::min());

    Vector2f::value_type Vector2f::normalize(value_type epsilon /* = mathUtil::epsilonf */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.f / len;
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

    Vector2f Vector2f::normalized() const
    {
        auto len = length();
        if (len > mathUtil::getEpsilon<value_type>())
        {
            auto invLen = 1.f / len;
            return Vector2f(_x * invLen, _y * invLen);
        }
        else return Vector2f::zero;
    }

    Vector2f operator + (Vector2f::value_type f, const Vector2f &v)
    { return v + f; }

    Vector2f operator * (Vector2f::value_type f, const Vector2f &v)
    { return v * f; }

    Vector2f operator / (Vector2f::value_type f, const Vector2f &v)
    { return Vector2f(f / v.x(), f / v.y()); }
}

#endif
