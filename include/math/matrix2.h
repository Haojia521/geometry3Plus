#ifndef G3_MATH_MATRIX_2
#define G3_MATH_MATRIX_2

#include <cmath>

#include <math/mathUtil.h>
#include <math/vector2d.h>

namespace g3
{
    template<typename VecT>
    class Matrix2
    {
    public:
        typedef VecT                             vector_type;
        typedef typename vector_type::value_type value_type;
        typedef Matrix2<vector_type>             self_type;

        // static values
        static const self_type identity;
        static const self_type zero;
        static const self_type one;

        // static functions

        // constructors
        Matrix2(bool isIdentity = false)
        {
            if (isIdentity)
            {
                _row0[0] = _row1[1] = 1;
                _row0[1] = _row1[0] = 0;
            }
            else
            { _row0[0] = row0[1] = _row1[0] = _row1[1] = 0; }
        }
        Matrix2(value_type m00, value_type m01, value_type m10, value_type m11)
        { _row0[0] = m00; _row0[1] = m01; _row1[0] = m10; _row1[1] = m11; }
        Matrix2(value_type m00, value_type m11)
        { _row0[0] = m00; _row1[1] = m11; _row0[1] = _row1[0] = 0; }
        Matrix2(value_type angle, bool isDegree = false)
        {
            if (isDegree) ;
            else ;
        }
        Matrix2(const vector_type &u, const vector_type &v, bool beColumns)
        {
            if (beColumns) { _row0[0] = u[0]; _row0[1] = v[0]; _row1[0] = u[1]; _row1[1] = v[1]; }
            else { _row0 = u; _row1 = v; }
        }
        Matrix2(const vector_type &u, const vector_type &v) // tensor product of u,v --> u * v^T
        {
            _row0[0] = u.x() * v.x();
            _row0[1] = u.x() * v.y();
            _row1[0] = u.y() * v.x();
            _row1[1] = u.y() * v.y();
        }

        // type conversion

        // functions
        inline void setToRow(const vector_type &u, const vector_type &v)
        { _row0 = u; _row1 = v; }

        inline void setToRow(value_type m00, value_type m01, value_type m10, value_type m11)
        { _row0[0] = m00; _row0[1] = m01; _row1[0] = m10; _row1[1] = m11; }

        inline void setToColumn(const vector_type &u, const vector_type &v)
        { _row0[0] = u[0]; _row0[1] = v[0]; _row1[0] = u[1]; _row1[1] = v[1]; }

        inline void setToColumn(value_type m00, value_type m10, value_type m01, value_type m11)
        { _row0[0] = m00; _row0[1] = m01; _row1[0] = m10; _row1[1] = m11; }

        inline void setToDiagonal(value_type m00, value_type m11)
        { _row0[0] = m00; _row1[1] = m11; _row0[1] = _row1[0] = 0; }

        inline void setToRotationRad(value_type angle)
        {
            _row0[0] = _row1[1] = std::cos(angle);
            _row1[0] = std::sin(angle);
            _row0[1] = -_row1[0];
        }

        inline void setToRotationDeg(value_type anlge)
        { setToRotationRad(anlge * mathUtil::getRad2Deg<value_type>()); }

        inline value_type qForm(const vector_type &u, const vector_type &v) const
        { return u.dot((*this) * v); }

        inline self_type transpose() const
        { return self_type(_row0[0], _row1[0], _row0[1], _row1[1]); }

        inline self_type inverse(value_type epsilon = mathUtil::getEpsilon<value_type>())
        {
            auto det = determinant();
            if (std::abs(det) > epsilon)
            {
                auto invDet = 1 / det;
                return (adjoint() * invDet);
            }
            else
                return zero;
        }

        inline self_type adjoint() const
        { return self_type(_row1[1], -_row0[1], -_row1[0], _row0[0]); }

        inline value_type determinant() const
        { return _row0[0] * _row1[1] - _row0[1] * _row1[0]; }

        // pre-condition: this matrix represents a rotation
        inline value_type extractAngle()
        { return std::atan2(_row1[0], _row0[0]); }

