#ifndef G3_MATH_MATRIX_3
#define G3_MATH_MATRIX_3

#include <cmath>
#include <vector>
#include <functional>

#include <math/mathUtil.h>
#include <math/vectorTraits.h>

namespace g3
{
    template<typename T>
    class Matrix3
    {
    public:
        typedef typename Vector3Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef Matrix3<T>                             self_type;

        // static values
        static const self_type identity;
        static const self_type zero;

        // static functions

        // constructors
        Matrix3(bool isIdentity = false)
        {
            if (isIdentity)
            { _row0 = vector_type::axisX; _row1 = vector_type::axisY; _row2 = vector_type::axisZ; }
            else
            { _row0 = _row1 = _row2 = vector_type::zero; }
        }
        Matrix3(const std::vector<value_type> m)  // assume input is row-major and no check of out-of-range exception
        {
            _row0.set(m[0], m[1], m[2]);
            _row1.set(m[3], m[4], m[5]);
            _row2.set(m[6], m[7], m[8]);
        }
        Matrix3(const std::vector<std::vector<value_type>> m) // no check of out-of-range exception
        {
            _row0.set(m[0][0], m[0][1], m[0][2]);
            _row1.set(m[1][0], m[1][1], m[1][2]);
            _row2.set(m[2][0], m[2][1], m[2][2]);
        }
        Matrix3(const std::function<value_type(int)> &f) // assume input is row-major
        {
            _row0.set(f(0), f(1), f(2));
            _row1.set(f(3), f(4), f(5));
            _row2.set(f(6), f(7), f(8));
        }
        Matrix3(const std::function<value_type(int, int)> &f)
        {
            _row0.set(f(0, 0), f(0, 1), f(0, 2));
            _row1.set(f(1, 0), f(1, 1), f(1, 2));
            _row2.set(f(2, 0), f(2, 1), f(2, 2));
        }
        Matrix3(value_type m00, value_type m11, value_type m22)
        { _row0.set(m00, 0, 0); _row1.set(0, m11, 0); _row2.set(0, 0, m22); }
        Matrix3(const vector_type &v0, const vector_type &v1, const vector_type &v2,
                bool beColumns)
        {
            if (beColumns)
            {
                _row0.set(v0[0], v1[0], v2[0]);
                _row1.set(v0[1], v1[1], v2[1]);
                _row2.set(v0[2], v1[2], v2[2]);
            }
            else { _row0 = v0; _row1 = v1; _row2 = v2; }
        }
        Matrix3(value_type m00, value_type m01, value_type m02,
                value_type m10, value_type m11, value_type m12,
                value_type m20, value_type m21, value_type m22)
        {
            _row0.set(m00, m01, m02);
            _row1.set(m10, m11, m12);
            _row2.set(m20, m21, m22);
        }

        // type conversion
        template<typename U>
        operator Matrix3<U>() const
        {
            return Matrix3<U>(static_cast<typename Matrix3<U>::vector_type>(_row0),
                              static_cast<typename Matrix3<U>::vector_type>(_row1),
                              static_cast<typename Matrix3<U>::vector_type>(_row2), false);
        }

        // functions
        vector_type row(int i) const
        { return (i == 0) ? _row0 : (i == 1) ? _row1 : _row2; }

        vector_type column(int i) const
        {
            return (i == 0) ? vector_type(_row0[0], _row1[0], _row2[0]) : 
                   (i == 1) ? vector_type(_row0[1], _row1[1], _row2[1]) : 
                              vector_type(_row0[2], _row1[2], _row2[2]);
        }

        void toBuffer(value_type buffer[]) const // no check of out-of-range exception
        {
            buffer[0] = _row0[0]; buffer[1] = _row0[1]; buffer[2] = _row0[2];
            buffer[3] = _row1[0]; buffer[4] = _row1[1]; buffer[5] = _row1[2];
            buffer[6] = _row2[0]; buffer[7] = _row2[1]; buffer[8] = _row2[2];
        }

        value_type determinant() const
        {
            auto x0 = _row2[2] * _row1[1] - _row2[1] * _row1[2];
            auto x1 = -(_row2[2] * _row0[1] - _row2[1] * _row0[2]);
            auto x2 = _row1[2] * _row0[1] - _row1[1] * _row0[2];
            return (_row0[0] * x0 + _row1[0] * x1 + _row2[0] * x2);
        }

