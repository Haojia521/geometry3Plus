#ifndef G3_MATH_RAY_3
#define G3_MATH_RAY_3

#include <math/vectorTraits.h>

namespace g3
{
    template <typename T>
    class Ray3
    {
    public:
        using vector_type = typename Vector3Traits<T>::vector_type;
        using value_type = typename vector_type::value_type;

        // static values

        // static functions

        // constructors
        Ray3(const vector_type &origin, const vector_type &direction) : _origin(origin), _direction(direction)
        { _direction.normalize(); }

        // type conversion
        template <typename U>
        operator Ray3<U>() const
        {
            return Ray3<U>(static_cast<typename Ray3<U>::vector_type>(_origin),
                           static_cast<typename Ray3<U>::vector_type>(_direction));
        }

        // functions
        const vector_type& origin() const
        { return _origin; }
        const vector_type& direction() const
        { return _direction; }
        vector_type& origin()
        { return _origin; }

        vector_type& direction()
        { return _direction; }

        vector_type pointAt(value_type d) const
        { return _origin + _direction * d; }

        value_type project(const vector_type &p) const
        { return (p - _origin).dot(_direction); }

        value_type distanceSquared(cosnt vector_type &p) const
        {
            auto t = (p - _origin).dot(_direction);
            if (t < 0)
            { return _origin.distanceSquared(p); }
            else
            {
                auto proj = _origin + _direction * t;
                return (proj - p).lengthSquared();
            }
        }

        vector_type closestPoint(const vector_type &p) const
        {
            auto t = (p - _origin).dot(_direction);
            if (t < 0)
            { return _origin; }
            else
            { return _origin + _direction * t; }
        }

        // operator functions

    private:
        vector_type _origin;
        vector_type _direction;
    };

    using Ray3d = Ray3<double>;
    using Ray3f = Ray3<float>;
}

#endif
