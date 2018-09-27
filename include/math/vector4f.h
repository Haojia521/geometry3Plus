#ifndef G3_MATH_VECTOR_4_F
#define G3_MATH_VECTOR_4_F

#include <cmath>

#include <math/mathUtil.h>

namespace g3
{
    class Vector4f
    {
    public:
        typedef float    value_type;
        typedef Vector4f self_type;

        // static values
        static const self_type zero;
        static const self_type one;

        // constructors
        Vector4f() { _x = _y = _z = _w = 0; }
        Vector4f(value_type d) { _x = _y = _z = _w = d; }
        Vector4f(value_type x, value_type y, value_type z, value_type w) { _x = x; _y = y; _z = z; _w = w; }
        Vector4f(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; _w = vals[3]; }

        // copy-constructors
        Vector4f(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; _w = copy._w; }

        // functions
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type& z() { return _z; }
        value_type& w() { return _w; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }
        value_type  z() const { return _z; }
        value_type  w() const { return _w; }

        value_type lengthSquared() const { return _x * _x + _y * _y + _z * _z + _w * _w; }
        value_type length() const { return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w); }
        value_type lengthL1() const { return std::abs(_x) + std::abs(_y) + std::abs(_z) + std::abs(_w); }

        value_type normalize(value_type epsilon = mathUtil::getEpsilon<value_type>());
        self_type normalized() const;

        bool isNormalized() const
        { return std::abs((_x * _x + _y * _y + _z * _z + _w * _w) - 1.f) < mathUtil::getZeroTolerance<value_type>(); }

        // TODO: realize function 'vector4f::round()'
        void round(int decimals)
        { }

        value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y + _z * v._z + _w * v._w; }

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
            auto dx = _x - v._x, dy = _y - v._y, dz = _z - v._z, dw = _w - v._w;
            return dx * dx + dy * dy + dz * dz + dw * dw;
        }

        value_type distance(const self_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; _w = v._w; }
        void set(value_type x, value_type y, value_type z, value_type w) { _x = x; _y = y; _z = z; _w = w; }

        void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; _w += _w; }
        void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; _w -= v._w; }

        bool equals(const self_type &v) const
        { return (*this) == v; }
        bool epsilonEqual(const self_type &v, value_type eps) const
        { return std::abs(_x - v._x) <= eps && std::abs(_y - v._y) <= eps && std::abs(_z - v._z) <= eps && std::abs(_w - v._w) <= eps; }

        // operator functions
        value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 1) return _y; else if (i == 2) return _z; else return _w; }
        value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 1) return _y; else if (i == 2) return _z; else return _w; }

        self_type operator - () const { return self_type(-_x, -_y, -_z, -_w); }

        self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y, _z - v._z, _w - v._w); }
        self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d, _z - d, _w - d); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y, _z + v._z, _w + v._w); }
        self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d, _z + d, _w + d); }
        friend self_type operator + (value_type d, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y, _z * v._z, _w * v._w); }

        self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d, _z * d, _w * d); }
        friend self_type operator * (value_type d, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y, _z / v._z, _w / v._w); }

        self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d, _z / d, _w / d); }
        friend self_type operator / (value_type d, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y && _z == v._z && _w == v._w; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y, _z, _w;
    };

    const Vector4f Vector4f::zero = Vector4f();
    const Vector4f Vector4f::one = Vector4f(1.0, 1.0, 1.0, 1.0);

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
        if (len > mathUtil::getEpsilon<value_type>())
        {
            auto invLen = 1.f / len;
            return Vector4f(_x * invLen, _y * invLen, _z * invLen, _w * invLen);
        }
        else return Vector4f::zero;
    }

    Vector4f operator + (Vector4f::value_type d, const Vector4f &v)
    { return v + d; }

    Vector4f operator * (Vector4f::value_type d, const Vector4f &v)
    { return v * d; }

    Vector4f operator / (Vector4f::value_type d, const Vector4f &v)
    { return Vector4f(d / v.x(), d / v.y(), d / v.z(), d / v.w()); }
}

#endif
