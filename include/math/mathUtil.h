#ifndef G3_MATH_MATH_UTIL
#define G3_MATH_MATH_UTIL

namespace g3
{
    namespace mathUtil
    {
        constexpr double PI      = 3.1415926535897932384626433832795;
        constexpr double twoPI   = 2.0 * PI;
        constexpr double halfPI  = 0.5 * PI;

        constexpr double deg2rad = PI / 180.0;
        constexpr double rad2deg = 180 / PI;

        constexpr double zeroTolerance = 1e-08;
        constexpr double epsilon       = 2.2204460492503131e-016;

        constexpr double sqrtTwo    = 1.4142135623730950488016887242097;
        constexpr double sqrtTwoInv = 1.0 / sqrtTwo;
        constexpr double sqrtThree  = 1.7320508075688772935274463415059;

        template<typename T>
        inline constexpr T getPI() { return static_cast<T>(PI); }
        template<typename T>
        inline constexpr T getTwoPI() { return static_cast<T>(twoPI); }
        template<typename T>
        inline constexpr T getHalfPI() { return static_cast<T>(halfPI); }

        template<typename T>
        inline constexpr T getDeg2Rad() { return static_cast<T>(deg2rad); }
        template<typename T>
        inline constexpr T getRad2Deg() { return static_cast<T>(rad2deg); }

        template<typename T>
        inline constexpr T getZeroTolerance() { return static_cast<T>(zeroTolerance); }
        template<typename T>
        inline constexpr T getEpsilon() { return static_cast<T>(epsilon); }

        template<typename T>
        inline constexpr T getSqrtTwo() { return static_cast<T>(sqrtTwo); }
        template<typename T>
        inline constexpr T getSqrtTwoInv() { return static_cast<T>(sqrtTwoInv); }
        template<typename T>
        inline constexpr T getSqrtThree() { return static_cast<T>(sqrtThree); }

        template<typename T>
        inline T clamp(T value, T low, T high)
        { return (value < low) ? low : (value > high) ? high : value; }

        template<typename T>
        inline T barycentricCoords(const T &vp, const T &v0, const T &v1, const T &v2)
        {
            return barycentricCoords<T, T>(vp, v0, v1, v2);
        }

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
