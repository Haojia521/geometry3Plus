﻿#ifndef G3_MATH_VECTOR_3_D
#define G3_MATH_VECTOR_3_D

#include <math/vector2d.h>
#include <math/vector3f.h>

namespace g3
{
    class Vector3d
    {
    public:
        using value_type  = double;
        using self_type   = Vector3d;
        using asso_type_2 = Vector2d;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type oneNormalized;
        static const self_type axisX;
        static const self_type axisY;
        static const self_type axisZ;
        static const self_type maxValue;
        static const self_type minValue;
        static const self_type invalid;

        // static functions
        static value_type dot(const self_type &v1, const self_type &v2)
        { return v1.dot(v2); }
        static self_type cross(const self_type &v1, const self_type &v2)
        { return v1.cross(v2); }

        static value_type angleD(const self_type &v1, const self_type &v2)
        { return v1.angleD(v2); }
        static value_type angleR(const self_type &v1, const self_type &v2)
        { return v1.angleR(v2); }

        static self_type lerp(const self_type &a, const self_type &b, value_type t)
        {
            auto s = 1.0 - t;
            return self_type(s * a.x() + t * b.x(), 
                             s * a.y() + t * b.y(), 
                             s * a.z() + t * b.z());
        }

        // constructors
        Vector3d() { _x = _y = _z = 0.0; }
        Vector3d(value_type d) { _x = _y = _z = d;}
        Vector3d(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }
        Vector3d(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; }

        // copy-constructors
        Vector3d(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; }

        // type conversion
        Vector3d(const Vector3i &v3i)              // Vector3i -> Vector3d
        {
            _x = static_cast<value_type>(v3i.x());
            _y = static_cast<value_type>(v3i.y());
            _z = static_cast<value_type>(v3i.z());
        }
        Vector3d(const Vector3f &v3f)              // Vector3f -> Vector3d
        {
            _x = static_cast<value_type>(v3f.x());
            _y = static_cast<value_type>(v3f.y());
            _z = static_cast<value_type>(v3f.z());
        }
        operator Vector3f() const           // Vector3d -> Vector3f
        {
            return Vector3f(static_cast<Vector3f::value_type>(_x),
                            static_cast<Vector3f::value_type>(_y),
                            static_cast<Vector3f::value_type>(_z));
        }

        // functions
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type& z() { return _z; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }
        value_type  z() const { return _z; }

        asso_type_2 xy() const { return asso_type_2(_x, _y); }
        void xy(const asso_type_2 &v) { _x = v.x(); _y = v.y(); }

        asso_type_2 xz() const { return asso_type_2(_x, _z); }
        void xz(const asso_type_2 &v) { _x = v.x(); _z = v.y(); }

        asso_type_2 yz() const { return asso_type_2(_y, _z); }
        void yz(const asso_type_2 &v) { _y = v.x(), _z = v.y(); }

        value_type lengthSquared() const { return _x * _x + _y * _y + _z * _z; }
        value_type length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }
        value_type lengthL1() const { return std::abs(_x) + std::abs(_y) + std::abs(_z); }

        value_type max() const { return std::fmax(_x, std::fmax(_y, _z)); }
        value_type min() const { return std::fmin(_x, std::fmin(_y, _z)); }

        value_type maxAbs() const 
        { return std::fmax(std::abs(_x), std::fmax(std::abs(_y), std::abs(_z))); }
        value_type minAbs() const 
        { return std::fmin(std::abs(_x), std::fmin(std::abs(_y), std::abs(_z))); }

        self_type abs() const
        { return self_type(std::abs(_x), std::abs(_y), std::abs(_z)); }

        value_type normalize(value_type epsilon = mathUtil::epsilon);
        self_type normalized() const;

        bool isNormalized() const
        { return std::abs((_x * _x + _y * _y + _z * _z) - 1.0) < mathUtil::zeroTolerance; }

        // TODO: realize function 'vector3d::round()'
        void round(int decimals)
        { }

        value_type dot(const self_type &v) const
        { return _x * v._x + _y * v._y + _z * v._z; }

        self_type cross(const self_type &v) const
        { return self_type(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x); }

