#pragma once
#ifdef SN_BUILD_DLL
	#define SPOON_API __declspec(dllexport)
#else
	#define SPOON_API __declspec(dllimport)
#endif // SN_BUILD_DLL

template <typename T> struct Vector2D;
using FVector2D = Vector2D<float>;
using IVector2D = Vector2D<int>;
using DVector2D = Vector2D<double>;

template <typename T> struct Transform;
using FTransform = Transform<float>;
using ITransform = Transform<int>;
using DTransform = Transform<double>;

struct FColor;

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

