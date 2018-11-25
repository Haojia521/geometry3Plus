#ifndef G3_MATH_LINE_3
#define G3_MATH_LINE_3

#include <math/vectorTraits.h>

namespace g3
{
    template <typename T>
    class Line3
    {
    public:
        using vector_type = Vector3Traits<T>::vector_type;
        using value_type = typename vector_type::value_type;
        using self_type = Line3<T>;

        // static values

        // static functions

        // constructors
        Line3(const vector_type &o, const vector_type *d) : _origin(o), _direction(d) {}

        // type conversion
        template <typename U>
        operator Line3<U>() const
        {
            return Line3<U>(static_cast<typename Line3<U>::vector_type>(_origin),
                            static_cast<typename Line3<U>::vector_type>(_direction));
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

        vector_type closestPoint(const vector_type &p) const
        { return pointAt(project(p)); }

        value_type distanceSuqared(const vector_type &p) const
        { return (closestPoint(p) - p).lengthSquared(); }

    private:
        vector_type _origin;
        vector_type _direction;
    };

    using Line3d = Line3<double>;
    using Line3f = Line3<float>;
}

#endif
