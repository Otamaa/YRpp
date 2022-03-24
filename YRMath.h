#pragma once

#include <YRPPCore.h>
#include <cmath>
#include <algorithm>

#define MATH_FUNC(name, address)\
	inline NAKED double __cdecl name(double value)\
	{\
		JMP(address);\
	}

#define MATH_FUNC_TWOVAL(name, address)\
	inline NAKED double __cdecl name(double valuea , double valueb)\
	{\
		JMP(address);\
	}

#define MATH_FUNC_FLOAT(name, address)\
	inline NAKED float __stdcall name(float value)\
	{\
		JMP(address);\
	}

#define MATH_FUNC_TWOVAL_FLOAT(name, address)\
	inline NAKED float __stdcall name(float valuea , float valueb)\
	{\
		JMP(address);\
	}

namespace Math
{
	constexpr auto const Pif = 3.1415927f;
	constexpr auto const SMALL_FLOAT = 0.0000001f;
	constexpr auto const HalfPiF = 1.57079632f;
	constexpr auto const Pi = 3.1415926535897932384626433832795;
	constexpr auto const C_Sharp_Pi = 3.1415926535897931;
	constexpr auto const TwoPi = 6.283185307179586476925286766559;
	constexpr auto const HalfPi = 1.5707963267948966192313216916398;
	constexpr auto const Sqrt2 = 1.4142135623730950488016887242097;
	constexpr auto const Sqrt3 = 1.73205080756887719318f;
	constexpr auto const Sqrtoo2 = 0.7071067811865475244008442f;
	constexpr auto const Sqrtoo3 = 0.5773502691896257645091489f;
	constexpr auto const Sqrtoo6 = 0.4082482904638630163662140f;
	constexpr auto const epsilon = 0.0001f;
	constexpr auto const EPSILON = 1.0E-6;
	constexpr auto const short_epsilon = 0.1f;
	constexpr auto const float_max = FLT_MAX;
	constexpr auto const float_min = FLT_MIN;
	constexpr auto const float_tiny = 1.0e-37f;
	constexpr auto const E = 2.71828182845904523536f; // Holds the value for "e": Euler's number or Napier's constant, to 15 significant figures. This is a mathematically useful number.
	constexpr auto const LOG2E = 1.44269504088896340736f;
	constexpr auto const LOG10E = 0.434294481903251827651f;
	constexpr auto const LN2 = 0.693147180559945309417f;
	constexpr auto const LN10 = 2.30258509299404568402f;
	constexpr auto const P4 = 0.785398163397448309616f;// Holds the value for PI / 4 OR 45 degrees. Only up to 16 significant figures.
	constexpr auto const P8 = 0.39269908169872413f; // Holds the value for PI / 8 OR 22.5 degrees. Only up to 17 significant figures.
	constexpr auto const P16 = 0.19634954084936206f; // Holds the value for PI / 16 OR 11.25 degrees. Only up to 17 significant figures.
	constexpr auto const PI = 0.318309886183790671538f;
	constexpr auto const _2_PI = 0.636619772367581343076f;
	constexpr auto const _1_SQRTPI = 0.564189583547756286948f;
	constexpr auto const _2_SQRTPI = 1.12837916709551257390f;
	constexpr auto const THREE_PI_2 = 4.7123889803846895f; // Holds the value for 3 * PI_2 OR 270 degrees. Only up to 17 significant figures.
	constexpr auto const TIGHT_CORNER_RADIUS = 0.5f;
	constexpr auto const RAD_TO_DEG = 57.295779513082325225835265587527f; // Holds the value for 180 / PI which is used to convert radians to degrees.
	constexpr auto const DEG_TO_RAD = 0.017453292519943294444444444444444f; // Holds the value for PI / 180 which is used to convert degrees to radians.
	constexpr auto const DEG90_AS_RAD = 1.570796326794897;
	constexpr auto const BINARY_ANGLE_MAGIC_VALUE = -10430.06004058427;
	constexpr const float ZERO = (float)1e-7;
	constexpr const float PI_HALVES = 0.50f * Math::PI;
	constexpr const float PI_THIRDS = Math::PI * 0.3333333333333f;
	constexpr const float PI_FOURTHS = 0.25f * Math::PI;
	constexpr const float PI_SIXTHS = Math::PI * 0.6666666666667f;
	constexpr const float PI_2 = 2.00f * Math::PI;
	constexpr const float PI_DIV180 = Math::PI / 180.0f;
	constexpr const float PI_INVx180 = 180.0f / Math::PI;
	constexpr const float PI_INV = 1.0f / Math::PI;
	constexpr const double DEG_TO_RAD_Double = Math::Pi / 180;
	constexpr const double BINARY_ANGLE_MAGIC = -(360.0 / (65535 - 1)) * DEG_TO_RAD;
	constexpr const double DEG_TO_RAD_ALTERNATE = C_Sharp_Pi / 180;
	constexpr const double BINARY_ANGLE_MAGIC_ALTERNATE = -(360.0 / (65535 - 1)) * DEG_TO_RAD_ALTERNATE;

