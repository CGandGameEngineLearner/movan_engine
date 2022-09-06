#include "math.h"

namespace Movan
{
	Math::AngleUnit Math::k_AngleUnit;

	Math::Math()
	{
		k_AngleUnit = AngleUnit::AU_DEGREE;
	}
	
	bool Math::realEqual(float a, float b, float tolerance /* = std::numeric_limits<float>::epsilon() */)
	{
		return std::fabs(b - a) <= tolerance;
	}

	float Math::clamp(float v, float min, float max)
	{
		return std::max(v, std::min(v, max));
	}

	float Math::degreesToRadians(float degrees) { return degrees * Math_fDeg2Rad; }

	float Math::radiansToDegrees(float radians) { return radians * Math_fRad2Deg; }

	float Math::angleUnitsToRadians(float angleunits)
	{
		if (k_AngleUnit == AngleUnit::AU_DEGREE)
			return angleunits * Math_fDeg2Rad;

		return angleunits;
	}

	float Math::radiansToAngleUnits(float radians)
	{
		if (k_AngleUnit == AngleUnit::AU_DEGREE)
			return radians * Math_fRad2Deg;
		
		return radians;
	}

	float Math::angleUnitsToDegrees(float angleunits)
	{
		if (k_AngleUnit == AngleUnit::AU_RADIAN)
			return angleunits * Math_fRad2Deg;

		return angleunits;
	}
}