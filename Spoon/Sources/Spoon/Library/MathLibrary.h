#pragma once

#include <corecrt_math.h>
#include <numbers>
#include "TVector.h"

namespace MathLibrary
{
	constexpr float Gravity(9.81f);
	
	constexpr double Pi() { return std::numbers::pi; }
	
	static float CosRad(float A) { return cosf(A); }
	static double CosRad(double A) { return cos(A);	}

	static float ACos(float A) { return acosf( (A<-1.f) ? -1.f : ( (A < 1.f) ? A : 1.f) ); }
	static double ACos(double A) { return acos( (A<-1.0) ? -1.0 : ( (A < 1.0) ? A : 1.0) ); }

	static double Lerp(const double& A, const double& B, const double& alpha) { return A + ((B-A)*alpha); }

	template <typename T>
	static Vector2D<T>& Vect2DLerp(const Vector2D<T>& A, const Vector2D<T>& B, const double& alpha) { return Vector2D<T>(A.X + ((B.X-A.X)*alpha), A.Y + ((B.Y-A.Y)*alpha)); }

}