	MATH_FUNC(sqrt,	 0x4CAC40);
	MATH_FUNC(sin,	 0x4CACB0);
	MATH_FUNC(cos,	 0x4CAD00);
	MATH_FUNC(tan,	 0x4CAD50);
	MATH_FUNC(asin,	 0x4CAD80);
	MATH_FUNC(acos,	 0x4CADB0);
	MATH_FUNC(atan,	 0x4CADE0);
	MATH_FUNC_TWOVAL(atan2, 0x4CAE30);

	MATH_FUNC_FLOAT(sqrt, 0x4CB060);
	MATH_FUNC_FLOAT(sin, 0x4CB150);
	MATH_FUNC_FLOAT(cos, 0x4CB1A0);
	MATH_FUNC_FLOAT(asin, 0x4CB260);
	MATH_FUNC_FLOAT(acos, 0x4CB290);
	MATH_FUNC_FLOAT(tan, 0x4CB320);
	MATH_FUNC_FLOAT(atan, 0x4CB480);
	MATH_FUNC_TWOVAL_FLOAT(atan2, 0x4CB3D0);

	MATH_FUNC_TWOVAL(arctanfoo , 0x4CAE30)

	//famous Quaqe 3 Fast Inverse Square Root
	inline float Q_invsqrt(float number)
	{
		static_assert(std::numeric_limits<float>::is_iec559); // (enable only on IEEE 754)

		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long *)&y;						  // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);               // what the fuck?
		y = *(float *)&i;
		y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	 // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration,this can be removed

		return y;
	}

	inline constexpr double rad2deg(double rad)
	{
		return rad * 180.0 / Pi;
	}

	inline constexpr double rad2deg_Alternate(double rad)
	{
		return rad * 180.0 / C_Sharp_Pi;
	}

	template <typename T>
	inline double stdsqrt(T val) { return std::sqrt(val); }
	inline constexpr double deg2rad(double deg)
	{
		return deg * Pi / 180.0;
	}

	inline constexpr double deg2rad_Alternate(double deg)
	{
		return deg * C_Sharp_Pi / 180.0;
	}

	template <typename T>
	inline constexpr int sgn(T val) {
		// http://stackoverflow.com/a/4609795
		return (T(0) < val) - (val < T(0));
	}

	template <typename T>
	using value_return_t = std::remove_cv_t<std::remove_reference_t<T>>;

	template<class T>
	inline constexpr T min(T a, T b)
	{
		if (a < b) return(a);
		return(b);
	}

	template<class T>
	inline constexpr T LessOrEqualTo(T a, T b)
	{
		if (a <= b) return(a);
		return(b);
	}

	template<class T>
	inline constexpr T MoreOrEqualTo(T a, T b)
	{
		if (a >= b) return(a);
		return(b);
	}

	template<class T>
	inline constexpr T max(T a, T b)
	{
		if (a > b) return(a);
		return(b);
	}

	inline constexpr auto limit(int value, int limit)
	{
		if (limit <= 0)
		{
			return max(value, -limit);
		}
		else
		{
			return min(value, limit);
		}
	}

	template <typename T, typename TMin, typename TMax>
	inline constexpr auto clamp(T&& value, TMin&& min, TMax&& max)
	{
		return std::clamp(value, min, max);
	}
};