        self_type inverse(value_type epsilon = mathUtil::getEpsilon<value_type>()) const
        {
            auto det = determinant();
            if (std::abs(det) > epsilon)
            {
                auto invDet = 1 / det;

                auto x00 = (_row2[2] * _row1[1] - _row2[1] * _row1[2]) * invDet;
                auto x01 = -(_row2[2] * _row0[1] - _row2[1] * _row0[2]) * invDet;
                auto x02 = (_row1[2] * _row0[1] - _row1[1] * _row0[2]) * invDet;

                auto x10 = -(_row2[2] * _row1[0] - _row2[0] * _row1[2]) * invDet;
                auto x11 = (_row2[2] * _row0[0] - _row2[0] * _row0[2]) * invDet;
                auto x12 = -(_row1[2] * _row0[0] - _row1[0] * _row0[2]) * invDet;

                auto x20 = (_row2[1] * _row1[0] - _row2[0] * _row1[1]) * invDet;
                auto x21 = -(_row2[1] * _row0[0] - _row2[0] * _row0[1]) * invDet;
                auto x22 = (_row1[1] * _row0[0] - _row1[0] * _row0[1]) * invDet;

                return self_type(x00, x01, x02, x10 , x11, x12, x20, x21, x22);
            }
            else
                return zero;
        }

        self_type transpose() const
        { return self_type(_row0, _row1, _row2, true); }

        bool epsilonEqual(const self_type &m, value_type epsilon) const
        {
            return _row0.epsilonEqual(m._row0, epsilon) && 
                   _row1.epsilonEqual(m._row1, epsilon) && 
                   _row2.epsilonEqual(m._row2, epsilon);
        }

        // operator functions
        vector_type& operator [] (int r)
        { return (r == 0) ? _row0 : (r == 1) ? _row1 : _row2; }
        vector_type  operator [] (int r) const
        { return (r == 0) ? _row0 : (r == 1) ? _row1 : _row2; }

        self_type operator - () const
        { return self_type(-_row0, -_row1, -_row2, false); }
        self_type operator - (const self_type &m) const
        { return self_type(_row0 - m._row0, _row1 - m._row1, _row2 - m._row2, false); }
        self_type operator - (value_type n) const
        { return self_type(_row0 - n, _row1 - n, _row2 - n, false); }

        self_type operator + (const self_type &m) const
        { return self_type(_row0 + m._row0, _row1 + m._row1, _row2 + m._row2, false); }
        self_type operator + (value_type n) const
        { return self_type(_row0 + n, _row1 + n, _row2 + n, false); }

        self_type operator * (const self_type &m) const
        {
            auto mCol0 = m.column(0), mCol1 = m.column(1), mCol2 = m.column(2);
            auto m00 = _row0.dot(mCol0), m01 = _row0.dot(mCol1), m02 = _row0.dot(mCol2);
            auto m10 = _row1.dot(mCol0), m11 = _row1.dot(mCol1), m12 = _row1.dot(mCol2);
            auto m20 = _row2.dot(mCol0), m21 = _row2.dot(mCol1), m22 = _row2.dot(mCol2);
            return self_type(m00, m01, m02, m10, m11, m12, m20, m21, m22);
        }
        self_type operator * (value_type n) const
        { return self_type(_row0 * n, _row1 * n, _row2 * n, false); }
        template<typename T>
        friend Matrix3<T> operator * (typename Matrix3<T>::value_type n, const Matrix3<T> &m);

        self_type operator / (value_type n) const
        { return self_type(_row0 / n, _row1 / n, _row2 / n, false); }

        vector_type operator * (const vector_type &v) const
        { return vector_type(_row0.dot(v), _row1.dot(v), _row2.dot(v)); }
        template<typename T>
        friend typename Matrix3<T>::vector_type operator * (const typename Matrix3<T>::vector_type &v, const Matrix3<T> &m);

    private:
        vector_type _row0, _row1, _row2;
    };

    template<typename T>
    const Matrix3<T> Matrix3<T>::identity = Matrix3<T>(true);

    template<typename T>
    const Matrix3<T> Matrix3<T>::zero = Matrix3<T>();

    template<typename T>
    Matrix3<T> operator * (typename Matrix3<T>::value_type n, const Matrix3<T> &m)
    { return Matrix3<T>(m._row0 * n, m._row1 * n, m._row2 * n, false); }

    template<typename T>
    typename Matrix3<T>::vector_type operator * (const typename Matrix3<T>::vector_type &v, const Matrix3<T> &m)
    { return Matrix3<T>::vector_type(v.dot(m.column(0)), v.dot(m.column(1)), v.dot(m.column(2))); }

    typedef Matrix3<double> Matrix3d;
    typedef Matrix3<float>  Matrix3f;
}

#endif
