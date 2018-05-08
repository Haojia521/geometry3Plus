#ifndef G3_MATH_MATH_UTIL
#define G3_MATH_MATH_UTIL

namespace g3
{
    namespace mathUtil
    {
        const double PI      = 3.1415926535897932384626433832795;
        const double twoPI   = 2.0 * PI;
        const double halfPI  = 0.5 * PI;

        const double deg2rad = PI / 180.0;
        const double rad2deg = 180 / PI;

        const double zeroTolerance = 1e-08;
        const double epsilon       = 2.2204460492503131e-016;

        const double sqrtTwo    = 1.4142135623730950488016887242097;
        const double sqrtTwoInv = 1.0 / sqrtTwo;
        const double sqrtThree  = 1.7320508075688772935274463415059;

        template<typename T>
        inline T getPI() { return static_cast<T>(PI); }
        template<typename T>
        inline T getTwoPI() { return static_cast<T>(twoPI); }
        template<typename T>
        inline T getHalfPI() { return static_cast<T>(halfPI); }

        template<typename T>
        inline T getDeg2Rad() { return static_cast<T>(deg2rad); }
        template<typename T>
        inline T getRad2Deg() { return static_cast<T>(rad2deg); }

        template<typename T>
        inline T getZeroTolerance() { return static_cast<T>(zeroTolerance); }
        template<typename T>
        inline T getEpsilon() { return static_cast<T>(epsilon); }

        template<typename T>
        inline T getSqrtTwo() { return static_cast<T>(sqrtTwo); }
        template<typename T>
        inline T getSqrtTwoInv() { return static_cast<T>(sqrtTwoInv); }
        template<typename T>
        inline T getSqrtThree() { return static_cast<T>(sqrtThree); }

        template<typename T>
        inline T clamp(T value, T low, T high)
        { return (value < low) ? low : (value > high) ? high : value; }

        template<typename T, typename U>
        inline U barycentricCoords(const T &vp, const T &v0, const T &v1, const T &v2)
        {
            auto kV02 = v0 - v2;
            auto kV12 = v1 - v2;
            auto kPV2 = vp - v2;
            auto fM00 = kV02.dot(kV02);
            auto fM01 = kV02.dot(kV12);
            auto fM11 = kV12.dot(kV12);
            auto fR0  = kV02.dot(kPV2);
            auto fR1  = kV12.dot(kPV2);
            auto fDet = fM00 * fM11 - fM01 * fM01;
            auto fInvDet = 1 / fDet;
            auto fBary1 = (fM11 * fR0 - fM01 * fR1) * fInvDet;
            auto fBary2 = (fM00 * fR1 - fM01 * fR0) * fInvDet;
            auto fBary3 = 1 - fBary1 - fBary2;
            return U(fBary1, fBary2, fBary3);
        }
    }
}

#endif
