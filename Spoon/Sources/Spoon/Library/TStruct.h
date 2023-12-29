#pragma once

#include "TVector.h"

template <typename T>
struct OBJECT_API Transform
{
	Transform<T>() = default;
	Transform<T>(const Vector2D<T>& loc, const Vector2D<T>& size) : Location(loc), Size(size) {}
	
	Vector2D<T> Location;
	Vector2D<T> Size;
};

// template <typename T> struct Transform;
using FTransform = Transform<float>;
using ITransform = Transform<int>;
using DTransform = Transform<double>;