        inline vector_type row(int i) const
        { return (i == 0) ? _row0; _row1; }

        inline vector_type column(int i) const
        { return (i == 0) ? vector_type(_row0[0], _row1[0]) : vector_type(_row0[1], _row1[1]); }

        // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
        // M = [m0|m1], then orthonormal output matrix is Q = [q0|q1],
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //
        // where |V| indicates length of vector V and A*B indicates dot
        // product of vectors A and B.
        void orthonormalize()
        {
            vector_type col0 = column(0), col1 = column(1);

            // compute q0
            auto invLength = 1 / col0.length();
            col0 = col0 * invLength;

            // compute q1
            auto dot0 = col0.dot(col1);
            col1 = col1 - (col0 * dot0);
            invLength = 1 / col1.length();
            col1 = col1 * invLength;

            setToColumn(col0, col1);
        }

        void eigenDecomposition(self_type &rot, self_type &diag)
        {
            if (std::abs(_row0[1]) < mathUtil::getZeroTolerance<value_type>() &&
                std::abs(_row1[0]) < mathUtil::getZeroTolerance<value_type>())
            {
                // This matrix is diagonal (within numerical round-off).
                rot.setToRow(1, 0, 0, 1);
                diag.setToRow(_row0[0], 0, 0, _row1[1]);
                return;
            }

            auto trace = _row0[0] + _row1[1];
            auto diff = _row0[0] - _row1[1];
            auto discr = std::sqrt(diff * diff + _row0[1] * _row0[1] * 4);
            auto eigVal0 = 0.5f * (trace - discr);
            auto eigVal1 = 0.5f * (trace + discr);
            diag.setToDiagonal(eigVal0, eigVal1);

            auto cs = (diff >= 0) ? _row0[1] : (eigVal0 - _row1[1]);
            auto sn = (diff >= 0) ? (eigVal0 - _row0[0]) : _row0[1];

            auto invLength = 1 / std::sqrt(cs * cs + sn * sn);
            cs *= invLength;
            sn *= invLength;

            rot.setToRow(cs, -sn, sn, cs);
        }

        // operator functions
        inline value_type& operator [] (int r, int c)
        { return (r == 0) ? _row0[c] : _row1[c]; }
        inline value_type  operator [] (int r, int c) const
        { return (r == 0) ? _row0[c] : _row1[c]; }

        inline self_type operator - () const
        { return self_type(-_row0, -_row1, false); }
        inline self_type operator - (const self_type &m) const
        { return self_type(_row0 - m._row0, _row1 - m._row1, false); }
        inline self_type operator - (value_type n) const
        { return self_type(_row0 - n, _row1 - n, false); }

        inline self_type operator + (const self_type &m) const
        { return self_type(_row0 + m._row0, _row1 + m._row1, false); }
        inline self_type operator + (value_type n) const
        { return self_type(_row0 + n, _row1 + n, false); }

        inline self_type operator * (value_type n) const
        { return self_type(_row0 * n, _row1 * n, false); }
        friend self_type operator * (value_type n, const self_type &m);

        inline self_type operator / (value_type n) const
        { return self_type(_row0 / n, _row1 / n, false); }

        inline vector_type operator * (const vector_type &v) const
        { return vector_type(_row0.dot(v), _row1.dot(v)); }
        friend vector_type operator * (const vector_type &v, const self_type &m);

    private:
        vector_type _row0, _row1;
    };

    template<typename T>
    inline Matrix2<T> operator * (Matrix2<T>::value_type n, const Matrix2<T> &m)
    { return Matrix2<T>(m._row0 * n, m._row1 * n, false); }

    template<typename T>
    inline Matrix2<T>::vector_type operator * (const Matrix2<T>::vector_type &v, const Matrix2<T> &m)
    { return Matrix2<T>::vector_type(m._row0.dot(v), m._row1.dot(v)); }

    typedef Matrix2<Vector2d> Matrix2d;
    typedef Matrix2<Vector2f> Matrix2f;
}

#endif
