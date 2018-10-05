#ifndef G3_MATH_VECTOR_3_F
#define G3_MATH_VECTOR_3_F

#include <math/vector2f.h>
#include <math/vector3i.h>

namespace g3
{
    class Vector3f
    {
    public:
        typedef float    value_type;
        typedef Vector3f self_type;
        typedef Vector2f assoc_2d_type;

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
            auto s = 1.f - t;
            return self_type(s * a.x() + t * b.x(), 
                             s * a.y() + t * b.y(), 
                             s * a.z() + t * b.z());
        }

        // constructors
        Vector3f() { _x = _y = _z = 0; }
        Vector3f(value_type d) { _x = _y = _z = d; }
        Vector3f(value_type x, value_type y, value_type z) { _x = x; _y = y; _z = z; }
        Vector3f(value_type vals[]) { _x = vals[0]; _y = vals[1]; _z = vals[2]; }

        // copy-constructors
        Vector3f(const self_type &copy) { _x = copy._x; _y = copy._y; _z = copy._z; }

        // type conversion
        Vector3f(const Vector3i &v3i)             // Vector3i -> Vector3f
        {
            _x = static_cast<value_type>(v3i.x());
            _y = static_cast<value_type>(v3i.y());
            _z = static_cast<value_type>(v3i.z());
        }

        // functions
        value_type& x() { return _x; }
        value_type& y() { return _y; }
        value_type& z() { return _z; }
        value_type  x() const { return _x; }
        value_type  y() const { return _y; }
        value_type  z() const { return _z; }

        assoc_2d_type xy() const { return assoc_2d_type(_x, _y); }
        void xy(const assoc_2d_type &v) { _x = v.x(); _y = v.y(); }

        assoc_2d_type xz() const { return assoc_2d_type(_x, _z); }
        void xz(const assoc_2d_type &v) { _x = v.x(); _z = v.y(); }

        assoc_2d_type yz() const { return assoc_2d_type(_y, _z); }
        void yz(const assoc_2d_type &v) { _y = v.x(), _z = v.y(); }

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

        value_type normalize(value_type epsilon = mathUtil::getEpsilon<value_type>());
        self_type normalized() const;

        bool isNormalized() const
        { return std::abs((_x * _x + _y * _y + _z * _z) - 1.f) < mathUtil::getZeroTolerance<value_type>(); }

        // TODO: realize function 'vector3f::round()'
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

    const Vector3f Vector3f::zero = Vector3f();
    const Vector3f Vector3f::one = Vector3f(1.f, 1.f, 1.f);
    const Vector3f Vector3f::oneNormalized = Vector3f::one.normalized();
    const Vector3f Vector3f::axisX = Vector3f(1.f, 0.f, 0.f);
    const Vector3f Vector3f::axisY = Vector3f(0.f, 1.f, 0.f);
    const Vector3f Vector3f::axisZ = Vector3f(0.f, 0.f, 1.f);
    const Vector3f Vector3f::maxValue = Vector3f(std::numeric_limits<Vector3f::value_type>::max(),
                                                 std::numeric_limits<Vector3f::value_type>::max(),
                                                 std::numeric_limits<Vector3f::value_type>::max());
    const Vector3f Vector3f::minValue = Vector3f(std::numeric_limits<Vector3f::value_type>::min(),
                                                 std::numeric_limits<Vector3f::value_type>::min(),
                                                 std::numeric_limits<Vector3f::value_type>::min());
    const Vector3f Vector3f::invalid = Vector3f::maxValue;

    Vector3f::value_type Vector3f::normalize(value_type epsilon /* = mathUtil::epsilonf */)
    {
        auto len = length();
        if (len > epsilon)
        {
            auto invLen = 1.f / len;
            _x *= invLen;
            _y *= invLen;
            _z *= invLen;
        }
        else
        {
            len = 0.f;
            _x = _y = _z = 0.f;
        }

        return len;
    }

    Vector3f::self_type Vector3f::normalized() const
    {
        auto len = length();
        if (len > mathUtil::getEpsilon<value_type>())
        {
            auto invLen = 1.f / len;
            return Vector3f(_x * invLen, _y * invLen, _z * invLen);
        }
        else return Vector3f::zero;
    }

    Vector3f operator + (Vector3f::value_type d, const Vector3f &v)
    { return v + d; }

    Vector3f operator * (Vector3f::value_type d, const Vector3f &v)
    { return v * d; }

    Vector3f operator / (Vector3f::value_type d, const Vector3f &v)
    { return Vector3f(d / v.x(), d / v.y(), d / v.z()); }
}

#endif
