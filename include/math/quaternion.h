#ifndef G3_MATH_AUQTERNION
#define G3_MATH_AUQTERNION

#include <cmath>

#include <math/mathUtil.h>
#include <math/matrix3.h>
#include <math/vector4d.h>

namespace g3
{
    template<typename T>
    class Quaternion
    {
        typedef typename Vector4Traits<value_type>::vector_type inner_data_type;
        Quaternion(const inner_data_type &data) : _vec4(data) {}
    public:
        typedef typename Vector3Traits<T>::vector_type vector_type;
        typedef typename vector_type::value_type       value_type;
        typedef Matrix3<T>                             matrix_type;
        typedef Quaternion<T>                          self_type;

        // static values
        static const self_type zero;
        static const self_type indentity;

        // static functions
        
        // constructors
        Quaternion() : _vec4(0, 0, 0, 1) {}
        Quaternion(value_type x, value_type y, value_type z, value_type w) : 
            _vec4(x, y, z, w) {}
        Quaternion(const vector_type &axis, value_type angle, bool isDeg = true) : Quaternion()
        { if (isDeg) setAxisAngleDeg(axis, angle); else setAxisAngleRad(axis, angle); }
        Quaternion(const vector_type &from, const vector_type &to) : Quaternion()
        { setFromTo(from, to); }
        Quaternion(const self_type &p, const self_type &q, value_type t) : Quaternion()
        { setToSlerp(p, q, t); }
        Quaternion(const matrix_type &m) : Quaternion()
        { setFromRotationMatrix(m); }

        // copy constructors
        
        // type conversion
        
        // functions
        inline value_type  x() const { return _vec4.x(); }
        inline value_type  y() const { return _vec4.y(); }
        inline value_type  z() const { return _vec4.z(); }
        inline value_type  w() const { return _vec4.w(); }
        inline value_type& x() { return _vec4.x(); }
        inline value_type& y() { return _vec4.y(); }
        inline value_type& z() { return _vec4.z(); }
        inline value_type& w() { return _vec4.w(); }

        inline value_type lengthSquared() const
        { return _vec4.lengthSquared(); }

        inline value_type length() const
        { return _vec4.length(); }

        inline value_type dot(const self_type &q)
        { return _vec4.dot(q._vec4); }

        value_type normalize(value_type epsilon = mathUtil::getZeroTolerance<value_type>())
        {
            return _vec4.normalize(epsilon);
        }

        self_type normalized() const
        {
            self_type q(*this);
            q.normalize();
            return q;
        }

        inline void setAxisAngleRad(const vector_type &axis, value_type angle)
        {
            auto halfAngle = 0.5f * angle;
            auto sn = std::sin(halfAngle);
            _vec4.w() = std::cos(halfAngle);
            _vec4.x() = sn * axis.x();
            _vec4.y() = sn * axis.y();
            _vec4.z() = sn * axis.z();
        }

        inline void setAxisAngleDeg(const vector_type &axis, value_type angle)
        { setAxisAngleRad(axis, angle * mathUtil::getDeg2Rad<value_type>()); }

        // this function can take non-normalized vectors vFrom and vTo (normalizes internally)
        void setFromTo(const vector_type &vFrom, const vector_type &vTo)
        {
            // [TODO] this page seems to have optimized version:
            //    http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors

            // [RMS] not ideal to explicitly normalize here, but if we don't,
            //   output quaternion is not normalized and this causes problems,
            //   eg like drift if we do repeated SetFromTo()

            auto from = vFrom.normalized(), to = vTo.normalized();
            auto bisector = (from + to).normalized();
            _vec4.w() = from.dot(bisector);
            if (std::abs(_vec4.w()) > mathUtil::getZeroTolerance<value_type>())
            {
                auto cross = from.cross(bisector);
                _vec4.x() = cross.x(); _vec4.y() = cross.y(); _vec4.z() = cross.z();
            }
            else
            {
                _vec4.w() = 0;
                if (std::abs(from.x()) >= std::abs(from.y()))
                {
                    auto invLength = ((value_type)1) / std::sqrt(from.x() * from.x() + from.z() * from.z());
                    _vec4.x() = -from.z() * invLength;
                    _vec4.y() = 0;
                    _vec4.z() = from.x() * invLength;
                }
                else
                {
                    auto invLength = ((value_type)1) / std::sqrt(from.y() * from.y() + from.z() * from.z());
                    _vec4.x() = 0;
                    _vec4.y() = from.z() * invLength;
                    _vec4.z() = -from.y() * invLength;
                }
            }
            normalize();
        }

        void setToSlerp(const self_type &p, const self_type &q, value_type t)
        {
            auto cs = p.dot(q);
            auto angle = std::acos(cs);
            if (std::abs(angle) >= mathUtil::getZeroTolerance<value_type>())
            {
                auto sn = std::sin(angle);
                auto invSn = 1 / sn;
                auto tAngle = t * angle;
                auto coeff0 = std::sin(angle - tAngle) * invSn;
                auto coeff1 = std::sin(tAngle) * invSn;
                _vec4.x() = coeff0 * p.x() + coeff1 * q.x();
                _vec4.y() = coeff0 * p.y() + coeff1 * q.y();
                _vec4.z() = coeff0 * p.z() + coeff1 * q.z();
                _vec4.w() = coeff0 * p.w() + coeff1 * q.w();
            }
            else { _vec4.x() = p.x(); _vec4.y() = p.y(); _vec4.z() = p.z(); _vec4.w() = p.w(); }
        }

        void setFromRotationMatrix(const matrix_type &m)
        {
            // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
            // article "Quaternion Calculus and Fast Animation".
            int next[] { 1, 2, 0 };

            auto trace = m[0][0] + m[1][1] + m[2][2];
            if (std::abs(trace) > mathUtil::getZeroTolerance<value_type>())
            {
                auto root = std::sqrt(trace + 1);
                _vec4.w() = 0.5f * root;
                root = 0.5f / root;
                _vec4.x() = (m[2][1] - m[1][2]) * root;
                _vec4.y() = (m[0][2] - m[2][0]) * root;
                _vec4.z() = (m[1][0] - m[0][1]) * root;
            }
            else
            {
                int i = 0;
                if (m[1][1] > m[0][0]) i = 1;
                if (m[2][2] > m[i][i]) i = 2;

                int j = next[i];
                int k = next[j];

                auto root = std::sqrt(m[i][i] - m[j][j] - m[k][k] + 1);

                value_type quat { _vec4.x(), _vec4.y(), _vec4.z() };
                quat[i] = 0.5f * root;
                root = 0.5f / root;
                _vec4.w() = (m[k][j] - m[j][k]) * root;
                quat[j] = (m[j][i] - m[i][j]) * root;
                quat[k] = (m[k][i] - m[i][k]) * root;
                _vec4.x() = quat[0]; _vec4.y() = quat[1]; _vec4.z() = quat[2];
            }
            normalize();
        }

        // operator functions
        inline value_type  operator [] (int i) const
        { return _vec4[i]; }
        inline value_type& operator [] (int i)
        { return _vec4[i]; }

        inline self_type operator - () const
        { return self_type(-_vec4); }

        inline self_type operator - (const self_type &q) const
        { return self_type(_vec4 - q._vec4); }
        inline self_type operator - (value_type d) const
        { return self_type(_vec4 - d); }

    private:
        //value_type _x, _y, _z, _w;
        inner_data_type _vec4;
    };
}

#endif
