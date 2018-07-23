#ifndef G3_MATH_AUQTERNION
#define G3_MATH_AUQTERNION

#include <cmath>

#include <math/mathUtil.h>
#include <math/matrix3.h>

namespace g3
{
    template<typename T>
    class Quaternion
    {
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
        Quaternion() : _x(0), _y(0), _z(0), _w(1) {}
        Quaternion(value_type x, value_type y, value_type z, value_type w) : 
            _x(x), _y(y), _z(z), _w(w) {}
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
        inline value_type  x() const { return _x; }
        inline value_type  y() const { return _y; }
        inline value_type  z() const { return _z; }
        inline value_type  w() const { return _w; }
        inline value_type& x() { return _x; }
        inline value_type& y() { return _y; }
        inline value_type& z() { return _z; }
        inline value_type& w() { return _w; }

        inline value_type lengthSquared() const
        { return _x * _x + _y * _y + _z * _z + _w * _w; }

        inline value_type length() const
        { return std::sqrt(lengthSquared()); }

        inline value_type dot(const self_type &q)
        { return _x * q._x + _y * q._y + _z * q._z + _w * q._w; }

        value_type normalize(value_type epsilon = mathUtil::getZeroTolerance<value_type>())
        {
            auto len = length();
            if (len > epsilon)
            {
                auto invLen = 1 / len;
                _x *= invLen; _y *= invLen; _z = *= invLen; _w *= invLen;
            }
            else
            {
                len = 0;
                _x = _y = _z = _w = 0;
            }
            return len;
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
            w = std::cos(halfAngle);
            x = sn * axis.x();
            y = sn * axis.y();
            z = sn * axis.z();
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
            _w = from.dot(bisector);
            if (std::abs(_w) > mathUtil::getZeroTolerance<value_type>())
            {
                auto cross = from.cross(bisector);
                _x = cross.x(); _y = cross.y(); _z = cross.z();
            }
            else
            {
                _w = 0;
                if (std::abs(from.x()) >= std::abs(from.y()))
                {
                    auto invLength = ((value_type)1) / std::sqrt(from.x() * from.x() + from.z() * from.z());
                    _x = -from.z() * invLength;
                    _y = 0;
                    _z = from.x() * invLength;
                }
                else
                {
                    auto invLength = ((value_type)1) / std::sqrt(from.y() * from.y() + from.z() * from.z());
                    _x = 0;
                    _y = from.z() * invLength;
                    _z = -from.y() * invLength;
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
                _x = coeff0 * p.x() + coeff1 * q.x();
                _y = coeff0 * p.y() + coeff1 * q.y();
                _z = coeff0 * p.z() + coeff1 * q.z();
                _w = coeff0 * p.w() + coeff1 * q.w();
            }
            else { _x = p.x(); _y = p.y(); _z = p.z(); _w = p.w(); }
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
                _w = 0.5f * root;
                root = 0.5f / root;
                _x = (m[2][1] - m[1][2]) * root;
                _y = (m[0][2] - m[2][0]) * root;
                _z = (m[1][0] - m[0][1]) * root;
            }
            else
            {
                int i = 0;
                if (m[1][1] > m[0][0]) i = 1;
                if (m[2][2] > m[i][i]) i = 2;

                int j = next[i];
                int k = next[j];

                auto root = std::sqrt(m[i][i] - m[j][j] - m[k][k] + 1);

                value_type quat { _x, _y, _z };
                quat[i] = 0.5f * root;
                root = 0.5f / root;
                _w = (m[k][j] - m[j][k]) * root;
                quat[j] = (m[j][i] - m[i][j]) * root;
                quat[k] = (m[k][i] - m[i][k]) * root;
                _x = quat[0]; _y = quat[1]; _z = quat[2];
            }
            normalize();
        }

        // operator functions
        inline value_type  operator [] (int i) const
        { return (i == 0) ? _x : (i == 1) ? _y : (i == 2) ? _z : _w; }
        inline value_type& operator [] (int i)
        { return (i == 0) ? _x : (i == 1) ? _y : (i == 2) ? _z : _w; }

        inline self_type operator - () const
        { return self_type(-_x, -_y, -_z, -_w); }

        inline self_type operator - (const self_type &q)
        { return self_type(_x - q._x, _y - q._y, _z - q._z, _w - q._w); }
        inline self_type operator - (value_type d)
        { return self_type(_x - d, _y - d, ) }

    private:
        value_type _x, _y, _z, _w;
    };
}

#endif
