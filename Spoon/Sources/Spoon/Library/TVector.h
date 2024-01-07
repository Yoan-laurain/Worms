#pragma once
#include "Core/Core.h"
#include <snpch.h>


template <typename T>
struct OBJECT_API Vector2D
{
	T X;
	T Y;

	/************************************************************************/
	/* Constructor															*/
	/************************************************************************/

	Vector2D<T>() : X(0), Y(0) {};

	template <typename L = T>
	explicit Vector2D<T>(const L& _val) : X(static_cast<T>(_val)), Y(static_cast<T>(_val)) {};

	template <typename L = T, typename R = L>
	explicit Vector2D<T>(const L& _x, const R& _y) : X(static_cast<T>(_x)), Y(static_cast<T>(_y)) {};

	Vector2D<T>& operator=(const T& _val)
	{
		X = _val; Y = _val;
		return *this;
	}

	/************************************************************************/
	/* Operator overload													*/
	/************************************************************************/

	template <typename L = T>
	Vector2D<T>& operator+=(const Vector2D<L>& _val)
	{
		X += _val.X; Y += _val.Y;
		return *this;
	}

	template<typename L>
	Vector2D<T>& operator+=(const L& _val)
	{
		X += _val; Y += _val;
		return *this;
	}

	template <typename L>
	Vector2D<T>& operator-=(const Vector2D<L>& _val)
	{
		X -= _val.X; Y -= _val.Y;
		return *this;
	}

	template<typename L>
	Vector2D<T>& operator-=(const L& _val)
	{
		X -= _val; Y -= _val;
		return *this;
	}

	template <typename L>
	Vector2D<T>& operator/=(const L& _val)
	{
		X/=_val; Y/=_val;
		return *this;
	}

	Vector2D<T>& ReverseVector()
	{
		X = -X; Y = -Y;
		return *this;
	}

	T GetSquareLength() const
	{
		return (X * X) + (Y * Y);
	}

	T GetLength() const
	{
		return std::sqrt(GetSquareLength());
	}

	T Dot(const Vector2D<T>& _val)
	{
		return X * _val.X + Y * _val.Y;
	}

	/************************************************************************/
	/* Default Var Static													*/
	/************************************************************************/

	// Vector2D<T>D with 0 value
	static Vector2D<T> const Zero() { return Vector2D<T>(0.f); }

	// Vector2D<T>D with 1, 0 value
	static Vector2D<T> const Right() { return Vector2D<T>(1, 0); }

	// Vector2D<T>D with 0, 1 value
	static Vector2D<T> const Up() { return Vector2D<T>(0, 1); }

	static T DotProduct(const Vector2D<T>& _left, const Vector2D<T> _right)
	{
		return _left.X * _right.X + _left.Y * _right.Y;
	}

	static T Distance(const Vector2D<T>& _left, const Vector2D<T>& _right)
	{
		return std::sqrt((_left.X - _right.X) * (_left.X - _right.X) + (_left.Y - _right.Y) * (_left.Y - _right.Y));
	}

	static Vector2D<T> Normalize(const Vector2D<T>& _val)
	{
		return Vector2D<T>(_val / _val.GetLength());
	}

	static Vector2D<T>& Lerp(const Vector2D<T>& _left, const Vector2D<T>& _right, const float& _alpha)
	{
		return Vector2D<T>(_left + (_alpha * (_right - _left)));
	}

	Vector2D<T> GetSafeNormal() 
	{
		const T squareSum = (X * X) + (Y * Y);
		if (squareSum > 0)
		{
			const T scale = 1 / std::sqrt(squareSum);
			return Vector2D<T>(X * scale, Y * scale);
		}
		else
		{
			return Vector2D<T>(0, 0);
		}
	}
	
	Vector2D<T> GetTangent() 
	{
		return Vector2D<T>(Y, -X).GetSafeNormal();
	}

};

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator+(const Vector2D<T>& right, const Vector2D<L>& left)
{
	return Vector2D<T>(right.X + left.X, right.Y + left.Y);
}

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator+(const Vector2D<T>& right, const L& left)
{
	return Vector2D<T>(right.X + left, right.Y + left);
}

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator-(const Vector2D<T>& right, const Vector2D<L>& left)
{
	return Vector2D<T>(right.X - left.X, right.Y - left.Y);
}

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator-(const Vector2D<T>& right, const L& left)
{
	return Vector2D<T>(right.X - left, right.Y - left);
}

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator/(const Vector2D<T>& right, const L& left)
{
	return Vector2D<T>(right.X / left, right.Y / left);
}

template <typename T>
bool const OBJECT_API operator==(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return (left.X == right.X) && (left.Y == right.Y);
}

template <typename T>
bool const OBJECT_API operator!=(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return !(left == right);
}

// This operation doesn't really have sense cause it suppose that X1 and Y1 will always be inferior or equal to X2 and Y2.
template <typename T>
bool const OBJECT_API operator<=(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return left.X <= right.X && left.Y <= right.Y;
}

template <typename T>
Vector2D<T> OBJECT_API operator*(const Vector2D<T>& right, const Vector2D<T>& left)
{
	return Vector2D<T>(right.X * left.X, right.Y * left.Y);
}

template <typename T, typename L = T>
Vector2D<T> OBJECT_API operator*(const Vector2D<T>& right, const L& left)
{
	return Vector2D<T>(right.X * left, right.Y * left);
}	

template <typename T>
bool const OBJECT_API operator>=(const Vector2D<T>& left, const Vector2D<T>& right)
{
	return (right <= left);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& var)
{
	return os << "X : " << var.X << ", Y : " << var.Y;
}



/************************************************************************/
/* Vector3																*/
/************************************************************************/

template <typename T>
struct SPOON_API Vector
{
	T X;
	T Y;
	T Z;

	/************************************************************************/
	/* Constructor															*/
	/************************************************************************/

	Vector() : X(0), Y(0), Z(0) {};

	explicit Vector(const T& _val) : X(_val), Y(_val), Z(_val) {};

	explicit Vector(const T& _x, const T& _y, const T& _z) : X(_x), Y(_y), Z(_z) {};

	/************************************************************************/
	/* Operator overload													*/
	/************************************************************************/

	Vector<T>& operator+=(const Vector<T>& _val)
	{
		X += _val.X; Y += _val.Y; Z += _val.Z;
		return *this;
	}

	template <typename L>
	Vector<T>& operator+=(const L& _val)
	{
		X += _val; Y += _val; Z += _val;
		return *this;
	}

	Vector<T>& operator-=(const Vector<T>& _val)
	{
		X -= _val.X; Y -= _val.Y; Z -= _val.Z;
		return *this;
	}

	template <typename L>
	Vector<T>& operator-=(const L& _val)
	{
		X -= _val; Y -= _val; Z -= _val;
		return *this;
	}

	T GetSquareLength()
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}

	T GetLenght()
	{
		return std::sqrt(GetSquareLength());
	}

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& _var)
{
	return os << "X: " << _var.X << " Y: " << _var.Y << " Z: " << _var.Z;
}

//template <typename T> struct Vector2D;
using FVector2D = Vector2D<float>;
using IVector2D = Vector2D<int>;
using DVector2D = Vector2D<double>;