        self_type unitCross(const self_type &v) const
        { return cross(v).normalize(); }

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
            auto dx = _x - v._x, dy = _y - v._y, dz = _z - v._z;
            return dx * dx + dy * dy + dz * dz;
        }

        value_type distance(const self_type &v) const
        { return std::sqrt(distanceSquared(v)); }

        void set(const self_type &v) { _x = v._x; _y = v._y; _z = v._z; }
        void set(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }

        void add(const self_type &v) { _x += v._x; _y += v._y; _z += v._z; }
        void subtract(const self_type &v) { _x -= v._x; _y -= v._y; _z -= v._z; }

        bool equals(const self_type &v) const
        { return (*this) == v; }
        bool epsilonEqual(const self_type &v, value_type eps) const
        { return std::abs(_x - v._x) <= eps && std::abs(_y - v._y) <= eps && std::abs(_z - v._z) <= eps; }

        // operator functions
        value_type& operator [] (int i) 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }
        value_type  operator [] (int i) const 
        { if (i == 0) return _x; else if (i == 1) return _y; else return _z; }

        self_type operator - () const { return self_type(-_x, -_y, -_z); }

        self_type operator - (const self_type &v) const
        { return self_type(_x - v._x, _y - v._y, _z - v._z); }
        self_type operator - (value_type d) const
        { return self_type(_x - d, _y - d, _z - d); }

        self_type operator + (const self_type &v) const
        { return self_type(_x + v._x, _y + v._y, _z + v._z); }
        self_type operator + (value_type d) const
        { return self_type(_x + d, _y + d, _z + d); }
        friend self_type operator + (value_type d, const self_type &v);

        self_type operator * (const self_type &v) const
        { return self_type(_x * v._x, _y * v._y, _z * v._z); }

        self_type operator * (value_type d) const
        { return self_type(_x * d, _y * d, _z * d); }
        friend self_type operator * (value_type d, const self_type &v);

        self_type operator / (const self_type &v) const
        { return self_type(_x / v._x, _y / v._y, _z / v._z); }

        self_type operator / (value_type d) const
        { return self_type(_x / d, _y / d, _z / d); }
        friend self_type operator / (value_type d, const self_type &v);

        bool operator == (const self_type &v) const
        { return _x == v._x && _y == v._y && _z == v._z; }
        bool operator != (const self_type &v) const
        { return !((*this) == v); }

    private:
        value_type _x, _y, _z;
    };

    const Vector3d Vector3d::zero = Vector3d();
    const Vector3d Vector3d::one = Vector3d(1.0, 1.0, 1.0);
    const Vector3d Vector3d::oneNormalized = Vector3d::one.normalized();
    const Vector3d Vector3d::axisX = Vector3d(1.0, 0.0, 0.0);
    const Vector3d Vector3d::axisY = Vector3d(0.0, 1.0, 0.0);
    const Vector3d Vector3d::axisZ = Vector3d(0.0, 0.0, 1.0);
    const Vector3d Vector3d::maxValue = Vector3d(std::numeric_limits<Vector3d::value_type>::max(),
                                                 std::numeric_limits<Vector3d::value_type>::max(),
                                                 std::numeric_limits<Vector3d::value_type>::max());
    const Vector3d Vector3d::minValue = Vector3d(std::numeric_limits<Vector3d::value_type>::min(),
                                                 std::numeric_limits<Vector3d::value_type>::min(),
                                                 std::numeric_limits<Vector3d::value_type>::min());
    const Vector3d Vector3d::invalid = Vector3d::maxValue;

    Vector3d::value_type Vector3d::normalize(value_type epsilon /* = mathUtil::epsilon */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.0 / len;
            _x *= invLen;
            _y *= invLen;
            _z *= invLen;
        }
        else
        {
            len = 0.0;
            _x = _y = _z = 0.0;
        }

        return len;
    }

    Vector3d::self_type Vector3d::normalized() const
    {
        auto len = length();
        if (len > mathUtil::epsilon)
        {
            auto invLen = 1.0 / len;
            return Vector3d(_x * invLen, _y * invLen, _z * invLen);
        }
        else return Vector3d::zero;
    }

    Vector3d operator + (Vector3d::value_type d, const Vector3d &v)
    { return v + d; }

    Vector3d operator * (Vector3d::value_type d, const Vector3d &v)
    { return v * d; }

    Vector3d operator / (Vector3d::value_type d, const Vector3d &v)
    { return Vector3d(d / v.x(), d / v.y(), d / v.z()); }
}

#endif
