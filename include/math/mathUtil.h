#ifndef G3_MATH_MATH_UTIL
#define G3_MATH_MATH_UTIL

namespace g3
{
    namespace mathUtil
    {
        const double pi      = 3.1415926535897932384626433832795;
        const double twoPi   = 2.0 * pi;
        const double halfPi  = 0.5 * pi;
        const double deg2rad = pi / 180.0;
        const double rad2deg = 180 / pi;

        const double zeroTolerance = 1e-08;
        const double epsilon       = 2.2204460492503131e-016;

        const double sqrtTwo    = 1.4142135623730950488016887242097;
        const double sqrtTwoInv = 1.0 / sqrtTwo;
        const double sqrtThree  = 1.7320508075688772935274463415059;

        template<typename T>
        inline T clamp(T value, T low, T high)
        { return (value < low) ? low : (value > high) ? high : value; }
    }
}

#endif
