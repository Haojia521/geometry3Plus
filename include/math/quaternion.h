#ifndef G3_MATH_AUQTERNION
#define G3_MATH_AUQTERNION

#include <cmath>

#include <math/mathUtil.h>
#include <math/matrix3.h>
#include <math/vectorTraits.h>

namespace g3
{
    template<typename T>
    class Quaternion
    {
        typedef typename Vector4Traits<T>::vector_type inner_data_type;
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
        static self_type inverse(const self_type &q)
        { return q.inverse(); }
        static self_type axisAngleDeg(const vector_type &axis, value_type deg)
        { return self_type(axis, deg); }
        static self_type axisAngleRed(const vector_type &axis, value_type rad)
        { return self_type(axis, rad, false); }
        static self_type formTo(const vector_type &from, const vector_type &to)
        { return self_type(from, to); }
        // TODO: add FromToConstrained()
        static self_type slerp(const self_type &p, const self_type &q, value_type t)
        { return self_type(p, q, t); }
        
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
        template<typename U>
        operator Quaternion<U>() const
        {
            return Quaternion<U>(static_cast<typename Quaternion<U>::inner_data_type>(_vec4));
        }

        // functions
        value_type  x() const { return _vec4.x(); }
        value_type  y() const { return _vec4.y(); }
        value_type  z() const { return _vec4.z(); }
        value_type  w() const { return _vec4.w(); }
        value_type& x() { return _vec4.x(); }
        value_type& y() { return _vec4.y(); }
        value_type& z() { return _vec4.z(); }
        value_type& w() { return _vec4.w(); }

        value_type lengthSquared() const
        { return _vec4.lengthSquared(); }

        value_type length() const
        { return _vec4.length(); }

        value_type dot(const self_type &q)
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

        void setAxisAngleRad(const vector_type &axis, value_type angle)
        {
            auto halfAngle = 0.5f * angle;
            auto sn = std::sin(halfAngle);
            _vec4.w() = std::cos(halfAngle);
            _vec4.x() = sn * axis.x();
            _vec4.y() = sn * axis.y();
            _vec4.z() = sn * axis.z();
        }

        void setAxisAngleDeg(const vector_type &axis, value_type angle)
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

        matrix_type toRotationMatrix() const
        {
            auto x2 = x() * 2, y2 = y() * 2, z2 = z() * 2;
            auto wx = w() * x2, wy = w() * y2, wz = w() * z2;
            auto xx = x() * x2, xy = x() * y2, xz = x() * z2;
            auto yy = y() * y2, yz = y() * z2, zz = z() * z2;
            return matrix_type(1 - (yy + zz), xy - wz, xz + wy,
                               xy + wz, 1 - (xx + zz), yz - wx,
                               xz - wy, yz + wx, 1 - (xx + yy));
        }

        vector_type axisX() const
        {
            auto y2 = y() * 2, z2 = z() * 2;
            auto wy = w() * y2, wz = w() * z2, xy = x() * y2;
            auto xz = x() * z2, yy = y() * y2, zz = z() * z2;
            return vector_type(1 - (yy + zz), xy + wz, xz - wy);
        }

        vector_type axisY() const
        {
            auto x2 = x() * 2, y2 = y() * 2, z2 = z() * 2;
            auto wx = w() * x2, wz = w() * z2, xx = x() * x2;
            auto xy = x() * y2, yz = y() * z2, zz = z() * z2;
            return vector_type(xy - wz, 1 - (xx + zz), yz + wx);
        }

        vector_type axisZ() const
        {
            auto x2 = x() * 2, y2 = y() * 2, z2 = z() * 2;
            auto wx = w() * x2, wy = w() * y2, xx = x() * x2;
            auto xz = x() * z2, yy = y() * y2, yz = y() * z2;
            return vector_type(xz + wy, yz - wx, 1 - (xx + yy));
        }

        self_type inverse() const
        {
            auto norm = lengthSquared();
            if (norm > mathUtil::getZeroTolerance<value_type>())
            {
                auto invNorm = ((value_type)1.0) / norm;
                return (conjugate() * invNorm);
            }
            else
                return zero;
        }

        self_type conjugate() const
        { return self_type(-x(), -y(), -z(), w()); }

        bool epsilonEqual(const self_type &q, value_type eps) const
        {
            return std::abs(x() - q.x()) <= eps &&
                   std::abs(y() - q.y()) <= eps &&
                   std::abs(z() - q.z()) <= eps &&
                   std::abs(w() - q.w()) <= eps;
        }

        // operator functions
        value_type  operator [] (int i) const
        { return _vec4[i]; }
        value_type& operator [] (int i)
        { return _vec4[i]; }

        self_type operator - () const
        { return self_type(-_vec4); }

        self_type operator - (const self_type &q) const
        { return self_type(_vec4 - q._vec4); }
        self_type operator - (value_type d) const
        { return self_type(_vec4 - d); }

        self_type operator + (const self_type &q) const
        { return self_type(_vec4 + q._vec4); }
        self_type operator + (value_type d) const
        { return self_type(_vec4 + d); }

        self_type operator * (const self_type &q) const
        {
            const auto &a = _vec4;
            const auto &b = q._vec4;
            auto w = a.w() * b.w() - a.x() * b.x() - a.y() * b.y() - a.z() * b.z();
            auto x = a.w() * b.x() + a.x() * b.w() + a.y() * b.z() - a.z() * b.y();
            auto y = a.w() * b.y() + a.y() * b.w() + a.z() * b.x() - a.x() * b.z();
            auto z = a.w() * b.z() + a.z() * b.w() + a.x() * b.y() - a.y() * b.x();
            return self_type(x, y, z, w);
        }

        self_type operator * (value_type d) const
        { return self_type(_vec4 * d); }
        friend self_type operator * (value_type d, const self_type &q);

        vector_type operator * (const vector_type &v) const
        {
            auto mat = toRotationMatrix();
            return mat * v;
        }

        self_type operator / (value_type d) const
        { return self_type(_vec4 / d); }

        bool operator == (const self_type &q) const
        { return _vec4 == q._vec4; }
        bool operator != (const self_type &q) const
        { return !((*this) == q); }

    private:
        //value_type _x, _y, _z, _w;
        inner_data_type _vec4;
    };

    template<typename T>
    const Quaternion<T> Quaternion<T>::zero = Quaternion<T>(0, 0, 0, 0);
    
    template<typename T>
    const Quaternion<T> Quaternion<T>::indentity = Quaternion<T>();

    template<typename T>
    Quaternion<T> operator * (typename Quaternion<T>::value_type d,
                              const Quaternion<T> &q)
    { return q * d; }

    typedef Quaternion<double> Quaterniond;
    typedef Quaternion<float>  Quaternionf;
}

#endif
