#pragma once

#include "TVector.h"

template <typename T>
struct OBJECT_API Transform
{
	Transform<T>()
	{
		SetRotation(0.f);
	}

	Transform<T>(const Vector2D<T>& loc, const Vector2D<T>& size, float rot = 0.0f, float sin = 0.0f, float cos = 1.0f)
		: Location(loc), Size(size)
	{
		SetRotation(rot);
	}

	void AddRotation(float rot)
	{
		Rotation += rot;
		Sin = std::sin(Rotation);
		Cos = std::cos(Rotation);
	}

	void SetRotation(float rot)
	{
		Rotation = rot;
		Sin = std::sin(Rotation);
		Cos = std::cos(Rotation);
	}

	Vector2D<T> Location;
	Vector2D<T> Size;
	float Rotation = 0.0f;
	float Sin;
	float Cos;
};

// template <typename T> struct Transform;
using FTransform = Transform<float>;
using ITransform = Transform<int>;
using DTransform = Transform<double>;
